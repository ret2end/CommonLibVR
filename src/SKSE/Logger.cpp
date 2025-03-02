#include "SKSE/Logger.h"

#include "RE/B/BSTEvent.h"
#include "RE/L/LogEvent.h"
#include "RE/V/VirtualMachine.h"

#include "REX/W32/OLE32.h"
#include "REX/W32/SHELL32.h"

#include "SKSE/API.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>

namespace SKSE
{
	namespace Impl
	{
		class LogEventHandler : public RE::BSTEventSink<RE::BSScript::LogEvent>
		{
		public:
			using EventResult = RE::BSEventNotifyControl;

			[[nodiscard]] static inline LogEventHandler* GetSingleton()
			{
				static LogEventHandler singleton;
				return std::addressof(singleton);
			}

			inline void SetFilter(std::regex a_filter) { _filter = std::move(a_filter); }

			EventResult ProcessEvent(const RE::BSScript::LogEvent* a_event, RE::BSTEventSource<RE::BSScript::LogEvent>*) override
			{
				using Severity = RE::BSScript::ErrorLogger::Severity;

				if (a_event && a_event->errorMsg && std::regex_search(a_event->errorMsg, _filter)) {
					switch (a_event->severity) {
					case Severity::kInfo:
						log::info("{}"sv, a_event->errorMsg);
						break;
					case Severity::kWarning:
						log::warn("{}"sv, a_event->errorMsg);
						break;
					case Severity::kError:
						log::error("{}"sv, a_event->errorMsg);
						break;
					case Severity::kFatal:
						log::critical("{}"sv, a_event->errorMsg);
						break;
					}
				}

				return EventResult::kContinue;
			}

		private:
			LogEventHandler() = default;
			LogEventHandler(const LogEventHandler&) = delete;
			LogEventHandler(LogEventHandler&&) = delete;
			~LogEventHandler() override = default;

			LogEventHandler& operator=(const LogEventHandler&) = delete;
			LogEventHandler& operator=(LogEventHandler&&) = delete;

			std::regex _filter;
		};
	}

	namespace log
	{
		std::optional<std::filesystem::path> log_directory()
		{
			wchar_t*                                                       buffer{ nullptr };
			const auto                                                     result = REX::W32::SHGetKnownFolderPath(REX::W32::FOLDERID_Documents, REX::W32::KF_FLAG_DEFAULT, nullptr, std::addressof(buffer));
			std::unique_ptr<wchar_t[], decltype(&REX::W32::CoTaskMemFree)> knownPath(buffer, REX::W32::CoTaskMemFree);
			if (!knownPath || result != 0) {
				error("failed to get known folder path"sv);
				return std::nullopt;
			}

			std::filesystem::path path = knownPath.get();
			path /= "My Games"sv;
#ifndef SKYRIMVR
			path /= std::filesystem::exists("steam_api64.dll") ? "Skyrim Special Edition" : "Skyrim Special Edition GOG";
#else
			path /= *REL::Relocation<const char**>(RELOCATION_ID(508778, 502114)).get();
#endif
			path /= "SKSE"sv;

			return path;
		}

		void add_papyrus_sink(std::regex a_filter)
		{
			auto handler = Impl::LogEventHandler::GetSingleton();
			handler->SetFilter(std::move(a_filter));

			SKSE::RegisterForAPIInitEvent([]() {
				auto papyrus = SKSE::GetPapyrusInterface();
				if (papyrus) {
					papyrus->Register([](RE::BSScript::IVirtualMachine* a_vm) {
						auto handler = Impl::LogEventHandler::GetSingleton();
						a_vm->RegisterForLogEvent(handler);
						return true;
					});
				}
			});
		}

		void remove_papyrus_sink()
		{
			SKSE::RegisterForAPIInitEvent([]() {
				auto papyrus = SKSE::GetPapyrusInterface();
				if (papyrus) {
					papyrus->Register([](RE::BSScript::IVirtualMachine* a_vm) {
						auto handler = Impl::LogEventHandler::GetSingleton();
						a_vm->UnregisterForLogEvent(handler);
						return true;
					});
				}
			});
		}

		void init()
		{
			// remove ifdef if 1.5.x support is removed
#ifdef SKYRIM_SUPPORT_AE
			auto path = log_directory();
			if (!path) {
				return;
			}

			*path /= std::format("{}.log", SKSE::GetPluginName());

			std::vector<spdlog::sink_ptr> sinks{
				std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true),
				std::make_shared<spdlog::sinks::msvc_sink_mt>()
			};

			auto logger = std::make_shared<spdlog::logger>("global", sinks.begin(), sinks.end());
#	ifndef NDEBUG
			logger->set_level(spdlog::level::debug);
			logger->flush_on(spdlog::level::debug);
#	else
			logger->set_level(spdlog::level::info);
			logger->flush_on(spdlog::level::info);
#	endif
			spdlog::set_default_logger(std::move(logger));
			spdlog::set_pattern("[%T.%e] [%=5t] [%L] %v");
#endif
		}
	}
}
