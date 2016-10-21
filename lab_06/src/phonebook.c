#include <stdlib.h>
#include <string.h>
#include "phonebook.h"
#include "names.h"

#define MAXH 100

/*#pragma once

#include <stddef.h>

typedef struct human_s {
    char name[256];
    char middle_name[256];
    char family_name[256];
    char phones[10][21];
} human_t;

typedef struct phonebook_s {
    human_t *humans;
    size_t size;
    size_t capacity;
} phonebook_t;

int load_phonebook_xml(const char *filename, phonebook_t *book);
int save_phonebook_xml(const char *filename, phonebook_t *book);
void print_phonebook(phonebook_t *book);
void gen_phonebook(phonebook_t *book, size_t size);
void clear_phonebook(phonebook_t *book);
human_t get_human(phonebook_t *book, char* family_name);
void push_back_human(phonebook_t *book, human_t *human);
*/


void push_back_human(phonebook_t *book, human_t *human) {
    if (book->size == book->capacity) {
        book->capacity = 2 * book->capacity + 1;
        book->humans = realloc(humans, capacity);
    }
    book->humans[size++] = *human;
}

int family_cmp(const void *h1, const void *h2) {
    char f1* = ((human_t *)h1)->family_name;
    char f2* = ((human_t *)h2)->family_name;
    return (strcmp(f1, f2) < 0);
}

human_t get_human(phonebook_t *book, char* family_name) {
    human_t human;
    strcpy(human.family_name, family_name); 
    return *(human_t *)bsearch(&human, book->humans, book->size, sizeof(human_t), family_cmp);
}

void clear_phonebook(phonebook_t *book) {
    free(book->humans);
    book->size = 0;
    book->capacity = 0;
}

void gen_phonebook(phonebook_t *book, size_t size) {
    clear_phonebook(book);
    int size = 1 + rand() % MAXH;
    for (int i = 0; i < size; ++i) {
        human_t *human = malloc();{kNames[rand() % NAMES_CNT], kMiddleNames[rand() % MIDDLE_NAMES_CNT], kFamilyNames[rand() % FAMILY_NAMES_CNT]};
        int pcnt = 1 + rand();
        for (int i = 0; i < pcnt; ++i) {
            int p = ((1 + rand()) << 15) ^ rand();
            for (int j = 0; p; ++j) {
                human.phone[i][j] = p % 10;
                p /= 10;
            }
        }
        push_back_human(book, human);
    }
}


