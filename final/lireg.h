#ifndef lireg
#define lireg

#include <fcntl.h>
#include <stdio.h>

typedef struct{
      int x;
      float y;
}csvDat;

float Slope(int XYsum, int Xsum, int Ysum, int SXsum);

float Bias(int XYsum, int Xsum, int Ysum, int SXsum);

float Ligre(int XYsum, int Xsum, int Ysum, int SXsum, int input);

csvDat * readCSV(FILE *csvFile);

#endif // !lireg
#define lireg
