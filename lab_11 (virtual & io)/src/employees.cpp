#include "../include/employees.h"
#include <string.h>
#include <string>
#include <cstring>

istream &operator>>(istream &in, Employee &e) {
    e.read(in);
    return in;
}

ostream &operator<<(ostream &out, const Employee &e) {
    e.show(out);
    return out;
}

ifstream &operator>>(ifstream &in, Employee &e) {
    e.load(in);
    return in;
}

ofstream &operator<<(ofstream &out, const Employee &e) {
    e.save(out);
    return out;
}

Developer::Developer() :_name(nullptr) {}

Developer::~Developer() {
    delete [] _name;
}

void Developer::show(ostream &out) const {
    out << "Developer\nName: " << _name << "\nBase Salary: " << _base_salary << '\n';
    out << "Has bonus: " << (_has_bonus ? '+' : '-') << '\n';
}

void Developer::read(istream &in) {
    string _buf;
    in >> _buf >> _base_salary >> _has_bonus;
    delete [] _name;
    _name = new char[_buf.size() + 1];
    strcpy(_name, _buf.c_str());
}

void Developer::save(ofstream &out) const {
    int32_t t = 1;
    out.write((char *)&t, 4);
    out.write(_name, strlen(_name) + 1);
    out.write((char *)&_base_salary, 4);
    out.write((char *)&_has_bonus, sizeof(bool));
}

void Developer::load(ifstream &in) {
    char c;
    int i;
    for (i = 0; in.read(&c, 1) && c; ++i);
    ++i;
    in.seekg(-i, in.cur);
    delete [] _name;
    _name = new char[i];
    for (i = 0; in.read(&_name[i], 1) && _name[i]; ++i);
    in.read((char *)&_base_salary, 4);
    in.read((char *)&_has_bonus, sizeof(bool));
}

SalesManager::SalesManager() : _name(nullptr) {}

SalesManager::~SalesManager() {
    delete [] _name;
}

void SalesManager::read(istream &in) {
    string _buf;
    in >> _buf >> _base_salary >> _sold_nm >> _price;
    delete [] _name;
    _name = new char[_buf.size() + 1];
    strcpy(_name, _buf.c_str());
}

void SalesManager::show(ostream &out) const {
    out << "Sales Manager\nName: " << _name << "\nBase Salary: " << _base_salary << '\n';
    out << "Sold items: " << _sold_nm << "\nItem price: " << _price << '\n';
}

void SalesManager::save(ofstream &out) const {
    int32_t t = 2;
    out.write((char *)&t, 4);
    out.write(_name, strlen(_name) + 1);
    out.write((char *)&_base_salary, 4);
    out.write((char *)&_sold_nm, 4);
    out.write((char *)&_price, 4);
}

void SalesManager::load(ifstream &in) {
    char c;
    int i;
    for (i = 0; in.read(&c, 1) && c; ++i);
    ++i;
    in.seekg(-i, in.cur);
    delete [] _name;
    _name = new char[i];
    for (i = 0; in.read(&_name[i], 1) && _name[i]; ++i);
    in.read((char *)&_base_salary, 4);
    in.read((char *)&_sold_nm, 4);
    in.read((char *)&_price, 4);
}

void EmployeesArray::add(const Employee *e) {
    if (_number == _capacity) {
        Employee **_new_employees = new Employee*[2 * _capacity];
        for (int i = 0; i < _number; ++i)
            _new_employees[i] = _employees[i];
        _capacity *= 2;
        std::swap(_new_employees, _employees);
        delete []_new_employees;
    }
    _employees[_number++] = (Employee *)e;
}

int EmployeesArray::total_salary() const {
    int total = 0;
    for (int i = 0; i < _number; ++i)
        total += _employees[i]->salary();
    cout << "== Total salary: " << total << "\n\n";
    return total;
}

EmployeesArray::EmployeesArray()
        : _number(0), _capacity(1), _employees(new Employee*[1]) {}

EmployeesArray::~EmployeesArray() {
    for (int i = 0; i < _number; ++i)
        delete _employees[i];
    delete []_employees;
}

istream &operator>>(istream &in, EmployeesArray &employees) {
    int type;
    cin >> type;
    Employee *e;
    if (type == 1)
        e = (new Developer);
    else
        e = (new SalesManager);
    cin >> *e;
    employees.add(e);
    return in;
}

ostream &operator<<(ostream &out, const EmployeesArray &employees) {
    for (int i = 0; i < employees._number; ++i)
        cout << i + 1 << ". " << *employees._employees[i];
    return out;
}

ifstream &operator>>(ifstream &in, EmployeesArray &employees) {
    int32_t cnt;
    in.read((char *)&cnt, 4);
    for (int i = 0; i < (int)cnt; ++i) {
        int32_t type;
        in.read((char *)&type, 4);
        Employee *e = (type == 1 ? (Employee *)(new Developer) : (Employee *)(new SalesManager));
        in >> *e;
        employees.add(e);
    }
    return in;
}

ofstream &operator<<(ofstream &out, const EmployeesArray &employees) {
    out.write((char *)&employees._number, 4);
    for (int i = 0; i < employees._number; ++i) {
        out << *employees._employees[i];
    }
    return out;
}
