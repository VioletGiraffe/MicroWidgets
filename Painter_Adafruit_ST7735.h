#pragma once

#include "Painter_Adafruit_Base.h"

#include <Adafruit_GFX.h>
#ifndef ST7735_BLACK // Adafruit headers lack an include guard
#include <Adafruit_ST7735.h>
#endif


class PainterAdafruitST7735 : public PainterAdafruitBase<PainterAdafruitST7735, Adafruit_ST7735>
{
public:
	
};