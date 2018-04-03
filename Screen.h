#pragma once

#include "Widget.h"

// A widget that is the size of the whole screen

template <class ConcretePainter, class ConcreteScreen>
class Screen : public Widget<ConcreteScreen>
{
public:
	Screen() : Widget<ConcreteScreen>(Point{0, 0}, Size{ConcretePainter::screenWidth(), ConcretePainter::screenHeight()})  {
	}

	uint16_t width() const {
		return ConcretePainter::screenWidth();
	}

	uint16_t height() const {
		return ConcretePainter::screenHeight();
	}
};

#define DEFINE_SCREEN(ScreenClassName) template <class ConcretePainter> struct ScreenClassName: public Screen<ConcretePainter, ScreenClassName<ConcretePainter>>