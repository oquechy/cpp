#ifndef __LAB_11_EMPLOYEES_H_INCLUDED
#define __LAB_11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <iostream>
#include <fstream>

using namespace std;

class Employee {
    friend istream &operator>>(istream &in, Employee &e);
    friend ostream &operator<<(ostream &out, const Employee &e);
    friend ifstream &operator>>(ifstream &in, Employee &e);
    friend ofstream &operator<<(ofstream &out, const Employee &e);

public:
    Employee() {}
    virtual ~Employee() {}
    virtual void show(ostream &out) const = 0;
    virtual void read(istream &in) = 0;
    virtual void save(ofstream &out) const = 0;
    virtual void load(ifstream &in) = 0;
    virtual int salary() const = 0;
};

class Developer : public Employee {
public:
    Developer();
    ~Developer();
    int salary() const {
        int salary = _base_salary;
        if (_has_bonus) {
            salary += 1000;
        }
        return salary;
    }
private:
    Developer &operator=(const Developer&);
    Developer(const Developer&);
    void show(ostream &out) const;
    void read(istream &in);
    void save(ofstream &out) const;
    void load(ifstream &in);
    char *_name;
    int32_t _base_salary;
    bool _has_bonus;
};

class SalesManager : public Employee {
public:
    SalesManager();
    ~SalesManager();
    int salary() const {
        return (int)(_base_salary + _sold_nm * _price * 0.01);
    }

private:
    SalesManager &operator=(const SalesManager&);
    SalesManager(const SalesManager&);
    void show(ostream &out) const;
    void read(istream &in);
    void save(ofstream &out) const;
    void load(ifstream &in);
    char *_name;
    int32_t _base_salary;
    int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
    void add(const Employee *e);
    int total_salary() const;
    EmployeesArray();
    ~EmployeesArray();
    friend istream &operator>>(istream &in, EmployeesArray &e);
    friend ostream &operator<<(ostream &out, const EmployeesArray &e);
    friend ifstream &operator>>(ifstream &in, EmployeesArray &e);
    friend ofstream &operator<<(ofstream &out, const EmployeesArray &e);

private:
    EmployeesArray &operator=(const EmployeesArray &);
    EmployeesArray(const EmployeesArray &);
    Employee **_employees;
    int _number, _capacity;
};

#endif //__LAB_11_EMPLOYEES_H_INCLUDED
