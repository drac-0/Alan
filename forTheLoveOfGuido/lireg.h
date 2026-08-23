#ifndef lireg
#define lireg

#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#define absolute(x) ((unsigned int) x ^ 0xFFFFFFFF) + 1
typedef uint32_t  u32t ;

typedef struct{
      int x;
      float y;
}csvDat;

typedef struct{
      csvDat * Data;
      unsigned int length;
} mainData;

typedef struct{
      float Slope;
      float Bias;
      float Lireg;
      float MSE;
      float MAE;
      float RMSE;
      mainData * Pred;
      float * Y_Predict;
}result;

mainData * Init();

float Slope(float XYsum, int Xsum, float Ysum, int SXsum, int length);

float Bias(float XYsum, int Xsum, float Ysum, int SXsum, int length);

float Ligre(float XYsum, int Xsum, float Ysum, int SXsum, int input, int length);

mainData * readCSV(FILE *csvFile);

mainData * readCSVpy(char * path);

float MSE(float Slope, float Bi, mainData *evaluated);

float RMSE(float MSE);

float MAE(float Slope, float Bi, mainData *evaluated);

float MAE_FuckUnion_FuckFABS(float Slope, float Bi, mainData *evaluated);

result * assembled(char * path);

#endif // !lireg
#define lireg
