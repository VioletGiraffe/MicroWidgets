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
		rect(topLeft, topLeft + size - 1, color);
	}

	void rect(const Point& topLeft, const Point& bottomRight, const Color& color) {
		// Fill the horizontal lines

		const auto fastLedColor = crgbFromColor(color);
		for (uint16_t x = topLeft.x(), rightX = bottomRight.x(); x <= rightX; ++x)
		{
			FastLedDisplayPainter<Width, Height, DataPin>::_fastLedWrapper._screenBuffer[topLeft.y() * Width + x] = fastLedColor;
			FastLedDisplayPainter<Width, Height, DataPin>::_fastLedWrapper._screenBuffer[bottomRight.y() * Width + x] = fastLedColor;
		}

		// Fill in the vertical lines
		// The first and last horizontal lines of the rect had already been filled in completely by the previous loop over x coordinate
		for (uint16_t y = topLeft.y() + 1, bottomY = bottomRight.y(); y < bottomY; ++y)
		{
			FastLedDisplayPainter<Width, Height, DataPin>::_fastLedWrapper._screenBuffer[y * Width + topLeft.x()] = fastLedColor;
			FastLedDisplayPainter<Width, Height, DataPin>::_fastLedWrapper._screenBuffer[y * Width + bottomRight.x()] = fastLedColor;
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
		const auto fastLedColor = crgbFromColor(color);
		for (auto& pixel: this->_fastLedWrapper._screenBuffer)
			pixel = fastLedColor;
	}

	void setPixel(const Point& pixel, const Color& color) {
		this->_fastLedWrapper._screenBuffer[pixel.y() * Width + pixel.x()] = crgbFromColor(color);
	}

	inline void setPixel(uint16_t x, uint16_t y, const Color& color) {
		setPixel(Point{x, y}, color);
	}

	void drawFastVLine(const Point& start, uint16_t height, const Color& color) {
		const auto fastLedColor = crgbFromColor(color);
		for (uint16_t yOffset = start.y() * Width; yOffset < (start.y() + height) * Width; yOffset += Width)
			this->_fastLedWrapper._screenBuffer[yOffset + start.x()] = fastLedColor;
	}

	void drawFastHLine(const Point& start, uint16_t width, const Color& color) {
		const uint16_t yOffset = start.y() * Width;
		const auto fastLedColor = crgbFromColor(color);
		for (uint16_t x = start.x(); x < start.x() + width; ++x)
			this->_fastLedWrapper._screenBuffer[yOffset + x] = fastLedColor;
	}

	// Reference Bresenham's line algorithm implementation from https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C
	void drawLine(const Point& start, const Point& end, const Color& color) {
		int x0 = start.x(), y0 = start.y(), x1 = end.x(), y1 = end.y();
		int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
		int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1; 
		int err = (dx>dy ? dx : -dy)/2, e2;

		const auto fastLedColor = crgbFromColor(color);
		for(;;)
		{
			this->_fastLedWrapper._screenBuffer[y0 * Width + x0] = fastLedColor;
			if (x0 == x1 && y0 == y1)
				break;

			const auto e2 = err;
			if (e2 >-dx) { err -= dy; x0 += sx; }
			if (e2 < dy) { err += dx; y0 += sy; }
		}
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
	static inline CRGB crgbFromColor(const Color& color) {
		CRGB crgb;
		crgb.r = color.r();
		crgb.g = color.g();
		crgb.b = color.b();

		return crgb;
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

template <uint16_t Width, uint16_t Height, uint8_t DataPin>
typename FastLedDisplayPainter<Width, Height, DataPin>::FastLedWrapper
    FastLedDisplayPainter<Width, Height, DataPin>::_fastLedWrapper;