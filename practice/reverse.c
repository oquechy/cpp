#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char s[256], *ans[256], delim[] = " \n\t";
    fgets(s, 255, stdin);
    int sz = 0;
    char *ptr = s;
    while (ans[sz++] = strtok(ptr, delim)){
        ptr = NULL;
    }
    for (int i = sz - 2; i >= 0; --i)
        printf("%s ", ans[i]);
    return 0;
}

