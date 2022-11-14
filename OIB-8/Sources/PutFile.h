//
// Created by Mark on 26.04.2022.
//

#ifndef OIB_8_PUTFILE_H
#define OIB_8_PUTFILE_H

void FileInit();
void ContainerInfo();
void ContainerRead();
void HiddenInfo();
void HiddenRead();
void ChangeDataBytes();
void HiddenSecretFile();

#define BYTES_COUNT 8.00
#define FOOTING_OF_DEGREE 2.00
#define ENTER 10

void PutFile()
{
    FileInit();
    ContainerInfo();

    container.data = (unsigned char*)calloc(sizeof(unsigned char), container.size);
    container.header = (char*)calloc(sizeof(char), container.dataOffset);

    system("cls");

    printf("---------------------------\n| ¬ведите степень упаковки: ");
    scanf("%d", &hidden.packingDegree);

    ContainerRead();

    HiddenInfo();

    hidden.data = (unsigned char*)calloc(sizeof(unsigned char), hidden.size);

    HiddenRead();

    ChangeDataBytes();
    HiddenSecretFile();
}

void FileInit()
{
    char c;
    int i = 1;

    system("cls");
    printf("-------------------------\n| ¬ведите им€ контейнера: ");

    imageName = (char*)malloc(sizeof(char) * 1);

    c = (char)getchar();

    if(c == '\n')
        c = (char)getchar();

    do
    {
        i++;
        imageName = (char *) realloc(imageName, sizeof(char) * i);
        imageName[i - 2] = c;
    } while ((c = (char)getchar()) != 10);

    imageName[i - 1] = '\0';
    i = 1;

    system("cls");
    printf("-------------------------------\n| ¬ведите им€ секретного файла: ");

    secretName = (char*)malloc(sizeof(char) * 1);

    c = (char)getchar();

    if(c == '\n')
        c = (char)getchar();

    do
    {
        i++;
        secretName = (char *) realloc(secretName, sizeof(char) * i);
        secretName[i - 2] = c;
    } while ((c = (char)getchar()) != ENTER);

    secretName[i - 1] = '\0';
}

void ContainerInfo()
{
    FILE *file = fopen(imageName, "rb+");

    fseek(file, DATA_OFFSET_OFFSET, SEEK_SET);
    fread(&container.dataOffset, 4, 1, file);

    fseek(file, WIDTH_OFFSET, SEEK_SET);
    fread(&container.width, 4, 1, file);

    fseek(file, HEIGHT_OFFSET, SEEK_SET);
    fread(&container.height, 4, 1, file);

    fseek(file, SIZE_OFFSET, SEEK_SET);
    fread(&container.size, 4, 1, file);

    fclose(file);
}

void ContainerRead()
{
    FILE *file = fopen(imageName, "rb+");

    for(int i = 0; i < container.dataOffset; i++)
    {
        fseek(file, i, SEEK_SET);
        fread(&container.header[i], 1, 1, file);
    }

    for(int i = 0; i < container.size; i++)
    {
        fseek(file, container.dataOffset+i, SEEK_SET);
        fread(&container.data[i], 1, 1, file);
    }

    fclose(file);
}

void HiddenInfo()
{
    FILE *file = fopen(secretName, "rb+");

    fseek(file, 0, SEEK_END);
    hidden.size = ftell(file);
    rewind(file);

    fclose(file);
}

void HiddenRead()
{
    FILE *file = fopen(secretName, "rb+");

    for(int i = 0; i < hidden.size; i++)
    {
        fseek(file, i, SEEK_SET);
        fread(&hidden.data[i], 1, 1, file);
    }

    fclose(file);
}

void ChangeDataBytes()
{
    FILE *file = fopen(imageName, "rb+");

    const int step = round(BYTES_COUNT / hidden.packingDegree);
    int c_num = 0;
    int h_num = 0;
    int count = 0;
    int size = hidden.size;

    for(int i = 0; i < 20; i++)
    {
        if(container.data[i] % 2 == 1)
        {
            container.data[i] -= 1;
        }

        if(size % 2 == 1)
        {
            container.data[i]++;
        }

        size /= 2;
    }

    for(int i = 0; i < hidden.size; i++)
    {
        h_num = hidden.data[i];
        count = 0;

        //printf("\nhidden byte = %d\n\n", h_num);

        for(int j = i * step; j < i * step + step; j++)
        {
            c_num = container.data[20 + j];

            for(int f = 0; f < hidden.packingDegree; f++)
            {
                if(c_num % 2 != 0)
                {
                    container.data[20 + j] -= (int)pow(FOOTING_OF_DEGREE, f);
                }

                c_num /= 2;
            }

            for(int f = 0; f < hidden.packingDegree; f++)
            {
                if(count < 8)
                {
                    if(h_num % 2 != 0)
                    {
                        container.data[20 + j] += (int)pow(FOOTING_OF_DEGREE, f);
                    }

                    h_num /= 2;
                    count++;
                }
            }

            //printf("byte: %d\n", container.data[j]);
        }

        //printf("\n\n");
        //system("pause");
    }

    fclose(file);
}

void HiddenSecretFile()
{
    FILE *file = fopen(imageName, "wb+");

    int a;
    int degree = 0;

    for(int i = 0; i < container.dataOffset; i++)
    {
        fseek(file, i, SEEK_SET);
        fwrite(&container.header[i], 1, 1, file);
    }

    for(int i = 0; i < container.size; i++)
    {
        fseek(file, container.dataOffset+i, SEEK_SET);
        a = (int)container.data[i];
        //printf("%d\n", a);
        //system("pause");
        fwrite(&container.data[i], 1, 1, file); // size 1
    }

    fseek(file, 6, SEEK_SET);
    fwrite(&degree, 1, 1, file); // size 1

    fseek(file, 7, SEEK_SET);
    fwrite(&hidden.packingDegree, 1, 1, file);

    fclose(file);
}

#endif //OIB_8_PUTFILE_H