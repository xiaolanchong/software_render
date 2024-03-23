#pragma once

using ColorType = std::uint32_t;

inline ColorType Rgb(std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
	return ((ColorType)(((r) | ((std::uint16_t)((g)) << 8)) | (((std::uint32_t)(b)) << 16)));
}

inline std::uint8_t GetR(ColorType rgb)
{
	return static_cast<std::uint8_t>(rgb & 0xff);
}

inline std::uint8_t GetG(ColorType rgb)
{
	return static_cast<std::uint8_t>((rgb >> 8) & 0xff);
}

inline std::uint8_t GetB(ColorType rgb)
{
	return static_cast<std::uint8_t>((rgb >> 16) & 0xff);
}
