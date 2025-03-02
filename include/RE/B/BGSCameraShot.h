#pragma once

#include "RE/B/BSResourceHandle.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESImageSpaceModifiableForm.h"
#include "RE/T/TESModel.h"

namespace RE
{
	class BGSCameraShot :
		public TESForm,                     // 00
		public TESModel,                    // 20
		public TESImageSpaceModifiableForm  // 48
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSCameraShot;
		inline static constexpr auto VTABLE = VTABLE_BGSCameraShot;
		inline static constexpr auto FORMTYPE = FormType::CameraShot;

		enum class CAM_ACTION
		{
			kShoot = 0,
			kFly = 1,
			kHit = 2,
			kZoom = 3
		};

		enum class CAM_OBJECT
		{
			kAttacker = 0,
			kProjectile = 1,
			kTarget = 2,
			kLeadActor = 3
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct CAMERA_SHOT_DATA  // DATA
		{
		public:
			enum class Flag
			{
				kNone = 0,
				kPositionFollowsLocation = 1 << 0,
				kRotationFollowsTarget = 1 << 1,
				kDontFollowBone = 1 << 2,
				kFirstPersonCamera = 1 << 3,
				kNoTracer = 1 << 4,
				kStartAtTimeZero = 1 << 5
			};

			// members
			REX::EnumSet<CAM_ACTION, std::uint32_t> cameraAction;                // 00
			REX::EnumSet<CAM_OBJECT, std::uint32_t> location;                    // 04
			REX::EnumSet<CAM_OBJECT, std::uint32_t> target;                      // 08
			REX::EnumSet<Flag, std::uint32_t>       flags;                       // 0C
			float                                   playerTimeMult;              // 10
			float                                   targetTimeMult;              // 14
			float                                   globalTimeMult;              // 18
			float                                   maxTime;                     // 1C
			float                                   minTime;                     // 20
			float                                   targetPercentBetweenActors;  // 24
			float                                   nearTargetDistance;          // 28
		};
		static_assert(sizeof(CAMERA_SHOT_DATA) == 0x2C);

		~BGSCameraShot() override;  // 00

		// override (TESForm)
		void InitializeData() override;      // 04
		bool Load(TESFile* a_mod) override;  // 06
		void InitItemImpl() override;        // 13

		// members
		CAMERA_SHOT_DATA      data;          // 58 - DATA
		std::uint32_t         pad84;         // 84
		void*                 unk88;         // 88 - smart ptr
		void*                 unk90;         // 90 - smart ptr
		RefHandle             unk98;         // 98
		std::uint32_t         unk9C;         // 9C
		NiPointer<NiNode>     cameraNode;    // A0 - smart ptr
		NiPointer<NiAVObject> unkA8;         // A8 - smart ptr
		std::uint8_t          unkB0;         // B0
		bool                  unkB1;         // B1
		std::uint16_t         padB2;         // B2
		std::uint32_t         padB4;         // B4
		ModelDBHandle         cameraHandle;  // B8
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSCameraShot) == 0xC0);
}
