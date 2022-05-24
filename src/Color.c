#include "Color.h"

static f32 _Color_U8ToNormalizedF32(u8 byte)
{
	return (f32)byte / 255.0f;
}

static u8 _Color_NormalizedF32ToU8(f32 data)
{
	return (u8)(data * 255.0f);
}

Color Color_FromU32(u32 rgba)
{
	return (Color) {
		.r = _Color_U8ToNormalizedF32((rgba >> 24) & 0xff),
		.g = _Color_U8ToNormalizedF32((rgba >> 16) & 0xff),
		.b = _Color_U8ToNormalizedF32((rgba >> 8) & 0xff),
		.a = _Color_U8ToNormalizedF32(rgba & 0xff),
	};
}

u32 Color_ToU32(Color color)
{
	return (u32)((_Color_NormalizedF32ToU8(color.r) << 24) | (_Color_NormalizedF32ToU8(color.g) << 16) | (_Color_NormalizedF32ToU8(color.b) << 8) | (_Color_NormalizedF32ToU8(color.a)));
}

