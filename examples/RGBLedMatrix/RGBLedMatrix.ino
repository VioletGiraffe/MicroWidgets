#include <FastLED.h>
#include <MicroWidgets.h>
#include <Painter_FastLED.hpp>

constexpr auto DATA_PIN = 19;

void setup()
{
	FastLedDisplayPainter<8, 8, DATA_PIN> painter;
	painter.drawLine(Point{1, 0}, Point (4, 7), Color(0, 1, 1));
	painter.rect(Point{2, 0}, Point (4, 2), Color(1, 0, 0));
	painter.fillRect(Point{4, 3}, Point (6, 5), Color(0, 1, 0));
}

void loop()
{
}
