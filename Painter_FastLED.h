#pragma once

#include "Painter.h"
#include <FastLED.h>

#include <utility>

template <uint16_t Width, uint16_t Height>
class FastLedDisplayPainter : public DisplayPainter<FastLedDisplayPainter, decltype(FastLED)>
{
	using Parent = DisplayPainter<FastLedDisplayPainter, decltype(FastLED)>;

	static CRGB _screenBuffer[Width * Height];

public:
	void rect(const Point& topLeft, const Size& size, const Color& color) {
		
	}

	void rect(const Point& topLeft, const Point& bottomRight, const Color& color) {
		
	}

	void fillRect(const Point& topLeft, const Size& size, const Color& color) {
		
	}

	void fillRect(const Point& topLeft, const Point& bottomRight, const Color& color) {
		
	}

	void fillScreen(const Color& color) {
		
	}

	void setPixel(const Point& pixel, const Color& color) {
		
	}

	void setPixel(uint16_t x, uint16_t y, const Color& color) {
		setPixel(Point{x, y}, color);
	}

	void drawFastVLine(const Point& start, uint16_t height, const Color& color) {
		
	}

	void drawFastHLine(const Point& start, uint16_t width, const Color& color) {
		
	}

	void drawLine(const Point& start, const Point& end, const Color& color) {
		
	}

	void setCursor(const Point& pos) {
		
	}

	void setTextColor(const Color& color) {
		
	}

	void setTextColor(const Color& c, const Color& bg) {
		
	}

	void setTextSize(uint8_t s) {
		
	}

	void setTextWrap(bool w) {
		
	}

	template <typename ...Args>
	void print(Args&&... args) {
		
	}

	static constexpr uint16_t screenWidth() {
		return Width;
	}

	static constexpr uint16_t screenHeight() {
		return Height;
	}
};