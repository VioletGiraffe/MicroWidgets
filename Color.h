#pragma once

#include <stdint.h>

#define DEFINE_COLOR(name, r, g, b) \
	inline static const Color name() {\
	  return Color{r, g, b};\
   }

class Color
{
public:
	inline explicit Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) : _r(r), _g(g), _b(b) {};

	static inline Color fromHSV(uint16_t h, uint8_t s, uint8_t v) {
		Color out;

		if (s <= 0.0f)
		{
			out._r = v;
			out._g = v;
			out._b = v;
			return out;
		}

		float hh = h / 60.0f;
		uint16_t i = (uint16_t)hh;
		
		float ff = hh - i;
		const float vFloat = v / 255.0f, sFloat = s / 255.0f;
		const float p = vFloat * (1.0f - sFloat);
		const float q = vFloat * (1.0f - (sFloat * ff));
		const float t = vFloat * (1.0f - (sFloat * (1.0f - ff)));

		switch(i) {
		case 0:
			out._r = v;
			out._g = static_cast<uint8_t>(t * 255.0f);
			out._b = static_cast<uint8_t>(p * 255.0f);
			break;
		case 1:
			out._r = static_cast<uint8_t>(q * 255.0f);
			out._g = v;
			out._b = static_cast<uint8_t>(255.0f * p);
			break;
		case 2:
			out._r = static_cast<uint8_t>(255.0f * p);
			out._g = v;
			out._b = static_cast<uint8_t>(255.0f * t);
			break;

		case 3:
			out._r = static_cast<uint8_t>(255.0f * p);
			out._g = static_cast<uint8_t>(255.0f * q);
			out._b = v;
			break;
		case 4:
			out._r = static_cast<uint8_t>(255.0f * t);
			out._g = static_cast<uint8_t>(255.0f * p);
			out._b = v;
			break;
		case 5:
		default:
			out._r = v;
			out._g = static_cast<uint8_t>(255.0f * p);
			out._b = static_cast<uint8_t>(255.0f * q);
			break;
		}

		return out;     
	}

	inline uint16_t toRgb565() const {
		return to565(_r, _g, _b);
	}

	inline uint16_t toBgr565() const {
		return to565(_b, _g, _r);
	}

	inline uint32_t toRgb() const {
		return to32bit(_r, _g, _b);
	}

	inline uint32_t toBgr() const {
		return to32bit(_b, _g, _r);
	}

// Predefined colors
	// Grayscale
	DEFINE_COLOR(black, 0, 0, 0)
	DEFINE_COLOR(darkGrey, 64, 64, 64)
	DEFINE_COLOR(grey, 127, 127, 127)
	DEFINE_COLOR(white, 255, 255, 255)

	// Dark shades
	DEFINE_COLOR(maroon, 128, 0, 0)
	DEFINE_COLOR(darkRed, 139, 0, 0)
	DEFINE_COLOR(carmine, 150, 0, 24)
	DEFINE_COLOR(purple, 127, 0, 127)

	// Evenly spaced fully saturated colors colors
	DEFINE_COLOR(red, 255, 0, 0)
	DEFINE_COLOR(orange, 255, 127, 0)
	DEFINE_COLOR(yellow, 255, 255, 0)
	DEFINE_COLOR(lawnGreen, 127, 255, 0)
	DEFINE_COLOR(green, 0, 255, 0)
	DEFINE_COLOR(springGreen, 0, 255, 127)
	DEFINE_COLOR(cyan, 0, 255, 255)
	DEFINE_COLOR(azure, 0, 127, 255)
	DEFINE_COLOR(blue, 0, 0, 255)
	DEFINE_COLOR(violet, 127, 0, 255)
	DEFINE_COLOR(magenta, 255, 0, 255)
	DEFINE_COLOR(pink, 255, 0, 127)

private:
	inline static uint16_t to565(uint8_t ch1, uint8_t ch2, uint8_t ch3) {
		return ((static_cast<uint16_t>(ch1 & 0b11111000) << 8) | (static_cast<uint16_t>(ch2 & 0b11111100) << 3) | (static_cast<uint16_t>(ch3) >> 3));
	}

	inline static uint32_t to32bit(uint8_t ch1, uint8_t ch2, uint8_t ch3) {
		return (static_cast<uint32_t>(ch1) << 16) | (static_cast<uint32_t>(ch2) << 8) | static_cast<uint32_t>(ch3);
	}

private:
	uint8_t _r = 0, _g = 0, _b = 0;
};

#undef DEFINE_COLOR // So that this macro is not visible to the client
