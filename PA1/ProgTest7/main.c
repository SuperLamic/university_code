#include <stdio.h>
#include <string.h>
#include <malloc.h>

int module, count = 0;

char getChar(int num)
{
    switch(num)
    {
        case 1:
            return 'R';
        case 2:
            return 'C';
        case 3:
            return 'I';
        case 4:
            return 'P';
        default:
            return '.';
    }
}

int isValid(char *arr, int len)
{
    int lastPark = 0, betweenCommercial = 0, industrialCount = 0;
    for (int i = 0; i < len; ++i) {
        char c = arr[i];

        if (lastPark >= module && c != 'P')
            return 0;

        if (betweenCommercial != 0 && betweenCommercial <= module && c == 'C')
            return 0;

        if (industrialCount == 1 && c != 'I')
            return 0;

        if (i == len-1 && industrialCount == 0 && c == 'I')
            return 0;

        if (c == 'P')
            lastPark=0;
        else
            lastPark++;

        if (c == 'C' && betweenCommercial == 0)
            betweenCommercial++;

        if (c != 'C' && betweenCommercial !=0)
            betweenCommercial++;

        if (betweenCommercial > module)
            betweenCommercial=0;

        if (c == 'I')
            industrialCount++;
        else
            industrialCount = 0;
    }
    return 1;
}

void iterate(char *arr, int position, int len, int print) {
    int i;

    if (position < (len - 1)) {
        for (i = 1; i <= 4; i++) {
            arr[position] = getChar(i);

            iterate(arr, position+1, len, print);
        }
    } else {
        for (i = 1; i <= 4; i++) {
            arr[position] = getChar(i);

            if (!isValid(arr,len))
                continue;

            if (print)
                printf("[%s]\n",arr);
            count++;
        }
    }
}

void compute(int num, int print)
{
    char * arr = (char*)malloc((num+1)* sizeof(char));

    memset(arr, 0, num + 1);
    count =0 ;
    iterate(arr,0,num,print);
    printf("=> %d\n",count);
    free(arr);
}

int loadModule()
{
    printf("Modul:\n");
    if (scanf(" %d", &module) != 1 || module <1 || module>10)
        return 0;
    return 1;
}

int handleQueries()
{
    char command[5];
    int ret = 0, mode = 0, num = 0, val =0;
    printf("Vypocty:\n");
    while(ret != EOF) {
        ret = scanf(" %s", command);
        if (ret == EOF)
            return 1;

        if (strcmp(command, "count") == 0)
            mode = 0;
        else if (strcmp(command, "list") == 0)
            mode = 1;
        else
            return 0;

        if (scanf(" %d", &num) != 1 || num <1)
            return 0;

        if ((val = fgetc(stdin)) != '\n')
        {
            if  (val == EOF)
                return 1;
            else {
                return 0;
            }
        }


        compute(num, mode);
    }
    return 1;
}

int main() {
    if (!loadModule() || !handleQueries())
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    return 0;
}