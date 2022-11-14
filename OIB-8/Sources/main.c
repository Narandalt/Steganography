#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Variables.h"
#include "PutFile.h"
#include "GetFile.h"

#define ChoosePut 1
#define ChooseGet 2
#define Exit 3

void Menu()
{
    system("chcp 1251");
    int user;

    system("cls");

    printf("------------------------------\\\n| Выберите нужный пункт меню:  \\\n|                               \\\n| 1. Спрятать файл               \\\n| 2. Достать файл из картинки     \\\n|                                  \\\n|-> ");
    scanf("%d", &user);

    switch(user)
    {
        case ChoosePut:
            PutFile();
            break;
        case ChooseGet:
            GetFile();
            break;
        case Exit:
            break;
        default:
            break;
    }
}

int main()
{
    Menu();

    system("pause");
}