//
// Created by oquechy on 15.04.17.
//

#include "bitstream.h"

using namespace std;

// bitstream

const int bitstream::byte = 8;

bitstream::bitstream(string filename, ios_base::openmode mode)
        : file(filename, ios::binary | mode), buf(0)
{}

void bitstream::close() {
    file.close();
}

bitstream::operator bool() const {
        return !file.fail();
}

// ibitstream

ibitstream::ibitstream(std::string filename)
        : bitstream(filename, std::ios::in)
{
    cur = -1;
}

bool ibitstream::pop() {
    return static_cast<bool>(buf & (1 << cur--));
}

ibitstream& ibitstream::operator>>(bool &c) {
    if (cur < 0) {
        file.read(&buf, sizeof(buf));
        cur = byte - 1;
    }
    c = pop();
    return *this;
}

void ibitstream::seekg(std::streamoff off) {
    file.seekg(off);
}

// obitstream

obitstream::obitstream(std::string filename)
        : bitstream(filename, ios::out)
{
    cur = byte - 1;
}

obitstream::obitstream(std::string filename, std::ios_base::openmode mode)
        : bitstream(filename, ios::out | mode)
{
    cur = byte - 1;
}

void obitstream::push(bool c) {
    buf |= (c << cur--);
}

obitstream& obitstream::operator<<(bool c) {
    push(c);
    if (cur < 0) {
        file.write(&buf, sizeof(buf));
        buf = 0;
        cur = byte - 1;
    }
    return *this;
}

obitstream& obitstream::operator<<(std::deque<bool> d) {
    for (bool b : d)
        *this << b;
    return *this;
}

obitstream::~obitstream() {
    if (cur != byte - 1)
        file.write(&buf, sizeof(buf));
}
