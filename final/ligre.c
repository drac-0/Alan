#include "lireg.h"
#include <stdio.h>
#include <stdlib.h>

float Slope(int XYsum, int Xsum, int Ysum, int SXsum){
      return (float)((5 * XYsum) - (Xsum * Ysum)) / (float)((5 * SXsum) - (Xsum * Xsum));
}

float Bias(int XYsum, int Xsum, int Ysum, int SXsum){
      float CalSlope = Slope(XYsum, Xsum, Ysum, SXsum);
      return (((float)Ysum - ((float)Xsum * CalSlope))) / 5;
}

float Ligre(int XYsum, int Xsum, int Ysum, int SXsum, int input){
      return Slope(XYsum, Xsum, Ysum, SXsum) * input + Bias(XYsum, Xsum, Ysum, SXsum);
}

csvDat * readCSV(FILE * csvFile){
      csvDat * Daf = malloc(sizeof(csvDat) * 2048);

      int read = 0;
      int records = 0;

      do {
            read = fscanf(csvFile, "%d, %f\n",
                          &Daf[records].x,
                          &Daf[records].y
                          );

            if (read == 2) records++;

      }while (!feof(csvFile));

      return Daf;
}

