#ifndef HW2_TEST_H
#define HW2_TEST_H

#include <cstddef>

#define DO_CHECK(EXPR) check(EXPR, __func__, __FILE__, __LINE__)

class Test {
protected:
    static int failedNum; // количество тестов, которые сломались
    static int totalNum;  // общее количество тестов
public:
    static void check(bool expr, const char *func, const char  *filename, size_t lineNum);
    static void showFinalResult();
    virtual void runAllTests() = 0;
};

#endif //HW2_TEST_H
