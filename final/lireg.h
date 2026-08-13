#ifndef lireg
#define lireg

#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define absolute(x) ((unsigned int) x ^ 0xFFFFFFFF) + 1

typedef struct{
      int x;
      float y;
}csvDat;

typedef struct{
      csvDat * Data;
      unsigned int length;
} mainData;

float Slope(float XYsum, int Xsum, float Ysum, int SXsum, int length);

float Bias(float XYsum, int Xsum, float Ysum, int SXsum, int length);

float Ligre(float XYsum, int Xsum, float Ysum, int SXsum, int input, int length);

mainData * readCSV(FILE *csvFile);

float MSE(float Slope, float Bi, mainData *evaluated);

float RMSE(float MSE);

float MAE(float Slope, float Bi, mainData *evaluated);

float absolutefloat();


#endif // !lireg
#define lireg
