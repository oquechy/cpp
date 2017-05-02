#include "matrix.h"

using namespace std;

// MatrixException

MatrixException::MatrixException(const std::string &err)
        : err_(err)
{}

void MatrixException::print(ostream &out) {
    out << err_ << '\n';
}

const std::string& MatrixException::get() {
    return err_;
}

// Matrix
/*
Matrix::Matrix()
        : data_(nullptr)
        , rows_(0)
        , cols_(0)
{}
*/

Matrix::Matrix(std::string fname) {
    ifstream in(fname);
    in >> rows_ >> cols_;
    data_ = new int32_t*[rows_];
    for (int i = 0; i < rows_; ++i)
        data_[i] = new int32_t[cols_];
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            in >> data_[i][j];
}

Matrix::Matrix(int rows, int cols)
        : data_(new int32_t*[rows])
        , rows_(rows)
        , cols_(cols)
{
    for (int i = 0; i < rows; ++i)
        data_[i] = new int32_t[cols]();
}

Matrix::~Matrix() {
    for (int i = 0; i < rows_; ++i)
        delete [] data_[i];
    delete [] data_;
}

void Matrix::load(std::string fname) {
    Matrix tmp(fname);
    swap(tmp);
}

void Matrix::print() {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j)
            cout << data_[i][j] << ' ';
        cout << '\n';
    }
}

void Matrix::add(const Matrix &m) {
    if (rows_ != m.rows_ || cols_ != m.cols_)
        throw MatrixException("ADD: dimensions do not match.");
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            data_[i][j] += m.data_[i][j];
}

void Matrix::mul(const Matrix &m) {
    if (cols_ != m.rows_)
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    Matrix tmp(rows_, m.cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < m.cols_; ++j)
            for (int q = 0; q < cols_; ++q)
                tmp.data_[i][j] += data_[i][q] * m.data_[q][j];
    swap(tmp);
}

void Matrix::swap(Matrix &m) {
    std::swap(rows_, m.rows_);
    std::swap(cols_, m.cols_);
    int32_t **tmp = data_;
    data_ = m.data_;
    m.data_ = tmp;
}

void Matrix::elem(int i, int j) {
    if (i < 0 || rows_ <= i || j < 0 || cols_ <= j)
        throw MatrixException("ACCESS: bad index.");
    cout << data_[i][j] << '\n';
}
