#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "../include/bmp.h"

void load_bmp(PBMP bmp, FILE *f) {
    DWORD p;
    char *cf = (char *)&bmp->file, *ci = (char *)&bmp->info;

    fread(cf, 2, 1, f);
    fread(cf + 4, 12, 1, f);
    fread(ci, 40, 1, f);
    fseek(f, bmp->file.bfOffBits, SEEK_SET);

    size_t pw = (size_t)(4 - (3 * bmp->info.biWidth) % 4) % 4;
    bmp->px = malloc(bmp->info.biHeight * sizeof(char *));
    for (int i = 0; i < bmp->info.biHeight; ++i) {
        int j = bmp->info.biHeight - i - 1;
        bmp->px[j] = malloc((size_t)3 * bmp->info.biWidth);
        fread(bmp->px[j], (size_t)3 * bmp->info.biWidth, 1, f);
        fread(&p, pw, 1, f);
    }
}

void save_bmp(PBMP bmp, FILE *f) {
    size_t pw = (size_t)(4 - (3 * bmp->info.biWidth) % 4) % 4;
    DWORD p = 0;
    char *cf = (char *)&bmp->file, *ci = (char *)&bmp->info;

    fwrite(cf, 2, 1, f);
    fwrite(cf + 4, 12, 1, f);
    fwrite(ci, 40, 1, f);
    fseek(f, bmp->file.bfOffBits, SEEK_SET);

    for (int i = 0; i < bmp->info.biHeight; ++i) {
        int j = bmp->info.biHeight - 1 - i;
        fwrite(bmp->px[j], (size_t)3 * bmp->info.biWidth, 1, f);
        fwrite(&p, pw, 1, f);
    }
}

void crop(PBMP bmp, int x, int y, int w, int h) {
    BYTE **px = malloc(h * sizeof(char *));

    for (int i = 0; i < h; ++i) {
        px[i] = malloc((size_t)3 * w);
        memcpy(px[i], bmp->px[y + i] + 3 * x, (size_t)3 * w);
    }

    clean(bmp);

    bmp->px = px;
    bmp->info.biWidth = w;
    bmp->info.biHeight = h;
}

void rotate(PBMP bmp) {
    BYTE **px = malloc(bmp->info.biWidth * sizeof(char *));

    for (int i = 0; i < bmp->info.biWidth; ++i) {
        px[i] = malloc((size_t)3 * bmp->info.biHeight);
        for (int j = 0; j < bmp->info.biHeight; ++j)
            memcpy(px[i] + 3 * j, bmp->px[bmp->info.biHeight - 1 - j] + 3 * i, 3);
    }

    clean(bmp);

    bmp->px = px;
    int tmp = bmp->info.biWidth;
    bmp->info.biWidth = bmp->info.biHeight;
    bmp->info.biHeight = tmp;
}

void clean(PBMP bmp) {
    for (int i = 0; i < bmp->info.biHeight; ++i)
        free(bmp->px[i]);
    free(bmp->px);
}

void resize(PBMP bmp) {
    DWORD pw = (DWORD)(4 - 3 * bmp->info.biWidth % 4) % 4;
    bmp->info.biSizeImage = bmp->info.biHeight * (3 * bmp->info.biWidth + pw);
}
