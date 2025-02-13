#pragma once

#include "RE/B/BSLightingShaderMaterialBase.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiSourceTexture;

	class BSLightingShaderMaterialFacegen : public BSLightingShaderMaterialBase
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSLightingShaderMaterialFacegen;
		inline static constexpr auto VTABLE = VTABLE_BSLightingShaderMaterialFacegen;
		inline static constexpr auto FEATURE = Feature::kFaceGen;

		~BSLightingShaderMaterialFacegen() override;  // 00

		// override (BSLightingShaderMaterialBase)
		BSShaderMaterial* Create() override;                                                                                                                 // 01
		void              CopyMembers(BSShaderMaterial* a_other) override;                                                                                   // 02
		std::uint32_t     ComputeCRC32(void) override;                                                                                                       // 04
		Feature           GetFeature() const override;                                                                                                       // 06 - { return Feature::kFaceGen; }
		void              OnLoadTextureSet(std::uint64_t a_arg1, BSTextureSet* a_textureSet) override;                                                       // 08
		void              ClearTextures() override;                                                                                                          // 09
		void              ReceiveValuesFromRootMaterial(bool a_skinned, bool a_rimLighting, bool a_softLighting, bool a_backLighting, bool a_MSN) override;  // 0A
		void              GetTextures(void) override;                                                                                                        // 0B

		// members
		NiPointer<NiSourceTexture> tintTexture;        // A0
		NiPointer<NiSourceTexture> detailTexture;      // A8
		NiPointer<NiSourceTexture> subsurfaceTexture;  // B0

	protected:
		BSLightingShaderMaterialFacegen* Ctor()
		{
			using func_t = decltype(&BSLightingShaderMaterialFacegen::Ctor);
			static REL::Relocation<func_t> func{ RELOCATION_ID(100077, 106784) };
			return func(this);
		}
		friend class BSLightingShaderMaterialBase;

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSLightingShaderMaterialFacegen) == 0xB8);
}
