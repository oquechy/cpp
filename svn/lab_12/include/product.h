#ifndef LAB_12_PRODUCT_H
#define LAB_12_PRODUCT_H

#include <fstream>

class Product {
public:
    Product();
    Product(const Product &p);
    Product(const char* name, int quantity, double price);
    ~Product();
    Product &operator=(const Product &p);

    void swap(Product &p);

    friend std::ostream &operator<<(std::ostream& out, const Product& p);

private:
    char *name_;
    int quantity_;
    double price_;
};

std::ostream &operator<<(std::ostream& out, const Product& p);

#endif //LAB_12_PRODUCT_H
