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

void print(double wh[HIDDENNO][INPUTNO + 1],
            double wo[HIDDENNO + 1]);

double forward(double wh[HIDDENNO][INPUTNO + 1],
                double wo[HIDDENNO + 1],double hi[],
                double e[INPUTNO + 1]);

void olearn(double wo[HIDDENNO + 1], double hi[],
            double e[INPUTNO + 1],double o);

int getdata(double e[][INPUTNO + 1]);
void hlearn(double wh[HIDDENNO][INPUTNO + 1],
            double wo[HIDDENNO][INPUTNO + 1],double hi[],
            double e[INPUTNO + 1],double o);



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
            err += (o -e[j][INPUTNO])*(o - )
            {
                /* code */
            }
            
            {
                /* code */
            }
            
        }
    }
}
