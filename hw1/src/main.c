#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/bmp.h"

int crop_and_rotate(char **argv) {
    char crrot[] = "crop-rotate";
   // printf("%s %d", argv[1], strcpy(argv[1], crrot));
    if (strcmp(argv[1], crrot))
        return 14;
    BMP bmp;
    FILE *f = fopen(argv[2], "r");
    if (!f)
        return 2;
    load_bmp(&bmp, f);
    fclose(f);

    int x, y, w, h;
    if (!(sscanf(argv[3], "%d", &x)) || !(sscanf(argv[4], "%d", &y)) ||
        !(sscanf(argv[5], "%d", &w)) || !(sscanf(argv[6], "%d", &h)) ||
        w <= 0 || h <= 0 || x < 0 || bmp.info.biWidth <= x || y < 0 || bmp.info.biHeight <= y)
        return 3;

    crop(&bmp, x, y, w, h);
    rotate(&bmp);
    resize(&bmp);

    f = fopen(argv[7], "w");
    if (!f)
        return 4;
    save_bmp(&bmp, f);
    fclose(f);

    clean(&bmp);

    return 0;
}

int insert_msg(char **argv) {
    char ins[] = "insert";
    if (strcmp(argv[1], ins))
        return 5;

    BMP bmp;
    FILE *f = fopen(argv[2], "r");
    if (!f)
        return 6;
    load_bmp(&bmp, f);
    fclose(f);

    key k;
    f = fopen(argv[4], "r");
    if (!f)
        return 7;
    parse_key(&k, f);
    fclose(f);

    f = fopen(argv[5], "r");
    if (!f)
        return 8;
    fseek (f, 0, SEEK_END);
    size_t len = (size_t)ftell(f) + 1;
    char *msg = malloc(len);
    fseek (f, 0, SEEK_SET);
    fread(msg, 1, len, f);
    fclose (f);
    msg[len] = 0;
    insert(&bmp, &k, msg);
    free(msg);

    f = fopen(argv[3], "w");
    if (!f)
        return 9;
    save_bmp(&bmp, f);
    fclose(f);

    clean(&bmp);

    return 0;
}

int extract_msg(char **argv) {
    char extr[] = "extract";
    if (strcmp(argv[1], extr))
        return 10;

    BMP bmp;
    FILE *f = fopen(argv[2], "r");
    if (!f)
        return 11;
    load_bmp(&bmp, f);
    fclose(f);

    key k;
    f = fopen(argv[3], "r");
    if (!f)
        return 12;
    parse_key(&k, f);
    fclose(f);

    f = fopen(argv[4], "w");
    if (!f)
        return 13;
    char *msg = extract(&bmp, &k);
    fprintf(f, "%s", msg);
    fclose (f);
    free(msg);

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
    else
        return 1;
}
