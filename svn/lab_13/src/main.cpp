#include <cstddef>
#include "my_array.h"

template<typename T, std::size_t N>
void test_core() {
    my_array<T, N> a;
    const my_array<T, N> &ca = a;
    a.empty();
    ca.empty();
    a.size();
    ca.size();

    a.at(0);
    ca.at(0);
    a[0];
    ca[0];
    (void)static_cast<const T &>(a[0]);
    (void)static_cast<const T &>(ca[0]);
}

#include <cstddef>
#include "my_array.h"
#include <opencv2/opencv.hpp>
#include <cstddef>
#include "my_array.h"

#include <cstddef>
#include "my_array.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cstddef>
#include "my_array.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>

template<typename T, std::size_t N>
void test_assign(T t1, T t2) {
    my_array<T, N> a;
    const my_array<T, N> &ca = a;
    a.fill(t1);

    T t = ca[3];
    assert(t == t1);
    a[3] = t2;
    t = a[3];
    assert(t == t2);
    a[0] = T();
    a[0] = a[0];
    a[0] = ca[0];
    a[0] = a[N - 1] = t2;
    assert(a[0] == t2);
    assert(a[N - 1] == t2);
    (void) t;
}

template<typename T, std::size_t N>
void test_fill(const T& t) {
    my_array<T, N> a;
    a.fill(t);

    for(int i = 0; i < (int)N; ++i)
        assert(a[i] == t);
}

template<typename T, std::size_t N>
void test_default() {
    my_array<T, N> a;

    T t;

    for(int i = 0; i < (int)N; ++i)
        assert(a[i] == t);
}

template<typename T, std::size_t N>
void test_size() {
    my_array<T, N> a;

    assert(sizeof(a) == N * sizeof(T) || sizeof(a) == (N + 7) / 8);
    assert(a.size() == N);
    assert(a.empty() == 0);
}

class NonCopyable {
public:
    NonCopyable() {}
private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable);
};

struct Eq {
    int x;
    Eq() : Eq(11) {}
    Eq(int x) : x(x) {}
    bool operator==(Eq e) {
        return (x == e.x);
    }
};

int main() {
    test_core<int, 10>();
    test_core<bool, 10>();
    test_core<NonCopyable, 10>();
    test_core<Eq, 10>();

    test_assign<int, 10>(5, 11);
    test_assign<bool, 11>(1, 0);
    test_assign<Eq, 10>(Eq(), Eq(12));

    test_fill<int, 10>(4);
    test_fill<bool, 10>(1);

    test_size<int, 10>();
    test_size<bool, 10>();
    test_size<Eq, 10>();
    test_size<NonCopyable, 10>();

    test_default<Eq, 10>();
}

