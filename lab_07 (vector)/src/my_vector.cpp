#include <cstddef>
#include <cassert>
#include <algorithm>
#include "my_vector.h"

MyVector::MyVector() {
    _sz = 0;
    _cp = 2;
    _data = new int[2];
}

MyVector::MyVector(size_t init_capacity) {
    assert(init_capacity >= 0);
    _sz = 0;
    _cp = init_capacity;
    _data = new int[_cp];
}

MyVector::~MyVector() {
   delete []_data;
}

void MyVector::set(std::size_t index, int value) {
    assert(0 <= index && index <= _sz);
    _data[index] = value;
}

int MyVector::get(std::size_t index) {
    assert(0 <= index && index < _sz);
    return _data[index];
}

std::size_t MyVector::size() {
    return _sz;
}

std::size_t MyVector::capacity() {
    return _cp;
}

void MyVector::reserve(std::size_t new_capacity) {
    assert(new_capacity);
    if (_cp < new_capacity) {
        int *_nd = new int[new_capacity];
        for (int i = 0; i < (int)_sz; ++i)
            _nd[i] = _data[i];
        _cp = new_capacity;
        std::swap(_nd, _data);
        delete []_nd;       
    }    
}

void MyVector::push_back(int value) {
    if (_sz == _cp)
        reserve(_cp * 2);
    _data[_sz++] = value;
}
 
void MyVector::resize(std::size_t new_size) {
    while (_sz < new_size) 
        push_back(0);
    _sz = new_size;
}

void MyVector::insert(std::size_t index, int value) {
    assert(index >= 0);
    while (_sz < index)
        push_back(0);
    push_back(value);
    if (index < _sz)
        for (int i = index; i < (int)_sz; ++i)
            std::swap(_data[i], _data[_sz - 1]);    
}

void MyVector::erase(std::size_t index) {
    if (0 <= index && index < _sz) {
        for (int i = index; i < (int)_sz - 1; ++i)
            std::swap(_data[i], _data[i + 1]);  
        --_sz; 
    }
}

