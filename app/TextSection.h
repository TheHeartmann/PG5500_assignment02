#pragma once

#include "Arduino.h"
#include <TFT.h>
#include "TextOptions.h"
#include "RGB.h"


class TextSection {
public:
  TextSection() {}
  TextSection(TFT &tft, const TextOptions opts, char *buffer) : tft(&tft), opts(opts), text(buffer) {}
  void update(const String *newText);
  void update(const String *newText, const RGB *color);
  TextSection& operator=(const TextSection &other) {
      tft = other.tft;
      opts = other.opts;
      text = other.text;
      return *this;
  }

private:
  void draw(const char *text, const Vector pos, const RGB *color) const;
  char *text;
  TextOptions opts;
  TFT *tft;
};