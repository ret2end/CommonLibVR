#pragma once

#ifndef SKYRIMVR

namespace RE
{
	struct IMapCameraCallbacks
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMapCameraCallbacks;
		inline static constexpr auto VTABLE = VTABLE_IMapCameraCallbacks;

		// add
		virtual void Unk_00(void);  // 00
		virtual void Unk_01(void);  // 01

		virtual ~IMapCameraCallbacks();  // 02
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(IMapCameraCallbacks) == 0x8);
}

#endif
