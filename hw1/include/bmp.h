#ifndef HW1_BMP_H
#define HW1_BMP_H

#include <stdint.h>

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;

typedef struct tagBITMAPFILEHEADER {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    LONG  biWidth;
    LONG  biHeight;
    WORD  biPlanes;
    WORD  biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG  biXPelsPerMeter;
    LONG  biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagBMP {
    BITMAPFILEHEADER file;
    BITMAPINFOHEADER info;
    BYTE **px;
} BMP, *PBMP;

typedef struct tagKEY {
    int x, y, lsh, size;
} key;

void load_bmp(PBMP bmp, FILE *f);
void save_bmp(PBMP bmp, FILE *f);

void crop(PBMP bmp, int x, int y, int w, int h);
void rotate(PBMP bmp);
void clean(PBMP bmp);
void resize(PBMP bmp);

void parse_key(key *k, FILE *f);
char * extract(PBMP bmp, key *k);
void insert(PBMP bmp, key *k, char *msg);

#endif //HW1_BMP_H
