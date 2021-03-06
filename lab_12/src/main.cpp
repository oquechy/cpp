#include <iostream>

#include "../include/my_vector.h"
#include "../include/product.h"
#include "../include/test.h"

void print(const my_vector<Product>& v) {
    std::cout << v << std::endl;
}

int main() {
    test_my_vector<int>(5, 10);
    test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));
    return 0;
}
