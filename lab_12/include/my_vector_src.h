#ifndef LAB_12_MY_VECTOR_SRC_H
#define LAB_12_MY_VECTOR_SRC_H

#include "../include/my_vector.h"

template <class T>
my_vector<T>::my_vector() : capacity_(1), size_(0), array_((T*)new char[sizeof(T)]) {}

size_t next_pow(size_t n) {
    size_t i;
    for (i = 1; i < n; i *= 2);
    return i;
}

template <class T>
my_vector<T>::my_vector(size_t n)
        : capacity_(next_pow(n)), size_(n), array_((T*)new char[sizeof(T) * next_pow(n)]) {
    for(int i = 0; i < n; ++i)
        new (&array_[i]) T();
}

template<class T>
my_vector<T>::my_vector(const my_vector &v)
        : size_(v.size_), capacity_(next_pow(v.size_)), array_((T*)new char[sizeof(T) * capacity_]) {
    for (int i = 0; i < size_; i++)
        new (&array_[i]) T(v.array_[i]);
}

template<class T>
my_vector<T>& my_vector<T>::operator=(const my_vector<T> &v) {
    my_vector tmp(v);
    swap(tmp);
    return *this;
}

template<class T>
my_vector<T>::~my_vector() {
    for (int i = 0; i < size_; ++i)
        array_[i].~T();
    delete [] (char*)array_;
}

template<class T>
size_t my_vector<T>::size() const {
    return size_;
}

template<class T>
size_t my_vector<T>::capacity() const {
    return capacity_;
}

template<class T>
bool my_vector<T>::empty() const {
    return (size_ == 0);
}

template<class T>
void my_vector<T>::reserve(size_t n) {
    size_t new_capacity = next_pow(n);
    if (capacity_ >= new_capacity)
        return;
    T* new_array((T*)new char[sizeof(T) * new_capacity]);
    for (int i = 0; i < size_; ++i) {
        new(&new_array[i]) T(array_[i]);
        array_[i].~T();
    }
    delete [] (char *)array_;
    array_ = new_array;
    capacity_ = new_capacity;
}

template<class T>
void my_vector<T>::resize(size_t n) {
    reserve(n);
    for (int i = (int)size_; i < n; ++i)
        new (&array_[i]) T();
    size_ = n;
}

template<class T>
void my_vector<T>::swap(my_vector<T> &v) {
    std::swap(capacity_, v.capacity_);
    std::swap(size_, v.size_);
    T* tmp = array_;
    array_ = v.array_;
    v.array_ = tmp;
}

template<class T>
T & my_vector<T>::operator[](size_t index) {
    return array_[index];
}

template<class T>
const T & my_vector<T>::operator[](size_t index) const {
    return array_[index];
}

template<class T>
void my_vector<T>::push_back(const T &t) {
    if (size_ == capacity_)
        reserve(2 * capacity_);
    new (&array_[size_++]) T(t);
    //array_[size_++] = t;
}

template<class T>
void my_vector<T>::pop_back() {
    array_[--size_].~T();
}

template<class T>
void my_vector<T>::clear() {
    for (int i = 0; i < size_; ++i)
        array_[i].~T();
    size_ = 0;
}

template<class T>
std::ostream &operator<<(std::ostream& out, const my_vector<T> &v) {
    if (!v.size_)
        return out;
    for (int i = 0; i < v.size_ - 1; ++i)
        out << v.array_[i] << ' ';
    out << v.array_[v.size_ - 1];
    return out;
}

#endif //LAB_12_MY_VECTOR_SRC_H
