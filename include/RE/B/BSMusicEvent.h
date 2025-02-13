#pragma once

namespace RE
{
	class BSIMusicType;

	struct BSMusicEvent
	{
	public:
		enum class MUSIC_MESSAGE_TYPE
		{
			kAdd,
			kRemove,
			kRemoveImmediate,
			kPause,
			kUnpause
		};

		BSIMusicType*                                  musicType;  // 00
		REX::EnumSet<MUSIC_MESSAGE_TYPE, std::int32_t> msgType;    // 08
		std::uint32_t                                  pad0C;      // 0C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSMusicEvent) == 0x10);
}
