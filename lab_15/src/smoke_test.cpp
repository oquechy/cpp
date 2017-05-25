#include "linq.h"
#include <math.h>
#include <assert.h>
#include <vector>
#include <sstream>
#include <iterator>
#include <forward_list>

void where_neq_test() {
    int xs[] = { 1, 2, 1, 4, 1, 3};
    int x = 1;
    std::vector<int> res =
            from(xs, xs + 5)  // Взять элементы xs
                    .where_neq(1)    // Оставить только значения != 1
                    .to_vector();     // Преобразовать результат в вектор

    std::vector<int> expected = { 2, 4 };
    assert(res == expected);
}

void example1() {
    int xs[] = { 1, 2, 3, 4, 5 };

    std::vector<int> res =
            from(xs, xs + 5)  // Взять элементы xs
                    .select([](int x) { return x * x; })  // Возвести в квадрат
                    .where_neq(25)    // Оставить только значения != 25
                    .where([](int x) { return x > 3; })   // Оставить только значения > 3
                    .drop(2)          // Убрать два элемента из начала
                    .to_vector();     // Преобразовать результат в вектор

    std::vector<int> expected = { 16 };
    assert(res == expected);
}

void example2() {
    std::stringstream ss("1 2 3 -1 4");
    std::istream_iterator<int> in(ss), eof;

    std::vector<int> res =
            from(in, eof)  // Взять числа из входного потока
                    .take(3)       // Не более четырёх чисел
                    .until_eq(-1)  // Перестать читать после прочтения -1
                    .to_vector();  // Получить список считанных чисел

    std::vector<int> expected = { 1, 2, 3 };
    assert(expected == res);

    int remaining;
    assert(ss >> remaining);
    assert(remaining == 4);
}

void example3() {
    int xs[] = { 1, 2, 3, 4, 5 };

    std::vector<double> res =
            from(xs, xs + 5)  // Взять элементы xs
                    .select<double>([](int x) { return sqrt(x); })  // Извлечь корень
                    .to_vector();     // Преобразовать результат в вектор

    assert(res.size() == 5);
    for (std::size_t i = 0; i < res.size(); i++) {
        assert(fabs(res[i] - sqrt(xs[i])) < 1e-9);
    }
}

void functor() {
    int xs[] = { 1, 2, 3, 4, 5 };

    struct foo{
        double operator() (int x){
            return sqrt((double) x);
        }
    };

    std::vector<double> res =
            from(xs, xs + 5)  // Взять элементы xs
                    .select<double>(foo())  // Извлечь корень
                    .to_vector();     // Преобразовать результат в вектор

    assert(res.size() == 5);
    for (std::size_t i = 0; i < res.size(); i++) {
        assert(fabs(res[i] - sqrt(xs[i])) < 1e-9);
    }
}

void empty() {
    std::vector<int> xs;

    std::vector<double> res =
            from(xs.begin(), xs.end())  // Взять элементы xs
                    .select<double>([](int x) { return sqrt(x); })  // Извлечь корень
                    .drop(100)
                    .take(70)
                    .until([](int x) -> bool { return !x ;})
                    .until_eq(11)
                    .where([](int x) -> bool { return (bool)(x & 1) ;})
                    .to_vector();     // Преобразовать результат в вектор

    assert(res.size() == 0);
}

void example4() {
    std::stringstream iss("4 16");
    std::stringstream oss;
    std::istream_iterator<int> in(iss), eof;
    std::ostream_iterator<double> out(oss, "\n");

    from(in, eof)    // Взять числа из входного потока
            .select([](int x) { return sqrt(x); })  // Извлечь из каждого корень
            .copy_to(out);  // Вывести на экран

    assert(oss.str() == "2\n4\n");
}

void test_interactive() {
    std::istream_iterator<int> in(std::cin), eof;
    std::ostream_iterator<double> out(std::cout, "\n");

    from(in, eof)    // Взять числа из входного потока
            .select([](int x) { return sqrt(x); })  // Извлечь из каждого корень
            .copy_to(out);  // Вывести на экран

    //assert(oss.str() == "2\n4\n");
}

struct para{
    int x;
    float y;
};


void super_hard() {
    std::forward_list<para> xs =
            { {1, 2}, {3, 4}, {5, 5}, {5, 6}, {8, 9}, {7, 7}};

    std::vector<float> res =
            from(xs.begin(), xs.end())  // Взять элементы xs
                    .select<float>([](para p) { return p.x * p.y; })  // Возвести в квадрат
                    .where_neq(25)    // Оставить только значения != 25
                    .where([](int x) { return x > 3; })   // Оставить только значения > 3
                    .drop(1)          // Убрать два элемента из начала
                    .until([](float x){ return x == 72;})
                    .to_vector();     // Преобразовать результат в вектор

    std::vector<float > expected = { 30 };
    assert(res == expected);
}


int main() {
    where_neq_test();
    example1();
    example2();
    example3();
    example4();
    std::cerr << "error? \n";
    empty();
    functor();
    super_hard();
    test_interactive();
    std::cerr << "no way\n";
    return 0;
}
