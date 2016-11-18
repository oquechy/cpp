#include "../include/matrix.h"
#include <algorithm>

Matrix::Matrix(std::size_t r, std::size_t c) : _rows(r), _cols(c) {
    _data = new int *[r];
    for (size_t i = 0; i < r; ++i)
        _data[i] = new int[c]();
}

Matrix::Matrix(const Matrix& m) : _rows(m._rows), _cols(m._cols)  {
    _data = new int *[_rows];
    for(size_t i = 0; i < _rows; ++i) {
        _data[i] = new int[_cols]();
        for(size_t j = 0; j < _cols; ++j)
            _data[i][j] = m._data[i][j];
    }
}

Matrix::~Matrix() {
    for (size_t i = 0; i < _rows; ++i)
        delete [] _data[i];
    delete [] _data;
}

Matrix& Matrix::operator=(const Matrix& m) {
    Matrix n(m);
    n.swap(*this);
    return *this;
}

void Matrix::swap(Matrix &m){
    std::swap(_data, m._data);
    std::swap(_rows, m._rows);
    std::swap(_cols, m._cols);
}

std::size_t Matrix::get_rows() const { return _rows; }
std::size_t Matrix::get_cols() const { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
  return _data[i][j];
}

void Matrix::print(FILE *f) const {
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j)
            fprintf(f, "%d ", _data[i][j]);
        fprintf(f, "\n");
    }
}

bool Matrix::operator==(const Matrix& m) {
    bool res(_rows == m._rows && _cols == m._cols);
    if (res) {
        for(size_t i = 0; i < _rows; ++i)
            for(size_t j = 0; j < _cols; ++j)
                res &= _data[i][j] == m._data[i][j];
    }
    return res;
}

bool Matrix::operator!=(const Matrix& m) {
    return !(*this == m);
}

Matrix& Matrix::operator+=(const Matrix& m) {
    for(size_t i = 0; i < _rows; ++i)
        for(size_t j = 0; j < _cols; ++j)
            _data[i][j] += m._data[i][j];
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
    for(size_t i = 0; i < _rows; ++i)
        for(size_t j = 0; j < _cols; ++j)
            _data[i][j] -= m._data[i][j];
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
    return (*this = *this * m);
}

Matrix Matrix::operator+(const Matrix& m) const {
    Matrix n(*this);
    n += m;
    return n;
}

Matrix Matrix::operator-(const Matrix& m) const {
    Matrix n(*this);
    n -= m;
    return n;
}

Matrix Matrix::operator*(const Matrix& m) const {
    Matrix n(_rows, m._cols);
    for(size_t i = 0; i < _rows; ++i)
        for(size_t j = 0; j < m._cols; ++j)
            for(size_t q = 0; q < _cols; ++q)
                n._data[i][j] += _data[i][q] * m._data[q][j];
    return n;
}
