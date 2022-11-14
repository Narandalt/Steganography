//
// Created by Mark on 26.04.2022.
//

#ifndef OIB_8_VARIABLES_H
#define OIB_8_VARIABLES_H

#define DATA_OFFSET_OFFSET 0x000A
#define WIDTH_OFFSET 0x0012
#define HEIGHT_OFFSET 0x0016
#define SIZE_OFFSET 0x0002

char *imageName;
char *secretName;

typedef struct BMP
{
    int width;
    int height;
    int size;
    int dataOffset;
    unsigned char *data;
    char *header;
} bmp;

typedef struct SECRET
{
    int size;
    unsigned char *data;
    int packingDegree;
} secret;

bmp container;
secret hidden;

#endif //OIB_8_VARIABLES_H
