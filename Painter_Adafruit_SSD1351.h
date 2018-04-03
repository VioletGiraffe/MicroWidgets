#pragma once

#include "Painter_Adafruit_Base.h"

#include <Adafruit_GFX.h>

#ifndef SSD1351_COLORORDER_RGB // Adafruit_SSD1351.h lacks its own include guard, we're using a macro defined in Adafruit_SSD1351.h as the guard
#include <Adafruit_SSD1351.h>
#endif

class PainterAdafruitSsd1351 : public PainterAdafruitBase<PainterAdafruitSsd1351, Adafruit_SSD1351>
{
public:
	
};