#include <stdio.h>

#define LIMIT 10000000 * 10

long long int roomSize[2];
int fail = 0;

//new way
long long int min[2], step = 0;

int morePrecise(double num);
void clearInput();
long long int lcm(long long int a, long long int b);
int loadNumbers(long long int *ret);
int mergeQueues(long long int *queue1, long long int step1, long long int *queue2, long long int step2);
long long int getTileQueueLength(long long int tile[2], long long int min);

int loadRoomSize()
{
    printf("Minimalni velikost:\n");

    long long int sizes[] = {0,0};

    if (!loadNumbers(sizes) || sizes[0] <1 || sizes[1] <1) {
        printf("Nespravny vstup.\n");
        return 0;
    }

    roomSize[0] = sizes[0];
    roomSize[1] = sizes[1];

    min[0] = sizes[0];
    min[1] = sizes[1];

    return 1;
}

void loadTiles()
{
    printf("Dlazdicky:\n");
    while(1)
    {
        long long int sizes[] = {0,0};

        int readVal;
        if ((readVal = loadNumbers(sizes)) == 0 ) {
            fail=2;
            break;
        }

        if (readVal == -1) {
            if (step == 0)
                fail=2;
            break;
        }

        if (sizes[0]<1)
        {
            fail=2;
            break;
        }

        //hack when it failed (we just have to read all the other values)
        if (fail != 0) {
            continue;
        }

        long long int actualTileQueue[2];
        actualTileQueue[0] = getTileQueueLength(sizes, min[0]);

        actualTileQueue[1] = getTileQueueLength(sizes, min[1]);

        if (step == 0)
        {
            min[0] = actualTileQueue[0];
            min[1] = actualTileQueue[1];
            step = sizes[0]+sizes[1];
            continue;
        }

        if (!mergeQueues(&actualTileQueue[0], sizes[0]+sizes[1], &min[0], step) || !mergeQueues(&actualTileQueue[1], sizes[0]+sizes[1], &min[1], step))
        {
            fail = 1;
            continue;
        }

        step = lcm(sizes[0]+sizes[1],step);

    }
}


int main() {
    if (!loadRoomSize())
        return 1;

    clearInput();

    loadTiles();

    if (fail != 0)
    {
        switch (fail){
            case 1:
                printf("Reseni neexistuje.\n");
                break;
            default:
                printf("Nespravny vstup.\n");
                break;
        }

        return 1;
    }

    printf("Velikost: %.1f x %.1f\n",min[0]/10.0,min[1]/10.0);

    return 0;
}

int morePrecise(double num)
{
    if (num*10 - (int)(num*10) > 0)
        return 1;
    return 0;
}

long long int gcd(long long int a, long long int b) {
    int remainder = a % b;

    if (remainder == 0) {
        return b;
    }

    return gcd(b, remainder);
}

long long int lcm(long long int a, long long int b)
{
    long long int a1 = (a*b)/gcd(a, b);
    printf("%lld\n",a1);
    return a1;
}

int mergeQueues(long long int *queue1, long long int step1, long long int *queue2, long long int step2)
{
   /* long long int a = *queue1;
    long long int b = *queue2;*/
    long long int count = 0;
    while(*queue1 != *queue2)
    {
        if (*queue1> *queue2)
            *queue2+=step2;
        else
            *queue1+=step1;

        if (count++ > 10e7)
            return 0;
    }

    //printf("--o:%lld,t1%lld,t2:%lld--",*queue1, lcm(a,b), gcd(a,b));
    return 1;
}


long long int getTileQueueLength(long long int tile[2], long long int min)
{
    long long int count = (min-tile[1]) / (tile[0] + tile[1]) + (((min-tile[1])%(tile[0]+tile[1]) != 0) ? 1 : 0);
    long long int a = (tile[0]+tile[1]) * count + tile[1];
    //printf("%lld",a);
    return a;
}

/*int getTileQueueLength2(int tile[2], int min)
{
    int length = tile[1];
    while(length<min)
    {
        length+=(tile[0]+tile[1]);
    }
    return length;
}*/

void clearInput()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int loadNumbers(long long int *ret)
{
    double temp[2];
    ret[0] = 0;
    ret[1] = 0;

    int val;

    if (((val = scanf(" %lf %lf", &temp[0], &temp[1])) != 2 && val != -1))
    {
        clearInput();
        //printf("Nespravny vstup.\n");
        return 0;
    }

    if (val == -1)
        return -1;

    if (temp[0]<0 || temp[1]<0 || temp[0] > 10000000 || temp[1] > 10000000 || morePrecise(temp[0]) || morePrecise(temp[1]))
    {
       // printf("Nespravny vstup.\n");
        return 0;
    }

    ret[0] = (long long int)(temp[0]*10);
    ret[1] = (long long int)(temp[1]*10);

    return 1;
}

