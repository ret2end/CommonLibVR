#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/I/IMenu.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class TESObjectREFR;

	// menuDepth = 12
	// flags = kPausesGame | kAlwaysOpen | kUsesCursor | kAllowSaving
	// context = kConsole
	class Console : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_Console;
		constexpr static std::string_view MENU_NAME = "Console";

		~Console() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04

		static NiPointer<TESObjectREFR> GetSelectedRef();
		static ObjectRefHandle          GetSelectedRefHandle();

		void SetSelectedRef(NiPointer<TESObjectREFR> a_refPtr);
		void SetSelectedRef(TESObjectREFR* a_ref);
		void SetSelectedRef(ObjectRefHandle a_handle);

		// members
		void*         opcode;  // 30
		std::uint64_t unk38;   // 38
		std::uint64_t unk40;   // 40
#ifdef SKYRIM_SUPPORT_AE
		std::uint32_t unk48;                   // 48
		std::uint8_t  unk4c;                   // 4c
		bool          showAchievementWarning;  // 4d -- only used in ctor
		bool          ctrlKeyHeld;             // 4e
		std::uint8_t  pad4f;                   // 4f
#else
		std::uint64_t unk48;  // 48
		std::uint64_t unk50;  // 50
#endif

	protected:
		void SetSelectedRef_Impl(ObjectRefHandle& a_handle);

	private:
		KEEP_FOR_RE()
	};
#ifndef SKYRIMVR
#	ifdef SKYRIM_SUPPORT_AE
	static_assert(sizeof(Console) == 0x50);
#	else
	static_assert(sizeof(Console) == 0x58);
#	endif
#else
	static_assert(sizeof(Console) == 0x68);
#endif
}
