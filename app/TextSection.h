#pragma once

#include "Arduino.h"
#include <TFT.h>
#include <RTClib.h>
#include "TextOptions.h"
#include "RGB.h"


class TextSection {
public:
  TextSection(TFT &tft, const TextOptions opts, char *buffer) : tft(tft), opts(opts), text(buffer){}
  void write(const char *newText);
  void update(const String *newText);

private:
  void changeDisplayText(const char *newText) const;
  void draw(const char *text, const Vector pos, const RGB color) const;
  char *text;
  const TextOptions opts;
  TFT &tft;
};