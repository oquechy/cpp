#include <stdlib.h>
#include <stdio.h>
#include "../include/bmp.h"

int main(int argc, char **argv) {
    BMP bmp;

    if (argc != 7)
        return 1;
    FILE *f = fopen(argv[1], "r");
    if (!f)
        return 2;
    load_bmp(&bmp, f);
    fclose(f);

    int x, y, w, h;
    if (!(sscanf(argv[2], "%d", &x)) || !(sscanf(argv[3], "%d", &y)) ||
        !(sscanf(argv[4], "%d", &w)) || !(sscanf(argv[5], "%d", &h)) ||
        w <= 0 || h <= 0 || x < 0 || bmp.info.biWidth <= x || y < 0 || bmp.info.biHeight <= y)
        return 3;

    crop(&bmp, x, y, w, h);
    rotate(&bmp);
    resize(&bmp);

    f = fopen(argv[6], "w");
    if (!f)
        return 4;
    save_bmp(&bmp, f);
    fclose(f);

    clean(&bmp);

    return 0;
}