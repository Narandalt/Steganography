//
// Created by Mark on 28.04.2022.
//

#ifndef OIB_8_GETFILE_H
#define OIB_8_GETFILE_H

#include "Variables.h"

#define TXT 't'
#define EXE 'e'

void GetHiddenInfo();
void SolveSecretData();
void CreateFile();

void GetFile()
{
    FileInit();
    ContainerInfo();

    container.data = (unsigned char*)calloc(sizeof(unsigned char), container.size);
    container.header = (char*)calloc(sizeof(char), container.dataOffset);

    ContainerRead();
    GetHiddenInfo();

    hidden.data = (unsigned char*)calloc(sizeof(unsigned char), hidden.size);

    SolveSecretData();
    CreateFile();

}

void GetHiddenInfo()
{
    FILE *file = fopen(imageName, "rb+");

    int size = 0, a;

    for(int i = 0; i < 20; i++)
    {
        if(container.data[i] % 2 == 1)
        {
            hidden.size += (int)pow(FOOTING_OF_DEGREE, i);
        }
    }

    fseek(file, 7, SEEK_SET);
    fread(&hidden.packingDegree, 1, 1, file);

    fclose(file);
}

void SolveSecretData()
{
    FILE *file = fopen(imageName, "rb+");

    for(int i = 0; i < hidden.size; i++)
    {
        fseek(file, container.dataOffset+i+20, SEEK_SET);
        fread(&hidden.data[i], 1, 1, file);
    }

    fclose(file);
}

void CreateFile()
{
    FILE *file = fopen(secretName, "wb+");

    const int x = (int)(hidden.size * round(BYTES_COUNT / hidden.packingDegree));
    int result = 0, step = 0, row = 0;
    int a;
    char c;

    for(int i = 0; i < x; i++)
    {
        a = (int)container.data[i+20];

        for(int j = 0; j < hidden.packingDegree; j++)
        {
            if(step == BYTES_COUNT)
            {
                break;
            }

            result = (a % 2 == 1) ? result + (int)pow(FOOTING_OF_DEGREE, step) : result;
            step++;
            a /= 2;
        }

        if((i + 1) % (int)round(BYTES_COUNT / hidden.packingDegree) == 0)
        {
            step = 0;
            fseek(file, row, SEEK_SET);
            //printf("%d\n", result);
            //system("pause");

            container.data[i+20] = result;

            fwrite(&container.data[i+20], 1, 1, file);
            row++;
            result = 0;
        }
    }

    fclose(file);
}

#endif //OIB_8_GETFILE_H
