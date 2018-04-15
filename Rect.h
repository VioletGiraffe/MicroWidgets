#pragma once

#include "Size.h"

class Rect {
public:
	inline Rect() = default;
	inline explicit constexpr Rect(const Size& s): _size(s) {}
	inline explicit constexpr Rect(const Point& topLeft, const Size& s): _topLeft(topLeft), _size(s) {}

	inline Point topLeft() const {
		return _topLeft;
	}

	inline Size size() const {
		return _size;
	}

	Point bottomRight() const {
		return _topLeft + _size;
	}

	inline auto width() const {
		return _size.width();
	}

	inline auto height() const {
		return _size.height();
	}

private:
	Point _topLeft;
	Size _size;
};