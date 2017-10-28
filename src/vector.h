struct Vector {
    short x;
    short y;

    Vector& operator=(const Vector& other){
        x = other.x;
        y = other.y;
        return *this;
    }

    Vector operator-(const Vector& other) const {
        return {x - other.x, y - other.y};
    }

    Vector operator+(const Vector& other) const {
        return {x + other.x, y + other.y};
    }
};