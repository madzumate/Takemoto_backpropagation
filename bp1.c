#define CRT_SECURE_NO_WARNING
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
#define INPUTNO 3
#define HIDDENNO 3
#define ALPHA 10
#define SEED 65535
#define MAXINPUTNO 100
#define BIGNUM 100
#define LIMIT 0.001
 
 
double f(double u);
void initwh(double wh[HIDDENNO][INPUTNO + 1]);
 
void initwo(double wo[HIDDENNO + 1]);
 
double drnd(void);
 
void print(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1]);
 
double forward(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1],double hi[], double e[INPUTNO + 1]);
 
void olearn(double wo[HIDDENNO + 1], double hi[], double e[INPUTNO + 1],double o);
 
int getdata(double e[][INPUTNO + 1]);
void hlearn(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO][INPUTNO + 1],double hi[], double e[INPUTNO + 1],double o);
 
 
 
int main(void)
{
    double wh[HIDDENNO][INPUTNO + 1];
    double wo[HIDDENNO + 1];
    double e[MAXINPUTNO][INPUTNO + 1];
    double hi[HIDDENNO + 1];
    double o;
    double err = BIGNUM;
    int i,j;
    int n_of_e;
    int count = 0;
 
 
    srand(SEED);
 
    initwh(wh);
    initwo(wo);
    print(wh,wo);
 
    n_of_e = getdata(e);
    printf("学習データの個数：%d\n",n_of_e);
 
    while(err > LIMIT)
    {
        err = 0.0;
        for(j=0; j<n_of_e; ++j)
        {
            o=forward(wh, wo, hi ,e[j]);
            olearn(wo, hi, e[j], o);
            hlearn(wh, wo, hi, e[j], o);
            err += (o -e[j][INPUTNO])*(o - e[j][INPUTNO]);
        }
        ++count;
        fprintf(stderr, "%d\t%lf\n", count, err);
    }
    printf(wh, wo);
 
    for(i=0; i<n_of_e; i++)
    {
        printf("%d", i);
        for(j=0; j<INPUTNO+1; ++j)
        {
            printf("%d", i);
            for(j=0; j<INPUTNO; ++j)
            {
                printf("%lf", e[i][j]);
            }
            o=forward(wh, wo, hi, e[i]);
            printf("%lf\n", o);
        }
    }
    return 0;
}
 
 
 
void hlearn(double wh[HIDDENNO][INPUTNO+1], double wo[HIDDENNO+1], double hi[],double e[INPUTNO+1], double o)
{
    int i,j;
    double dj;
 
    for(j=0; j<HIDDENNO; ++j)
    {
        dj=hi[j] * (1 - hi[j]) * wo[j] * (e[INPUTNO] - o) *o * (1-o);
        for(i=0;i<INPUTNO; ++i)
        {
            wh[j][i] += ALPHA * e[i] * dj;
        }
        wh[j][i] += ALPHA * (-1.0) * dj;
    }
}
 
 
 
 
int getdata(double e[][INPUTNO+1])
{
    int n_of_e = 0;
    int j = 0;
 
    //追加
    char filename[20];
    FILE *fp;
    scanf("%s", &filename);
    if(( fp=fopen(filename, "r")) == NULL)
    {
        printf("\n DON'T OPEN FILE [%s]\n", filename);
        exit(1);
    }
    //追加ここまで
 
    while (scanf("%lf", &e[n_of_e][j]) != EOF)
    {
        ++j;
        if(j>INPUTNO)
        {
            j=0;
            ++n_of_e;
        }
    }
    return n_of_e;
}
 
 
 
 
 
void olearn(double wo[HIDDENNO+1], double hi[], double e[INPUTNO+1], double o)
{
    int i;
    double d;
 
    d = (e[INPUTNO] - o) * o * (1-o);
    for(i=0; i<HIDDENNO; ++i)
    {
        wo[i] += ALPHA * (-1.0) * d;
    }
    wo[i] += ALPHA * (-1.0) * d;
}
 
 
 
 
 
double forward(double wh[HIDDENNO][INPUTNO+1], double wo[HIDDENNO+1], double hi[], double e[INPUTNO+1])
{
    int i, j;
    double u;
    double o;
 
    for(i=0; i<HIDDENNO; ++i)
    {
        u=0;
        for(j=0; j<INPUTNO; ++j)
        {
            u += e[j] * wh[i][j];
        }
        u -= wh[i][j];
        hi[i] = f(u);
    }
    o=0;
    for(i=0; i<HIDDENNO; ++i)
    {
        o += hi[i] * wo[i];
    }
    o -= wo[i];
 
    return f(o);
}
 
 
 
 
 
void print(double wh[HIDDENNO][INPUTNO+1], double wo[HIDDENNO+1])
{
    int i, j;
 
    for(i=0; i < HIDDENNO; ++i)
    {
        for(j=0; j < INPUTNO+1; ++j)
        {
            printf("%lf", wh[i][j]);
        }
    }
    printf("\n");
    for(i=0; i<HIDDENNO+1; ++i)
    {
        printf("%lf", wo[i]);
    }
    printf("\n");
}
 
 
 
 
 
void initwh(double wh[HIDDENNO][INPUTNO+1])
{
    int i, j;
 
    for(i=0; i<HIDDENNO; ++i)
    {
        for(j=0; j<INPUTNO+1; ++j)
        {
            wh[i][j] = drnd();
        }
    }
}
 
 
 
 
 
void initwo(double wo[HIDDENNO+1])
{
    int i;
 
    for(i=0; i<HIDDENNO+1; ++i)
    {
        wo[i]=drnd();
    }
}
 
 
 
 
double drnd(void)
{
    double rndno;
 
    while((rndno = (double)rand() / RAND_MAX) == 1.0);
    rndno = rndno *2 - 1;
    return rndno;
}
 
 
double f(double u)
{
    return 1.0 / (1.0 + exp(-u));
}