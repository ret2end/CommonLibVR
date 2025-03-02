#include "RE/L/LooseFileStream.h"

#include "RE/M/MemoryManager.h"

namespace RE
{
	namespace BSResource
	{
#ifndef SKYRIM_SUPPORT_AE
		LooseFileStream* LooseFileStream::Create(BSFixedString a_prefix, BSFixedString a_dirName, BSFixedString a_fileName, std::uint32_t a_fileSize, bool a_readOnly, Location* a_location)
		{
			auto mem = malloc<LooseFileStream>();
			return mem->Ctor(a_prefix, a_dirName, a_fileName, a_fileSize, a_readOnly, a_location);
		}

		LooseFileStream* LooseFileStream::Ctor(const BSFixedString& a_prefix, const BSFixedString& a_dirName, const BSFixedString& a_fileName, std::uint32_t a_fileSize, bool a_readOnly, Location* a_location)
		{
			using func_t = decltype(&LooseFileStream::Ctor);
			static REL::Relocation<func_t> func{ RELOCATION_ID(68663, 0) };
			return func(this, a_prefix, a_dirName, a_fileName, a_fileSize, a_readOnly, a_location);
		}
#endif
	}
}
