#ifndef LAB_12_MY_VECTOR_H
#define LAB_12_MY_VECTOR_H

#include <cstddef>
#include <ostream>

template <class T>
class my_vector{
public:
    my_vector();
    my_vector(size_t n);
    my_vector(const my_vector& other);
    my_vector& operator=(const my_vector& other);
    ~my_vector();

    size_t size() const;
    size_t capacity() const;
    bool empty() const;

    void resize(size_t n);
    void reserve(size_t n);
    void swap(my_vector<T> &v);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    void push_back(const T& t);
    void pop_back();
    void clear();

    template<class C>
    friend std::ostream &operator<<(std::ostream& out, const my_vector<C> &v);

private:
    size_t capacity_;
    size_t size_;
    T* array_;
};

template<class T>
std::ostream &operator<<(std::ostream& out, const my_vector<T> &v);

#include "my_vector_src.h"

#endif //LAB_12_MY_VECTOR_H
