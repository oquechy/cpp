#ifndef LAB_12_TEST_SRC_H
#define LAB_12_TEST_SRC_H

#include <iostream>
#include "my_vector_src.h"

template<class T>
void test_my_vector(T t1, T t2) {

    my_vector<T> v1;
    std::cout << "1. default vector: " << v1 << \
    "\n   size: " << v1.size() << \
    "\n   capacity: " << v1.capacity() << "\n\n";
    if (v1.size() != 0)
        std::cout << "! wrong size !\n";
    if (v1.capacity() != 1)
        std::cout << "! wrong capacity !\n\n";


    for (int i = 0; i < 10; ++i)
        v1.push_back(t1);
    std::cout << "2. after push: " << v1 << \
    "\n   size: " << v1.size() << \
    "\n   capacity: " << v1.capacity() << \
    "\n   5-th element: " << v1[4] << "\n\n";
    if (v1.size() != 10)
        std::cout << "! wrong size !\n";
    if (v1.capacity() != 16)
        std::cout << "! wrong capacity !\n";


    my_vector<T> v2(v1);
    v2[4] = t2;
    std::cout << "3. copied vector: " << v2 << \
    "\n   size: " << v2.size() << \
    "\n   capacity: " << v2.capacity() << \
    "\n   changed 5-th element: " << v2[4] << "\n\n";
    if (v2.size() != 10)
        std::cout << "! wrong size !\n";
    if (v2.capacity() != 16)
        std::cout << "! wrong capacity !\n\n";


    for (int i = 0; i < 3; ++i)
        v2.pop_back();
    std::cout << "4. after pop: " << v2 << \
    "\n   size: " << v2.size() << \
    "\n   capacity: " << v2.capacity() << "\n\n";
    if (v2.size() != 7)
        std::cout << "! wrong size !\n";
    if (v1.capacity() != 16)
        std::cout << "! wrong capacity !\n\n";


    v1.clear();
    std::cout << "5. empty vector: " << v1 << \
    "\n   size: " << v1.size() << \
    "\n   capacity: " << v1.capacity() << "\n\n";
    if (v1.size() != 0)
        std::cout << "! wrong size !\n";
    if (v1.capacity() != 16)
        std::cout << "! wrong capacity !\n";
    if (!v1.empty())
        std::cout << "! wrong emptyness !\n\n";


    for (int i = 0; i < 10; ++i)
        v2.push_back(t2);
    v2 = v1;
    std::cout << "6. equal vector: " << v2 << \
    "\n   size: " << v2.size() << \
    "\n   capacity: " << v2.capacity() << "\n\n";
    if (v2.size() != 0)
        std::cout << "! wrong size !\n";
    if (v2.capacity() != 1)
        std::cout << "! wrong capacity !\n\n";


    my_vector<T> v3(10);
    std::cout << "7. 10-elements vector: " << v3 << \
    "\n   size: " << v3.size() << \
    "\n   capacity: " << v3.capacity() << "\n\n";
    if (v3.size() != 10)
        std::cout << "! wrong size !\n";
    if (v3.capacity() != 16)
        std::cout << "! wrong capacity !\n\n";


    v3.resize(80);
    std::cout << "8. resized vector: " << v3 << \
    "\n   size: " << v3.size() << \
    "\n   capacity: " << v3.capacity() << "\n\n";
    if (v3.size() != 80)
        std::cout << "! wrong size !\n";
    if (v3.capacity() != 128)
        std::cout << "! wrong capacity !\n\n";


    v1.reserve(180);
    std::cout << "9. reserved vector: " << v1 << \
    "\n   size: " << v1.size() << \
    "\n   capacity: " << v1.capacity() << "\n\n";
    if (v1.size() != 0)
        std::cout << "! wrong size !\n";
    if (v1.capacity() != 256)
        std::cout << "! wrong capacity !\n\n";

    const my_vector<T> v4(10);
    std::cout << "10. const vector: " << v4 << \
    "\n   size: " << v4.size() << \
    "\n   capacity: " << v4.capacity() << \
    "\n   5-th element: " << v4[4] << "\n\n";
    if (v1.size() != 0)
        std::cout << "! wrong size !\n";
    if (v1.capacity() != 256)
        std::cout << "! wrong capacity !\n\n";

}

#endif //LAB_12_TEST_SRC_H
