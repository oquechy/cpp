#include <cstddef>
#include <cassert>

template<typename T, std::size_t N>
class my_array {
private:
    T array_[N];

public:
    T& at(std::size_t index);
    const T& at(std::size_t index) const;
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    bool empty() const;
    std::size_t size() const;

    void fill(const T& val);
};

template<typename T, std::size_t N>
T& my_array<T, N>::operator[](std::size_t index) {
    return array_[index];
}
template<typename T, std::size_t N>
const T& my_array<T, N>::operator[](std::size_t index) const {
    return array_[index];
}

template<typename T, std::size_t N>
T& my_array<T, N>::at(std::size_t index) {
    assert(0 <= index && index < N);
    return array_[index];
}

template<typename T, std::size_t N>
const T& my_array<T, N>::at(std::size_t index) const {
    assert(0 <= index && index < N);
    return array_[index];
}

template<typename T, std::size_t N>
bool my_array<T, N>::empty() const {
    return (N == 0);
}

template<typename T, std::size_t N>
std::size_t my_array<T, N>::size() const {
    return N;
}

template<typename T, std::size_t N>
void my_array<T, N>::fill(const T& val) {
    for (int i = 0; i < (int)N; ++i)
        array_[i] = val;
}

template<std::size_t N>
class my_array<bool, N> {
private:
    char array_[(N + 7) / 8];
    static std::size_t size_;
    std::size_t get_index(std::size_t index) const;
    std::size_t get_offset(std::size_t index) const;

    class my_proxy{
        friend class my_array<bool, N>;
    private:
        char &position_;
        std::size_t offset_;
        bool get_value() const;
    public:
        my_proxy(char &position, std::size_t offset);
        operator bool() const;
        my_proxy& operator=(bool value);
        my_proxy& operator=(const my_proxy& proxy);
    };

public:
    my_proxy at(std::size_t index);
    bool at(std::size_t index) const;
    my_proxy operator[](std::size_t index);
    bool operator[](std::size_t index) const;

    bool empty() const;
    std::size_t size() const;

    void fill(bool val);
};

// proxy

template<std::size_t N>
bool my_array<bool, N>::my_proxy::get_value() const {
    return (bool)((position_ >> offset_) & 1);
}

template<std::size_t N>
my_array<bool, N>::my_proxy::my_proxy(char &position, std::size_t offset)
        : position_(position)
        , offset_(offset)
{}

template<std::size_t N>
my_array<bool, N>::my_proxy::operator bool() const {
    return get_value();
}

template<std::size_t N>
typename my_array<bool, N>::my_proxy& my_array<bool, N>::my_proxy::operator=(bool x) {
    if (x)
        position_ |= (1 << offset_);
    else
        position_ &= ~(1 << offset_);
    return *this;
}

template<std::size_t N>
typename my_array<bool, N>::my_proxy& my_array<bool, N>::my_proxy::operator=(const my_proxy &proxy) {
    return operator=(bool(proxy));
}

// array<bool>

template<std::size_t N>
std::size_t my_array<bool, N>::size_ = (N + 7) / 8;

template<std::size_t N>
std::size_t my_array<bool, N>::get_index(std::size_t index) const {
    return index / 8;
}

template<std::size_t N>
std::size_t my_array<bool, N>::get_offset(std::size_t index) const {
    return index % 8;
}

template<std::size_t N>
typename my_array<bool, N>::my_proxy my_array<bool, N>::operator[](std::size_t index) {
    return my_proxy(array_[get_index(index)], get_offset(index));
}

template<std::size_t N>
bool my_array<bool, N>::operator[](std::size_t index) const {
    return (bool)((array_[get_index(index)] >> get_offset(index)) & 1);
}

template<std::size_t N>
typename my_array<bool, N>::my_proxy my_array<bool, N>::at(std::size_t index) {
    assert(0 <= index && index < N);
    return operator[](index);
}

template<std::size_t N>
bool my_array<bool, N>::at(std::size_t index) const {
    assert(0 <= index && index < N);
    return operator[](index);
}

template<std::size_t N>
bool my_array<bool, N>::empty() const {
    return (N == 0);
}

template<std::size_t N>
std::size_t my_array<bool, N>::size() const {
    return N;
}

template<std::size_t N>
void my_array<bool, N>::fill(bool val) {
    char pattern = (char)(val ? ~0 : 0);
    for(int i = 0; i < (int)size_; ++i)
        array_[i] = pattern;
}