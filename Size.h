#pragma once

#include <stdint.h>

class Size
{
public:
	inline explicit constexpr Size(uint16_t w = 0, uint16_t h = 0) : _w(w), _h(h) {}

	inline uint16_t width() const {
		return _w;
	}

	inline uint16_t height() const {
		return _h;
	}

private:
	uint16_t _w = 0, _h = 0; // 16K resolution ought to be enough for anybody
};


class Point
{
public:
	inline explicit constexpr Point(uint16_t x = 0, uint16_t y = 0) : _x(x), _y(y) {}

	inline uint16_t x() const {
		return _x;
	}

	inline uint16_t y() const {
		return _y;
	}

	inline Point operator+(const Size& s) const {
		return Point{_x + s.width(), _y + s.height()};
	}

	inline Point operator-(const Size& s) const {
		return Point{_x - s.width(), _y - s.height()};
	}

	inline Point operator+(const uint16_t offset) const {
		return Point{_x + offset, _y + offset};
	}

	inline Point operator-(const uint16_t offset) const {
		return *this + (-offset);
	}

	inline Size operator-(const Point& other) const {
		return Size{_x - other._x, _y - other._y};
	}

	

private:
	uint16_t _x = 0, _y = 0; // 16K resolution ought to be enough for anybody
};