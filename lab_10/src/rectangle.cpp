#include "../include/rectangle.h"

#include "../include/circle.h"
#include <cstdio>
#include <cmath>

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y), width(width), height(height) { }

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, x, y, width, height);
}

bool Rectangle::is_inside(int x, int y) const {
    return (std::abs(x - this->x) <= width / 2 && std::abs(y - this->y) <= height / 2);
}

void Rectangle::zoom(int factor) {
    width *= factor;
    height *= factor;
}
