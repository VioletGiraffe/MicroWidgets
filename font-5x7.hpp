#pragma once

#include <Arduino.h>

#include <stdint.h>

// Taken from https://github.com/ChuckM/bb-lcd

class Font5x7
{
public:
	static constexpr uint8_t symbolWidth = 5;
	static constexpr uint8_t symbolHeight = 7;

	inline static bool fontBit(const char character, const uint8_t column, const uint8_t row)
	{
		return (font_data[(uint8_t)character * symbolWidth + column] & 1<<row) != 0;
	}

private:
	static const PROGMEM uint8_t font_data[];
};