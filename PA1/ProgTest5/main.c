#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *numbers;
long long int numbersCount = 20;
long long int occupiedCount = 0;

long long int lcm(long long int a, long long int b);

int increaseSize()
{
    numbers = (int*)realloc(numbers,numbersCount*3*sizeof(*numbers));
    if (numbers == NULL)
        return 0;
    numbersCount *=2;
    return 1;
}

int allocateMemory()
{
    numbers=(int*)malloc(numbersCount*sizeof(*numbers));
    if (numbers == NULL)
        return 0;
    return 1;
}

int addNumber(int number)
{
    if (occupiedCount == numbersCount)
        if (!increaseSize())
            return 0;

    if (number < 1)
        return 0;

    numbers[occupiedCount] = number;
    occupiedCount++;
    return 1;
}

int readInput()
{
    printf("Pocty pruhu:\n");
    char bracket;
    if (scanf(" %c", &bracket) != 1)
        return 0;
    if (bracket != '{')
        return 0;

    int num;
    char comma;
    while (1)
    {
        if (scanf(" %d", &num) != 1)
            return 0;

        if (!addNumber(num))
            return 0;

        if (scanf(" %c", &comma) != 1)
            return 0;

        if (comma == ',')
            continue;

        else if (comma == '}')
            break;

        else
            return 0;
    }
    //printf("loaded: %lld\n", occupiedCount);

    return 1;
}

long long int getLCM(int start, int end)
{
    long long int actualLcm = 1;
    int i;

    for (i = start; i < end; i++) {
        actualLcm = lcm(actualLcm, numbers[i]);
    }

    return actualLcm;
}

int handleQueries()
{
    printf("Trasy:\n");
    int start, end;
    int code;

    while(1)
    {
        if ((code = scanf(" %d %d", &start, &end)) != 2 && code != EOF)
            return 0;

        if (code == EOF)
            return 1;

        if (start < 0 || end <= start || end > occupiedCount)
            return 0;

        printf("Vozidel: %lld\n", getLCM(start, end));
    }
}

int main() {
    if (!allocateMemory())
        return 1;

    if (!readInput())
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    if (!handleQueries())
    {
        printf("Nespravny vstup.\n");
        return 1;
    }


    free(numbers);
    return 0;
}

long long int gcd(long long int a, long long int b) {
    long long int remainder = a % b;

    if (remainder == 0) {
        return b;
    }

    return gcd(b, remainder);
}

long long int lcm(long long int a, long long int b)
{
    return (a/gcd(a,b))*b;
}
