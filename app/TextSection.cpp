#include "TextSection.h"


void TextSection::update(const String &newText) const {
    update(newText, &WHITE);
}

void TextSection::update(const String &newText, const RGB *color) const {
    tft->setTextSize(opts.size);
    draw(text, opts.pos, &BLACK);
    newText.toCharArray(text, opts.length);
    draw(text, opts.pos, color);
}

void TextSection::redraw(const RGB *color) const {
    update(String(text), color);
}

void TextSection::draw(const char *text, const Vector position, const RGB *color) const
{
    tft->stroke(color->b, color->g, color->r);
    tft->text(text, position.x, position.y);
}
