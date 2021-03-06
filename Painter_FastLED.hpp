#pragma once

#include "Painter.h"
#include "font-5x7.hpp"

#include <FastLED.h>

#include <utility>

template <uint16_t LogicalWidth, uint16_t LogicalHeight, uint8_t DataPin, bool Transpose = true, typename Font = Font5x7>
class FastLedDisplayPainter : public DisplayPainter<FastLedDisplayPainter<LogicalWidth, LogicalHeight, DataPin, Transpose, Font>, decltype(FastLED)>
{
	using Parent = DisplayPainter<FastLedDisplayPainter<LogicalWidth, LogicalHeight, DataPin, Transpose, Font>, decltype(FastLED)>;

	constexpr static uint16_t Width = Transpose ? LogicalHeight : LogicalWidth;
	constexpr static uint16_t Height = Transpose ? LogicalWidth : LogicalHeight;
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
			FastLedDisplayPainter<Width, Height, DataPin>::_fastLedWrapper._screenBuffer[pixelAddress(x, topLeft.y())] = fastLedColor;
			FastLedDisplayPainter<Width, Height, DataPin>::_fastLedWrapper._screenBuffer[pixelAddress(x, bottomRight.y())] = fastLedColor;
		}

		// Fill in the vertical lines
		// The first and last horizontal lines of the rect had already been filled in completely by the previous loop over x coordinate
		for (uint16_t y = topLeft.y() + 1, bottomY = bottomRight.y(); y < bottomY; ++y)
		{
			FastLedDisplayPainter<Width, Height, DataPin>::_fastLedWrapper._screenBuffer[pixelAddress(topLeft.x(), y)] = fastLedColor;
			FastLedDisplayPainter<Width, Height, DataPin>::_fastLedWrapper._screenBuffer[pixelAddress(bottomRight.x(), y)] = fastLedColor;
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
		this->_fastLedWrapper._screenBuffer[pixelAddress(pixel.x(), pixel.y())] = crgbFromColor(color);
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
			this->_fastLedWrapper._screenBuffer[pixelAddress(x0, y0)] = fastLedColor;
			if (x0 == x1 && y0 == y1)
				break;

			const auto e2 = err;
			if (e2 >-dx) { err -= dy; x0 += sx; }
			if (e2 < dy) { err += dx; y0 += sy; }
		}
	}

	void setCursor(const Point& pos) {
		_textCursor = pos;
	}

	void setTextColor(const Color& color) {
		_textColorForeground = color;
	}

	void setTextColor(const Color& c, const Color& bg) {
		_textColorForeground = c;
		_textColorBackground = bg;
	}

	void setTextSize(uint8_t s) {
		_textSize = s;
	}

	void setTextWrap(bool wrap) {
		static_assert(DataPin == 0 && Width == 0 && Height == 0, "Not implemented");
	}

	template <typename ...Args>
	void print(Args&&... args) {
		
	}

	template <size_t NumChars>
	void print(const char (&text)[NumChars]) {
		for (const char c: text)
			print(c);
	}

	void print(const char asciiCharacter) {
		if (asciiCharacter == '\0')
			return;
		else if (asciiCharacter == ' ')
			_textCursor.x() += Font::symbolWidth + 1;
		else if (asciiCharacter == '\n' || asciiCharacter == '\r')
		{
			_textCursor.x() = 0;
			_textCursor.y() += _textCursor.y() + Font::symbolHeight + 1;
		}
		else
		{
			for (uint16_t glyphY = 0; glyphY < Font::symbolHeight; ++glyphY)
				for (uint16_t glyphX = 0; glyphX < Font::symbolWidth; ++glyphX)
					setPixel(Point{_textCursor.x() + glyphX, _textCursor.y() + glyphY}, Font::fontBit(asciiCharacter, glyphX, glyphY) ? _textColorForeground : _textColorBackground);

			_textCursor.x() += Font::symbolWidth + 1;
		}
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

	static uint16_t pixelAddress(uint16_t x, uint16_t y) {
		return y * Width + x;
	}

private:
	struct FastLedWrapper {
		inline FastLedWrapper() {
			FastLED.addLeds<NEOPIXEL, DataPin>(_screenBuffer, Width * Height);
		}

		CRGB _screenBuffer[NumLeds];
	};

	static FastLedWrapper _fastLedWrapper;
	Color _textColorForeground {10, 10, 10}, _textColorBackground;
	Point _textCursor;
	uint8_t _textSize;
};

template <uint16_t Width, uint16_t Height, uint8_t DataPin, bool Transpose, typename Font>
typename FastLedDisplayPainter<Width, Height, DataPin, Transpose, Font>::FastLedWrapper FastLedDisplayPainter<Width, Height, DataPin, Transpose, Font>::_fastLedWrapper;