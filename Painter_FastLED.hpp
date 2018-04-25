#pragma once

#include "Painter.h"
#include <FastLED.h>

#include <utility>

template <uint16_t Width, uint16_t Height, uint8_t DataPin>
class FastLedDisplayPainter : public DisplayPainter<FastLedDisplayPainter<Width, Height, DataPin>, decltype(FastLED)>
{
	using Parent = DisplayPainter<FastLedDisplayPainter<Width, Height, DataPin>, decltype(FastLED)>;

	constexpr static uint16_t NumLeds = Width * Height;

public:
	~FastLedDisplayPainter() {
		FastLED.show();
	}

	void rect(const Point& topLeft, const Size& size, const Color& color) {
		rect(topLeft, topLeft + size, color);
	}

	void rect(const Point& topLeft, const Point& bottomRight, const Color& color) {
		// Fill the horizontal lines
		for (uint16_t x = topLeft.x(); x < bottomRight.x(); ++x)
		{
			fillCrgbFromColor(this->_screenBuffer[topLeft.y() * Width + x], color);
			fillCrgbFromColor(this->_screenBuffer[bottomRight.y() * Width + x], color);
		}

		// Fill in the vertical lines
		for (uint16_t y = topLeft.y(); y < bottomRight.y(); ++y)
		{
			fillCrgbFromColor(this->_screenBuffer[y * Width + topLeft.x()], color);
			fillCrgbFromColor(this->_screenBuffer[y * Width + bottomRight.x()], color);
		}
	}

	void fillRect(const Point& topLeft, const Size& size, const Color& color) {
		for (uint16_t y = topLeft.y(); y < topLeft.y() + size.height(); ++y)
			drawFastHLine(Point(topLeft.x(), y), size.width(), color);
	}

	void fillRect(const Point& topLeft, const Point& bottomRight, const Color& color) {
		fillRect(topLeft, bottomRight - topLeft, color);
	}

	void fillScreen(const Color& color) {
		for (auto& pixel: this->_screenBuffer)
			fillCrgbFromColor(pixel, color);
	}

	void setPixel(const Point& pixel, const Color& color) {
		fillCrgbFromColor(this->_screenBuffer[pixel.y() * Width + pixel.x()], color);
	}

	inline void setPixel(uint16_t x, uint16_t y, const Color& color) {
		setPixel(Point{x, y}, color);
	}

	void drawFastVLine(const Point& start, uint16_t height, const Color& color) {
		for (uint16_t yOffset = start.y() * Width; yOffset < (start.y() + height) * Width; yOffset += Width)
			fillCrgbFromColor(this->_screenBuffer[yOffset + start.x()], color);
	}

	void drawFastHLine(const Point& start, uint16_t width, const Color& color) {
		const uint16_t yOffset = start.y() * Width;
		for (uint16_t x = start.x(); x < start.x() + width; ++x)
			fillCrgbFromColor(this->_screenBuffer[yOffset + x], color);
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

private:
	static inline void fillCrgbFromColor(CRGB& crgb, const Color& color) {
		crgb.r = color.r;
		crgb.g = color.g;
		crgb.b = color.b;
	}

private:
	struct FastLedWrapper {
		inline FastLedWrapper() {
			FastLED.addLeds<NEOPIXEL, DataPin>(_screenBuffer, Width * Height);
		}

		CRGB _screenBuffer[NumLeds];
	};

	static FastLedWrapper _fastLedWrapper;
};