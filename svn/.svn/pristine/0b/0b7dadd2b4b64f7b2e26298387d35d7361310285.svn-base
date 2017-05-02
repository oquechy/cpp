#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/bmp.h"

void print_usage() {
    printf("usage:\t./main crop-rotate <in-bmp> <out-bmp> <x> <y> <w> <h>\n\t"
                   "./main insert <in-bmp> <out-bmp> <key-txt> <msg-txt>\n\t"
                   "./main extract <in-bmp> <key-txt> <msg-txt>\n");
}

void no_file(char *name) {
    printf("no file %s\n", name);
}

int crop_and_rotate(char **argv) {
    char crrot[] = "crop-rotate";
    if (strcmp(argv[1], crrot)) {
        print_usage();
        return 14;
    }
    BMP bmp;
    FILE *f = fopen(argv[2], "r");
    if (!f) {
        no_file(argv[2]);
        return 2;
    }
    load_bmp(&bmp, f);
    fclose(f);

    int x, y, w, h;
    if (!(sscanf(argv[4], "%d", &x)) || !(sscanf(argv[5], "%d", &y)) ||
        !(sscanf(argv[6], "%d", &w)) || !(sscanf(argv[7], "%d", &h)) ||
        w <= 0 || h <= 0 || x < 0 || bmp.info.biWidth < x + w || y < 0 || bmp.info.biHeight < y + h) {
        print_usage();
        return 3;
    }

    crop(&bmp, x, y, w, h);
    rotate(&bmp);
    resize(&bmp);

    f = fopen(argv[3], "w");
    if (!f) {
        no_file(argv[3]);
        return 4;
    }
    save_bmp(&bmp, f);
    fclose(f);

    clean(&bmp);

    return 0;
}

int insert_msg(char **argv) {
    char ins[] = "insert";
    if (strcmp(argv[1], ins)) {
        print_usage();
        return 5;
    }

    BMP bmp;
    FILE *f = fopen(argv[2], "r");
    if (!f) {
        no_file(argv[2]);
        return 6;
    }
    load_bmp(&bmp, f);
    fclose(f);

    key *k;
    f = fopen(argv[4], "r");
    if (!f) {
        no_file(argv[4]);
        return 7;
    }
    fseek (f, 0, SEEK_END);
    size_t len = (size_t)ftell(f);
    k = malloc(len * 4);
    if (!k) {
        printf("memory error\n");
        return 15;
    }
    fseek (f, 0, SEEK_SET);
    parse_key(k, f);
    fclose(f);

    f = fopen(argv[5], "r");
    if (!f) {
        no_file(argv[5]);
        return 8;
    }
    fseek (f, 0, SEEK_END);
    len = (size_t)ftell(f);
    char *msg = malloc(len + 1);
    if (!msg) {
        printf("memory error\n");
        return 16;
    }
    fseek (f, 0, SEEK_SET);
    fread(msg, 1, len, f);
    fclose (f);
    msg[len] = 0;
    insert(&bmp, k, msg);
    free(msg);
    free(k);

    f = fopen(argv[3], "w");
    if (!f) {
        no_file(argv[3]);
        return 9;
    }
    save_bmp(&bmp, f);
    fclose(f);

    clean(&bmp);

    return 0;
}

int extract_msg(char **argv) {
    char extr[] = "extract";
    if (strcmp(argv[1], extr)) {
        print_usage();
        return 10;
    }

    BMP bmp;
    FILE *f = fopen(argv[2], "r");
    if (!f) {
        no_file(argv[2]);
        return 11;
    }
    load_bmp(&bmp, f);
    fclose(f);

    key *k;
    f = fopen(argv[3], "r");
    if (!f) {
        no_file(argv[3]);
        return 12;
    }
    fseek (f, 0, SEEK_END);
    size_t len = (size_t)ftell(f);
    k = malloc(len * 4);
    if (!k) {
        printf("memory error\n");
        return 17;
    }
    fseek (f, 0, SEEK_SET);
    parse_key(k, f);
    fclose(f);

    f = fopen(argv[4], "w");
    if (!f) {
        no_file(argv[4]);
        return 13;
    }
    char *msg = extract(&bmp, k);
    fprintf(f, "%s", msg);
    fclose (f);
    free(msg);
    free(k);

    clean(&bmp);

    return 0;
}

int main(int argc, char **argv) {
    if (argc == 8)
        return crop_and_rotate(argv);
    else if (argc == 6)
        return insert_msg(argv);
    else if (argc == 5)
        return extract_msg(argv);
    else {
        print_usage();
        return 1;
    }
}
