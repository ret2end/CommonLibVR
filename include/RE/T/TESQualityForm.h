#pragma once

#include "RE/B/BaseFormComponent.h"

namespace RE
{
	class TESQualityForm : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESQualityForm;
		inline static constexpr auto VTABLE = VTABLE_TESQualityForm;

		enum class Quality
		{
			kNovice = 0,
			kApprentice = 1,
			kJourneyman = 2,
			kExpert = 3,
			kMaster = 4
		};

		~TESQualityForm() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01 - { quality = 0; }
		void ClearDataComponent() override;                     // 02 - { return; }
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		// members
		REX::EnumSet<Quality, std::uint32_t> quality;  // 08 - QUAL
		std::uint32_t                        pad0C;    // 0C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESQualityForm) == 0x10);
}
