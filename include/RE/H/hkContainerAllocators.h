#pragma once

#include "RE/H/hkMemoryAllocator.h"

namespace RE
{
	struct hkContainerHeapAllocator
	{
		struct Allocator : public hkMemoryAllocator
		{
			inline static constexpr auto RTTI = RTTI_hkContainerHeapAllocator__Allocator;
			inline static constexpr auto VTABLE = VTABLE_hkContainerHeapAllocator__Allocator;

			~Allocator() override;  // 00

			void*        BlockAlloc(std::int32_t a_numBytes) override;                           // 01
			void         BlockFree(void* a_ptr, std::int32_t a_numBytes) override;               // 02
			void*        BufAlloc(std::int32_t& a_reqNumBytesInOut) override;                    // 03
			void         BufFree(void* a_ptr, std::int32_t a_numBytes) override;                 // 04
			void         GetMemoryStatistics(MemoryStatistics& a_usage) override;                // 08
			std::int32_t GetAllocatedSize(const void* a_obj, std::int32_t a_numBytes) override;  // 09
		};
		static_assert(sizeof(Allocator) == 0x8);

		[[nodiscard]] static Allocator* GetSingleton()
		{
			static REL::Relocation<hkContainerHeapAllocator::Allocator*> singleton{ RELOCATION_ID(510713, 383828) };
			return singleton.get();
		}

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkContainerHeapAllocator) == 0x1);
}
