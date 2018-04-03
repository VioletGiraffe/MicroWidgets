#pragma once

#include "Size.h"

template <class ConcreteWidget>
class Widget
{
public:
	struct Attributes {
		uint8_t frameWidth = 0;
	};

	Widget(const Point& topLeft = Point{ 0, 0 }, const Size& size = Size{ 0, 0 }) : _topLeft(topLeft), _size(size) {}

	const Attributes& attributes() const {
		return _attributes;
	}

	void setAttributes(const Attributes& attrs) {
		_attributes = attrs;
	}

	Point topLeft() const {
		return _topLeft;
	}

	Size size() const {
		return _size;
	}

	uint16_t width() const {
		return _size.width();
	}

	uint16_t height() const {
		return _size.height();
	}

	void update() {
		onDraw();
	}

protected:
	// Events
	void onDraw() {
		onDraw(_size);
	}

	// Polymorphic function - must be redefined by the subclass
	void onDraw(Size regionToUpdate) {
		static_cast<ConcreteWidget*>(this)->onDraw(regionToUpdate);
	}

protected:
	Attributes _attributes;
	Point _topLeft;
	Size _size;
};
