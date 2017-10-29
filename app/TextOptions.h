#pragma once

#include "Vector.h"

struct TextOptions {
    Vector pos;
    short size;
    short length;

    TextOptions& operator=(const TextOptions &other) {
        pos = other.pos;
        size = other.size;
        length = other.length;
        return *this;
    }
};