//
// Created by oquechy on 15.04.17.
//

#ifndef HW03_BITSTREAM_H
#define HW03_BITSTREAM_H

#include <fstream>
#include <deque>


static const int MAXS = 1 << 8;

class bitstream{
private:
    void operator=(const bitstream&);
    bitstream(const bitstream&);

protected:
    static const int byte;

    std::fstream file;
    int cur;
    char buf;

    bitstream(std::string filename, std::ios_base::openmode);

public:
    void close();
    explicit operator bool() const;
};

class ibitstream : public bitstream {
protected:
    bool pop();

public:
    ibitstream(std::string filename);
    ibitstream& operator>>(bool &c);
    void seekg(std::streamoff off);
};


class obitstream : public bitstream {
protected:
    void push(bool c);

public:
    obitstream(std::string filename);
    obitstream(std::string filename, std::ios_base::openmode);
    obitstream& operator<<(bool c);
    obitstream& operator<<(std::deque<bool> d);
    ~obitstream();
};

/*
 * #include "bitstream.h"
#include <iostream>

using namespace std;

int main() {
    ibitstream in("in");
    obitstream out("out", ios::app);
    ifstream fin("in", ios::ate);
    int size = (int)fin.tellg();
    bool b;
    deque<bool> d{0, 1, 1, 0, 0, 1, 0, 0};
    out << d;
    for (int i = 0; i < size * 8; ++i) {
        in >> b;
        out << b;
    }
    return 0;
}

 * */

#endif //HW03_BITSTREAM_H
