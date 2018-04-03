#pragma once

#include "Painter.h"

#include <utility>

template <class ConcretePainter, class DisplayType>
class PainterAdafruitBase : public DisplayPainter<ConcretePainter, DisplayType>
{
	using Parent = DisplayPainter<ConcretePainter, DisplayType>;
public:
	void rect(const Point& topLeft, const Size& size, const Color& color) {
		Parent::_displayInstance->drawRect(topLeft.x(), topLeft.y(), size.width(), size.height(), color.toRgb565());
	}

	void rect(const Point& topLeft, const Point& bottomRight, const Color& color) {
		Parent::_displayInstance->drawRect(topLeft.x(), topLeft.y(), bottomRight.x() - topLeft.x(), bottomRight.y() - topLeft.y(), color.toRgb565());
	}

	void fillRect(const Point& topLeft, const Size& size, const Color& color) {
		Parent::_displayInstance->fillRect(topLeft.x(), topLeft.y(), size.width(), size.height(), color.toRgb565());
	}

	void fillRect(const Point& topLeft, const Point& bottomRight, const Color& color) {
		Parent::_displayInstance->fillRect(topLeft.x(), topLeft.y(), bottomRight.x() - topLeft.x(), bottomRight.y() - topLeft.y(), color.toRgb565());
	}

	void fillScreen(const Color& color) {
		Parent::_displayInstance->fillScreen(color.toRgb565());
	}

	void setPixel(const Point& pixel, const Color& color) {
		Parent::_displayInstance->drawPixel(pixel.x(), pixel.y(), color.toRgb565());
	}

	void setPixel(uint16_t x, uint16_t y, const Color& color) {
		setPixel(Point{x, y}, color);
	}

	void drawFastVLine(const Point& start, uint16_t height, const Color& color) {
		Parent::_displayInstance->drawFastVLine(start.x(), start.y(), height, color.toRgb565());
	}

    void drawFastHLine(const Point& start, uint16_t width, const Color& color) {
		Parent::_displayInstance->drawFastHLine(start.x(), start.y(), width, color.toRgb565());
	}

    void drawLine(const Point& start, const Point& end, const Color& color) {
		Parent::_displayInstance->drawLine(start.x(), start.y(), end.x(), end.y(), color.toRgb565());
	}

	void setCursor(const Point& pos) {
		Parent::_displayInstance->setCursor(pos.x(), pos.y());
	}

    void setTextColor(const Color& color) {
		Parent::_displayInstance->setTextColor(color.toRgb565());
	}

    void setTextColor(const Color& c, const Color& bg) {
		Parent::_displayInstance->setTextColor(c.toRgb565, bg.toRgb565());
	}

    void setTextSize(uint8_t s) {
		Parent::_displayInstance->setTextSize(s);
	}

    void setTextWrap(bool w) {
		Parent::_displayInstance->setTextWrap(w);
	}

	template <typename ...Args>
	void print(Args&&... args) {
		Parent::_displayInstance->print(std::forward<Args>(args)...);
	}

	static uint16_t screenWidth() {
		return static_cast<uint16_t>(Parent::_displayInstance->width());
	}

	static uint16_t screenHeight() {
		return static_cast<uint16_t>(Parent::_displayInstance->height());
	}
};