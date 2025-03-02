#pragma once

#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class TESObjectREFR;

	struct TESFurnitureEvent
	{
	public:
		enum class FurnitureEventType
		{
			kEnter = 0,
			kExit = 1
		};

		// members
		NiPointer<TESObjectREFR>                        actor;            // 00
		NiPointer<TESObjectREFR>                        targetFurniture;  // 08
		REX::EnumSet<FurnitureEventType, std::uint32_t> type;             // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESFurnitureEvent) == 0x18);
}
