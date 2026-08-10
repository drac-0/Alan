#include "lireg.h"
#include <stdlib.h>

float Slope(float XYsum, int Xsum, float Ysum, int SXsum, int length){
      return (float)((length * XYsum) - (Xsum * Ysum)) / (float)((length * SXsum) - (Xsum * Xsum));
}

float Bias(float XYsum, int Xsum, float Ysum, int SXsum, int length){
      float CalSlope = Slope(XYsum, Xsum, Ysum, SXsum, length);
      return ((Ysum - ((float)Xsum * CalSlope))) / length;
}

float Ligre(float XYsum, int Xsum, float Ysum, int SXsum, int input, int length){
      return Slope(XYsum, Xsum, Ysum, SXsum,length) * input + Bias(XYsum, Xsum, Ysum, SXsum, length);
}

mainData * readCSV(FILE * csvFile){
      csvDat * Daf = malloc(sizeof(csvDat) * 2048);
      mainData * Act = malloc(sizeof(mainData));

      int read = 0;
      int records = 0;

      do {
            read = fscanf(csvFile, "%d, %f\n",
                          &Daf[records].x,
                          &Daf[records].y
                          );

            if (read == 2) records++;

      }while (!feof(csvFile));

      Act->length = records;
      Act->Data = Daf;

      return Act;
}

