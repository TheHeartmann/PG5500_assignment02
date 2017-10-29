#pragma once

#include "Arduino.h"
#include <TFT.h>
#include <RTClib.h>
#include "TextOptions.h"
#include "RGB.h"


class TextSection {
public:
  TextSection(TFT &tft, const TextOptions opts, char *buffer) : tft(tft), opts(opts), text(buffer){}
  void update(const String *newText);

private:
  void draw(const char *text, const Vector pos, const RGB color) const;
  char *text;
  const TextOptions opts;
  TFT &tft;
};