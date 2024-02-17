#pragma once
#include <sstream>
#include<string>

using byte = unsigned char;

struct Color_t
{
	byte r = 0, g = 0, b = 0, a = 0;

	bool operator==(Color_t c) const {
		return (this->r == c.r && this->g == c.g && this->b == c.b && this->a == c.a);
	}

	bool operator!=(Color_t c) const {
		return !(this->r == c.r && this->g == c.g && this->b == c.b && this->a == c.a);
	}

	[[nodiscard]] std::string to_hex() const
	{
		std::stringstream ss;
		ss << "\x7";
		ss << std::hex << (static_cast<int>(r) << 16 | static_cast<int>(g) << 8 | static_cast<int>(b));
		return ss.str();
	}

	[[nodiscard]] std::string to_hex_alpha() const
	{
		std::stringstream ss;
		ss << "\x8";
		ss << std::hex << (static_cast<int>(r) << 16 | static_cast<int>(g) << 8 | static_cast<int>(b));
		ss << std::hex << static_cast<int>(a);
		return ss.str();
	}
};