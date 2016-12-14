/*#ifndef HW2_TEST_H
#define HW2_TEST_H

class Test {
protected:
    static int failedNum; // количество тестов, которые сломались
    static int totalNum;  // общее количество тестов
public:
Эта функция запускает все тесты из производного класса. Именно эта функция запускается из main в test.cpp.

virtual void runAllTests() = 0;


// Можно добавлять методы при необходимости
};


#endif //HW2_TEST_H
*/

#include "Test.h"
#include <cstdio>

int Test::failedNum = 0; // количество тестов, которые сломались
int Test::totalNum = 0;

void Test::check(bool expr, const char *func, const char  *filename, size_t lineNum) {
    ++totalNum;
    if (expr)
        return;
    printf("test failed: %s in %s:%zu\n", func, filename, lineNum);
    ++failedNum;
}

void Test::showFinalResult() {
    printf("         .-.                                              .-.\n"
                   "        (. .)__.')                                  (`.__(. .)\n"
                   "        / V      )                                  (      V \\\n"
                   "  ()    \\  (   \\/                                    \\/   )  /    ()\n"
                   "<)-`\\()  `._`._ \\                                    / _.'_.'  ()/'-(>\n"
                   "  <)_>=====<<==`'====================================`'==>>=====<_(>\n"
                   " <>-'`(>                                         hjw          <)'`-<>\n"
                   "");
    printf("----------------------------------------------------------------------\n");
    if (failedNum)
        printf("                      Failed %d of %d tests.\n", failedNum, totalNum);
    else
        printf("                          All test passed.\n");
    printf("----------------------------------------------------------------------\n");
}
