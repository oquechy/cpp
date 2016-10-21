#include <stdlib.h>
#include "phonebook.h"

int main(int argc, char **argv) {
    phonebook_t book;
    book.size = 0;
    book.capacity = 0;
    book.humans = NULL;
    load_phonebook_xml(argv[1], &book);
    print_phonebook(&book);
    gen_phonebook(&book, rand() % 20 + 1);
    save_phonebook_xml(argv[2], &book);
    clear_phonebook(&book);
    return 0;
}