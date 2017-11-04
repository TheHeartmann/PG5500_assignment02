#pragma once

struct RGB {
    byte r;
    byte g;
    byte b;

    RGB& operator=(const RGB& other){
        r = other.r;
        g = other.g;
        b = other.b;
        return *this;
    }
};

const RGB BLACK = RGB{0, 0, 0};
const RGB WHITE = RGB{255, 255, 255};
const RGB GREEN = RGB{124, 252, 0};
const RGB RED = RGB{ 255, 0, 0 };
const RGB ORANGE = RGB{ 255, 171, 0 };
const RGB GRAY = RGB{ 128, 128, 128 };
