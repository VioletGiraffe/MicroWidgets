#pragma once

#include "Rect.h"

template <class ConcreteWidget>
class Widget
{
public:
	struct Attributes {
		uint8_t frameWidth = 0;
	};

	inline constexpr Widget() {}
	inline explicit constexpr Widget(const Rect& rect = Rect()) : _rect(rect) {}
	inline explicit constexpr Widget(const Point& topLeft, const Size& size) : _rect(topLeft, size) {}

	const Attributes& attributes() const {
		return _attributes;
	}

	void setAttributes(const Attributes& attrs) {
		_attributes = attrs;
	}

	inline Point topLeft() const {
		return _rect.topLeft();
	}

	inline Size size() const {
		return _rect.size();
	}

	inline uint16_t width() const {
		return _rect.width();
	}

	inline uint16_t height() const {
		return _rect.height();
	}

	void update() {
		onDraw();
	}

protected:
	// Events
	void onDraw() {
		onDraw(_rect);
	}

	// Polymorphic function - must be redefined by the subclass
	void onDraw(Rect updateRect, Rect excludeRect = Rect()) {
		static_cast<ConcreteWidget*>(this)->onDraw(updateRect, excludeRect);
	}

protected:
	Attributes _attributes;
	Rect _rect;
};
