#include <stdio.h>
#include <stdlib.h>
#include "limits.h"

long long int array[250000];
int counter = 0;

int resultCount = 0;
//min, max, count
int results[250000][3];

int correctInput(double d)
{
    return ((d-((long long int)d))==0);
}

int loadValues()
{
    printf("Hodnoty:\n");
    int retVal;
    long long int num;
    double num1;
    while ((retVal = scanf(" %lf", &num1)) == 1)
    {
        if (!correctInput(num1))
        {
            return 0;
        }
        num = (long long int)num1;
        array[counter] = num;
        counter++;
    }

    if (counter<2 || counter > 250000)
        return 0;

    if (retVal == EOF)
        return 1;

    return 0;
}

void calcResult()
{
    long long int biggestFail = INT_MAX;
    int lastCount = INT_MIN;

    for (int i = 0; i < counter;i++)
    {
        if (array[i]>= biggestFail)
            continue;

        for (int j = counter-1; j > i; j--) {
            if ((array[j] >= array[i]) && ((j-i) >= lastCount))
            {
                results[resultCount][0] = i;
                results[resultCount][1] = j;
                results[resultCount][2] = (j-i);
                lastCount = results[resultCount][2];
                resultCount++;
                break;
            }

            if (j == counter-2) {
                biggestFail = array[i];
            }
        }
    }


}

int main() {
    if (!loadValues())
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    calcResult();

    if (resultCount == 0)
    {
        printf("Nelze najit.\n");
        return 0;
    }

    int maxCount = results[resultCount-1][2];
    int counter = 0;

    for(int i = resultCount-1; i>=0;i--)
    {
        if (results[i][2] >= maxCount) {
            printf("%d: %d - %d\n", results[i][2]+1, results[i][0], results[i][1]);
            counter++;
        }
        else
            break;
    }

    printf("Moznosti: %d\n", counter);

    return 0;
}