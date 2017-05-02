#ifndef LAB_14_MATRIX_H
#define LAB_14_MATRIX_H

#include <cstddef>
#include <string>
#include <iostream>
#include <fstream>

class MatrixException{
private:
    const std::string err_;
public:
    MatrixException(const std::string &err);
    void print(std::ostream &out);
    const std::string & get();
};

class Matrix{
private:
    int32_t **data_;
    int rows_, cols_;
    bool operator=(const Matrix &m);
    Matrix(const Matrix &m);
public:
    Matrix(std::string fname);
    Matrix(int rows = 0, int cols = 0);
    ~Matrix();
    void load(std::string fname);
    void print();
    void add(const Matrix &m);
    void mul(const Matrix &m);
    void elem(int i, int j);
    void swap(Matrix &m);
};

#endif //LAB_14_MATRIX_H
