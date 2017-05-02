#include "../include/product.h"
#include <cstring>

Product::Product() : name_(new char[1]), quantity_(0), price_(0) {
    name_[0] = 0;
}

Product::Product(const Product &p)
        : name_(new char[strlen(p.name_) + 1]), quantity_(p.quantity_), price_(p.price_) {
    strcpy(name_, p.name_);
}

Product::Product(const char *name, int quantity, double price)
        : name_(new char[strlen(name) + 1]), quantity_(quantity), price_(price) {
    strcpy(name_, name);
}

void Product::swap(Product &p) {
    std::swap(quantity_, p.quantity_);
    std::swap(price_, p.price_);
    char *tmp = name_;
    name_ = p.name_;
    p.name_ = tmp;
}

Product::~Product() {
    delete [] name_;
}

Product& Product::operator=(const Product &p) {
    Product tmp(p);
    swap(tmp);
    return *this;
}

std::ostream &operator<<(std::ostream& out, const Product& p) {
    out << p.name_ << ' ' << p.quantity_ << ' ' << p.price_;
    return out;
}
