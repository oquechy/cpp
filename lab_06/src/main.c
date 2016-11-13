#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/phonebook.h"

/*void check(){
    FILE *my = fopen("try/my.txt", "r");
    FILE *correct = fopen("try/03-big.out", "r");
    if (!my)
        printf("!");
    if (!correct)
        printf("&");
    char *mys = malloc(1000), *cs = malloc(1000);
    while (fscanf(correct, "%s", cs)) {
        fscanf(my, "%s", mys);
        if (strcmp(mys, cs))
            printf("%s %s \n", cs, mys);
    }
    free(mys);
    free(cs);
}*/

int main(int argc, char **argv) {
    phonebook_t book;
    book.size = 0;
    book.capacity = 0;
    book.humans = NULL;
    load_phonebook_xml(argv[1], &book);
    print_phonebook(&book);
    gen_phonebook(&book, (size_t)rand() % 100 + 5);
    save_phonebook_xml(argv[2], &book);
    clear_phonebook(&book);
//    check();
    return 0;
}