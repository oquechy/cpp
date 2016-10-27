#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <expat.h>
#include "phonebook.h"
#include "names.h"

#define BUFFER_SIZE 10000

typedef struct data_s{
    phonebook_t *book;
    human_t h;
    int phone_i;
    int start_p, len_p, i_p;
} data_t;

void start_element(void *data, const char *element, const char **attribute) {
    data_t *d = (data_t *)data;
    if (!strcmp(element, "phone")) {
        d->start_p = 1;
    }
    if (!strcmp(element, "human")) {
        char name[1000];
        strcpy(name, attribute[1]);
        strcpy(d->h.name, strtok(name, " "));
        strcpy(d->h.middle_name, strtok(NULL, " "));
        strcpy(d->h.family_name, strtok(NULL, " "));
    }
}

void end_element(void *data, const char *element) {
    data_t *d = (data_t *)data;
    if (!strcmp(element, "human")) {
        for (int i = d->phone_i; i < 10; ++i)
            d->h.phones[i][0] = '@';
        d->phone_i = 0;
        push_back_human(d->book, &d->h);
    }
    if (!strcmp(element, "phone")) {
        d->start_p = 0;
        ++d->phone_i;
    }
}

void handle_data(void *data, const char *content, int length) {
    data_t *d = (data_t *)data;
    char *tmp = (char *)malloc((size_t)length + 1);
    strncpy(tmp, content, length);
    tmp[length] = '\0';
    if ('0' <= tmp[0] && tmp[0] <= '9') {
        if (!d->start_p){
            strcpy(d->h.phones[d->phone_i] + d->len_p, tmp);
        }
        else {
            strcpy(d->h.phones[d->phone_i], tmp);
            d->len_p = length;
        }
    }
    free(tmp);
}

void push_back_human(phonebook_t *book, human_t *human) {
    if (book->size == book->capacity) {
        book->capacity = 2 * book->capacity + 1;
        book->humans = realloc(book->humans, book->capacity * sizeof(human_t));
    }
    memcpy(&book->humans[book->size++], human, sizeof(human_t));
}

int family_cmp(const void *h1, const void *h2) {
    char *f1 = ((human_t *)h1)->family_name;
    char *f2 = ((human_t *)h2)->family_name;
    return (strcmp(f1, f2));
}

human_t get_human(phonebook_t *book, char* family_name) {
    human_t human;
    strcpy(human.family_name, family_name);
    return *(human_t *)bsearch(&human, book->humans, book->size, sizeof(human_t), family_cmp);
}

void clear_phonebook(phonebook_t *book) {
    free(book->humans);
    book->humans = NULL;
    book->size = 0;
    book->capacity = 0;
}

void gen_phonebook(phonebook_t *book, size_t size) {
    clear_phonebook(book);
    for (int i = 0; i < size; ++i) {
        human_t human;
        strcpy(human.name, kNames[rand() % NAMES_CNT]);
        strcpy(human.middle_name, kMiddleNames[rand() % MIDDLE_NAMES_CNT]);
        strcpy(human.family_name, kFamilyNames[rand() % FAMILY_NAMES_CNT]);
        int pcnt = 1 + rand() % 10;
        for (int i = 0; i < pcnt; ++i) {
            unsigned long long p = (((unsigned long long)rand() << (rand() % 31)) ^ (unsigned long long)rand()) + 1;
            for (int j = 0; p; ++j) {
                human.phones[i][j] = p % 10 + '0';
                human.phones[i][j + 1] = 0;
                p /= 10;
            }
        }
        for (int i = pcnt; i < 10; ++i)
            human.phones[i][0] = '@';
        push_back_human(book, &human);
    }
}

void print_phonebook(phonebook_t *book) {
    printf("%zu\n", book->size);
    for(int i = 0; i < book->size; ++i) {
        printf("name: %s\n", book->humans[i].name);
        printf("middle name: %s\n", book->humans[i].middle_name);
        printf("family name: %s\n", book->humans[i].family_name);
        for (int j = 0; j < 10 && book->humans[i].phones[j][0] != '@'; ++j)
            printf("phone: %s\n", book->humans[i].phones[j]);
        printf("\n");
    }
}

int save_phonebook_xml(const char *filename, phonebook_t *book) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        //printf("Failed to open file\n");
        return 1;
    }
    fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<phonebook>\n");
    for (int i = 0; i < book->size; ++i) {
        human_t hum = book->humans[i];
        fprintf(f, "    <human name=\"%s %s %s\">\n", hum.name, hum.middle_name, hum.family_name);
        for (int j = 0; j < 10 && hum.phones[j][0] != '@'; ++j)
            fprintf(f, "        <phone>%s</phone>\n", hum.phones[j]);
        fprintf(f, "    </human>\n");
    }
    fprintf(f, "</phonebook>\n");
    fclose(f);
    return 0;
}

int load_phonebook_xml(const char *filename, phonebook_t *book) {
    char buff[BUFFER_SIZE];
    size_t buff_size = BUFFER_SIZE;

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    data_t book_data;
    book_data.book = book;
    book_data.phone_i = 0;

    XML_Parser  parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_element, end_element);
    XML_SetCharacterDataHandler(parser, handle_data);
    XML_SetUserData(parser, &book_data);
    memset(buff, 0, buff_size);

    size_t len = 0;
    int done = 0;
    do {
        len = fread(buff, sizeof(char), buff_size, fp);
        done = len < buff_size;

        if (XML_Parse(parser, buff, len, done) == XML_STATUS_ERROR) {
            printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
            return 2;
        }
//        printf("buff -- %i\n", len);
        book_data.start_p = 0;

    } while (!done);

    XML_ParserFree(parser);
    fclose(fp);

    qsort(book->humans, book->size, sizeof(human_t), family_cmp);

    return 0;
}
