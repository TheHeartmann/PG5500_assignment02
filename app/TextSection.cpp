#include "TextSection.h"

void TextSection::update(const String *newText) {
    tft.setTextSize(opts.size);
    draw(text, opts.pos, BLACK);
    newText->toCharArray(text, opts.length);
    draw(text, opts.pos, WHITE);
}

void TextSection::draw(const char *text, const Vector position, RGB color) const
{
    tft.stroke(color.r, color.g, color.b);
    tft.text(text, position.x, position.y);
}
