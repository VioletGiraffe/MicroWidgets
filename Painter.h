#pragma once

#include "Size.h"
#include "Color.h"

template <class ConcreteImplementation>
class AbstractPainter
{
public:
	void rect(const Point& topLeft, const Size& size, const Color& color) {
		static_cast<ConcreteImplementation&>(*this).rect(topLeft, size, color);
	}

	void rect(const Point& topLeft, const Point& bottomRight, const Color& color) {
		static_cast<ConcreteImplementation&>(*this).rect(topLeft, bottomRight, color);
	}

	void fillRect(const Point& topLeft, const Size& size, const Color& color) {
		static_cast<ConcreteImplementation&>(*this).fillRect(topLeft, size, color);
	}

	void fillRect(const Point& topLeft, const Point& bottomRight, const Color& color) {
		static_cast<ConcreteImplementation&>(*this).fillRect(topLeft, bottomRight, color);
	}

	void setPixel(const Point& pixel, const Color& color) {
		static_cast<ConcreteImplementation&>(*this).setPixel(pixel, color);
	}

	void setPixel(uint16_t x, uint16_t y, const Color& color) {
		setPixel(Point{x, y}, color);
	}
};

template <class ConcreteImplementation, class DisplayType>
class DisplayPainter : public AbstractPainter<ConcreteImplementation>
{
public:
	uint16_t screenWidth() const {
		return static_cast<const ConcreteImplementation&>(*this).screenWidth();
	}

	uint16_t screenHeight() const {
		return static_cast<const ConcreteImplementation&>(*this).screenHeight();
	}

	void fillScreen(const Color& color) {
		static_cast<ConcreteImplementation&>(*this).fillScreen();
	}

	static void setDisplayInstance(DisplayType& instance) {
		_displayInstance = &instance;
	}

protected:
	static DisplayType* _displayInstance;
};

template <class ConcreteImplementation, class DisplayType>
DisplayType* DisplayPainter<ConcreteImplementation, DisplayType>::_displayInstance = nullptr;
