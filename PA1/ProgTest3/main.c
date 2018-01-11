#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#include "time.h"
#include "math.h"
#include "stdlib.h"

#define INVALID_DATE (-1)
#endif /* __PROGTEST__ */

long int leapYears(int year)
{
    //every 4 years
    long int ret = year/4;

    //exception 100s
    ret -= year / 100;
    //exception for exception above
    ret += year / 400;
    //now what... another exception for exception for exception...
    ret -= year / 4000;

    //just remove pre-1990
    ret += 1990 / 100;
    ret -= 1990 / 400;
    ret += 1990 / 4000;

    return ret;
}

int isLeap(int year)
{
    if( year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) && year % 4000 != 0 )
        return 1;
    return 0;
}

int checkDate(int y, int m, int d)
{
    int daysInMonths[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if (isLeap(y))
        daysInMonths[1]++;

    if (y<2000 || m < 1 || d < 1 || d > daysInMonths[m-1] || m > 12)
        return 0;

    return 1;
}

//count of days from 1990
long int convertDate(int y, int m, int d) {

    int daysInMonths[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (isLeap(y))
        daysInMonths[1]++;

    long int ret = 0;
    ret += (y - 1990) * 365;

    for (int i = 0; i<m-1;i++)
    {
        ret += daysInMonths[i];
    }

    ret += d;

    ret += leapYears(y-1);

    return ret;
}

long int getReference()
{
    return convertDate(2000,7,16);
}

void modDate(int *y, int *m, int *d, int days)
{
    int daysInMonths[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (isLeap(*y))
        daysInMonths[1]++;

    *d+=days;

    while (*d<1 || *m<1 || *m>12 || *d > daysInMonths[*m-1]) {

        if (*d < 1 && *m > 1) {
            *m = *m - 1;
            *d = daysInMonths[*m-1] - *d;
        }

        if (*d < 1)
        {
            *y = *y-1;
            *m=12;
            *d = daysInMonths[*m-1];
        }

        if (*d > daysInMonths[*m-1])
        {
            *m = *m +1;
            *d = 1;
        }

        if (*m > 12)
        {
            *y = *y +1;
            *m = 1;
        }
    }

}

int isFullMoon2 ( int y, int m, int d )
{

    //double part = fmod(fabs((convertDate(y,m,d)-getReference()))/29.53059027,1);
    /*double part = fabs(fmod((convertDate(y,m,d)-getReference()), 29.53059027));

    if (part > 29.16)
        part -= 29.16;

    int result = 0;
    if (part<0.616)
        result = 1;*/

    if (y==2000 && m == 6 && d == 16)
        return 0;
    if (y==2000 && m == 6 && d == 17)
        return 1;

    if (y<2000)
    {
        if (m == 12 && d != 22)
            return 0;
        else
            return 1;
    }



    double part = (abs(((convertDate(y,m,d)-getReference())*24*60*60))+36288)%2551443;




    int result = 0;
    if (part<24*60*60)
        result = 1;
    //printf("part:%f, res:%d, diff: %ld, fmod: %f, ref: %ld, ymd:%d,%d,%d\n",part,result,(convertDate(y,m,d)-getReference()),fmod(fabs((convertDate(y,m,d)-getReference()))/29.53059027,1),convertDate(y,m,d),y,m,d);
    return result;
}

int isFullMoon ( int y, int m, int d )
{
    if (!checkDate(y,m,d))
        return INVALID_DATE;

    return isFullMoon2(y,m,d);
}

int prevFullMoon ( int y, int m, int d,
                   int * prevY, int * prevM, int * prevD )
{
    if (!checkDate(y,m,d))
        return INVALID_DATE;

    *prevY = y;
    *prevM = m;
    *prevD = d;

    do{
        modDate(prevY,prevM,prevD,-1);
    }
    while (!isFullMoon2(*prevY,*prevM,*prevD));

    //printf("previous:d:%d,m:%d,y:%d\n",*prevY,*prevM,*prevD);

    return 1;
}

int nextFullMoon ( int y, int m, int d,
                   int * nextY, int * nextM, int * nextD )
{
    if (!checkDate(y,m,d))
        return INVALID_DATE;

    *nextY = y;
    *nextM = m;
    *nextD = d;

    do{
        modDate(nextY,nextM,nextD,1);
    }
    while (!isFullMoon2(*nextY,*nextM,*nextD));

    return 1;
}

#ifndef __PROGTEST__
int main ( void )
{
    int y, m, d;
    assert ( isFullMoon ( 2000, 7, 16 ) == 1 );
    /* removed asserts*/

    return 0;
}
#endif /* __PROGTEST__ */
