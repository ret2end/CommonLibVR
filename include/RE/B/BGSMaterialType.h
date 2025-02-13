#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/F/FormTypes.h"
#include "RE/M/MaterialIDs.h"
#include "RE/N/NiColor.h"
#include "RE/T/TESForm.h"

namespace RE
{
	class BGSMaterialType : public TESForm
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSMaterialType;
		inline static constexpr auto VTABLE = VTABLE_BGSMaterialType;
		inline static constexpr auto FORMTYPE = FormType::MaterialType;

		enum class FLAG
		{
			kNone = 0,
			kStairs = 1 << 0,
			kArrowsStick = 1 << 1
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		~BGSMaterialType() override;  // 00

		// override (TESForm)
		void ClearData() override;           // 04
		bool Load(TESFile* a_mod) override;  // 06
		void InitItemImpl() override;        // 13

		static BGSMaterialType* GetMaterialType(MATERIAL_ID a_materialID)
		{
			using func_t = decltype(&BGSMaterialType::GetMaterialType);
			static REL::Relocation<func_t> func{ RELOCATION_ID(20529, 20968) };
			return func(a_materialID);
		}

		// members
		BGSMaterialType*                  parentType;          // 20 - PNAM
		BSFixedString                     materialName;        // 28 - MNAM
		MATERIAL_ID                       materialID;          // 30
		NiColor                           materialColor;       // 34 - CNAM
		float                             buoyancy;            // 40 - BNAM
		REX::EnumSet<FLAG, std::uint32_t> flags;               // 44 - FNAM
		BGSImpactDataSet*                 havokImpactDataSet;  // 48 - HNAM
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSMaterialType) == 0x50);
}
