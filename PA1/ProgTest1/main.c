#include <stdio.h>
#include <float.h>
#include "math.h"

double coordinates[3][2];

void clearInput()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int readValues()
{
    char c;

    printf("Bod A:\n");
    if(scanf(" [ %lf , %lf %c",&coordinates[0][0],&coordinates[0][1], &c)!=3 || (c!=']'))
        return 1;

    //clearInput();
    printf("Bod B:\n");
    if(scanf(" [ %lf , %lf %c",&coordinates[1][0],&coordinates[1][1], &c)!=3 || (c!=']'))
        return 1;
    //clearInput();
    printf("Bod C:\n");
    if(scanf(" [ %lf , %lf %c",&coordinates[2][0],&coordinates[2][1], &c)!=3 || (c!=']'))
        return 1;
    clearInput();
    return 0;
}

//1=the same, 0=different
int checkVectorSizes(double u[2], double v[2])
{
    if((fabs(sqrt(pow(u[0],2)+pow(u[1],2))-sqrt(pow(v[0],2)+pow(v[1],2))))<=DBL_EPSILON*1024*(fabs(u[0])+fabs(u[1])+fabs(v[0])+fabs(v[1]))){//(u[0]*u[0]+u[1]*u[1]+v[0]*v[0]+v[1]*v[1])) {
         //printf("same:--%f,%f,%f,%f--",u[0],u[1],v[0],v[1]);
        return 1;
    }
    return 0;
}

int checkInput()
{
    for (int i = 0; i < 2; i++) {
        if(coordinates[i][0]==coordinates[i+1][0] && coordinates[i][1]==coordinates[i+1][1])
            //printf("stejne:%f,%f,%f,%f",coordinates[i][0],coordinates[i+1][0],coordinates[i][1],coordinates[i+1][1]);
            return 1;
    }
    if(coordinates[2][0]==coordinates[0][0] && coordinates[2][1]==coordinates[0][1])
    {
        //printf("stejne:%f,%f,%f,%f",coordinates[2][0],coordinates[0][0],coordinates[2][1],coordinates[2][1]);
        return 1;
    }


    if(fabs((coordinates[0][0]*(coordinates[1][1]-coordinates[2][1])+coordinates[1][0]*(coordinates[2][1]-coordinates[0][1])+coordinates[2][0]*(coordinates[0][1]-coordinates[1][1])))<=DBL_EPSILON*1024*(pow(coordinates[0][0],2)+pow(coordinates[1][0],2)+pow(coordinates[2][0],2)+pow(coordinates[0][1],2)+pow(coordinates[1][1],2)+pow(coordinates[2][1],2)))
    {
        //printf("nelze:%f",(coordinates[0][0]*(coordinates[1][1]-coordinates[2][1])+coordinates[1][0]*(coordinates[2][1]-coordinates[0][1])+coordinates[2][0]*(coordinates[0][1]-coordinates[1][1])));
        return 1;
    }

    return 0;
}

double makeSmaller(double num)
{
    if (pow(num,2) >= 1e60 )
        return num/1e60;
    if (pow(num,2)<=1e-60)
        return num*1e60;
    return num;
}

//0=rovnobeznik, 1=ctverec, 2=kosoctverec, 3=obdelnik
int getObjectType(double lastCoords[2], double a[2], double b[2])
{
    double vectors[2][2];
    vectors[0][0] = makeSmaller(a[0])-makeSmaller(lastCoords[0]);
    vectors[0][1] = makeSmaller(a[1])-makeSmaller(lastCoords[1]);
    vectors[1][0] = makeSmaller(b[0])-makeSmaller(lastCoords[0]);
    vectors[1][1] = makeSmaller(b[1])-makeSmaller(lastCoords[1]);

    int vectorsSame = checkVectorSizes(vectors[0],vectors[1]);

    if (fabs(((vectors[0][0]*vectors[1][0]) + vectors[0][1]*vectors[1][1])/(sqrt(pow(vectors[0][0],2)+pow(vectors[0][1],2))*sqrt(pow(vectors[1][0],2)+pow(vectors[1][1],2))))<=DBL_EPSILON*1024*(fabs(vectors[0][0]) + fabs(vectors[0][1])+ fabs(vectors[1][0])+ fabs(vectors[1][1])))
    {
        if(vectorsSame)
            return 1;

        return 3;
    }

    if (vectorsSame)
        return 2;


    //rovnobeznik
    return 0;
}



void printObjectType(int type)
{
    switch(type)
    {
        case 0:
            printf("rovnobeznik\n");
            break;
        case 1:
            printf("ctverec\n");
            break;
        case 2:
            printf("kosoctverec\n");
            break;
        case 3:
            printf("obdelnik\n");
            break;
    }
}

void printResult()
{
    double a[2]={coordinates[2][0]+coordinates[1][0]-coordinates[0][0],coordinates[2][1]+coordinates[1][1]-coordinates[0][1]};
    double b[2]={coordinates[0][0]+coordinates[2][0]-coordinates[1][0],coordinates[0][1]+coordinates[2][1]-coordinates[1][1]};
    double c[2]={coordinates[0][0]+coordinates[1][0]-coordinates[2][0],coordinates[0][1]+coordinates[1][1]-coordinates[2][1]};

    double v1[2], v2[2];

    printf("A': [%0.9g,%0.9g], ", a[0],a[1]);
    v1[0]=coordinates[1][0];
    v1[1]=coordinates[1][1];
    v2[0]=coordinates[2][0];
    v2[1]=coordinates[2][1];
    printObjectType(getObjectType(a,v1,v2));

    printf("B': [%0.9g,%0.9g], ", b[0],b[1]);
    v1[0]=coordinates[0][0];
    v1[1]=coordinates[0][1];
    v2[0]=coordinates[2][0];
    v2[1]=coordinates[2][1];
    printObjectType(getObjectType(b,v1,v2));

    printf("C': [%0.9g,%0.9g], ", c[0],c[1]);
    v1[0]=coordinates[0][0];
    v1[1]=coordinates[0][1];
    v2[0]=coordinates[1][0];
    v2[1]=coordinates[1][1];
    printObjectType(getObjectType(c,v1,v2));
}

int main() {
    if (readValues()!=0)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    if(checkInput()!=0)
    {
        printf("Rovnobezniky nelze sestrojit.\n");
        return 1;
    }
    printResult();
    return 0;
}
