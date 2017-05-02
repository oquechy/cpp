#include "../include/employees.h"
#include <string>
#include <cstring>

int main() {
    string mode;
    EmployeesArray employees;
    while (cin >> mode) {
        //cerr << mode << '\n';
        if (mode == "add") {
            cin >> employees;
        } else if (mode == "list") {
            cout << employees;
            employees.total_salary();
        } else if (mode == "load") {
            string file;
            cin >> file;
            ifstream in(file, ifstream::binary);
            in >> employees;
            in.close();
        } else if (mode == "save") {
            string file;
            cin >> file;
            ofstream out(file, ofstream::binary);
            out << employees;
            out.close();
        } else if (mode == "exit") {
            return 0;
        } else {
            cout << "Unknown command\n";
        }
    }
}