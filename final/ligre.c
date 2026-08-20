#include "lireg.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
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

            else if (read == 0 ) {
                  fscanf(csvFile, "%*[^\n]\n"); // eat the line
            }

      }while (!feof(csvFile));

      Act->length = records;
      Act->Data = Daf;

      return Act;
}

mainData * readCSVpy(char * path){
      FILE * fptr = fopen(path, "r");
      csvDat * Daf = malloc(sizeof(csvDat) * 2048);
      mainData * Act = malloc(sizeof(mainData));
      if (fptr == NULL){
            printf("Failed to open");
            return Act;
      }

      int read = 0;
      int records = 0;

      do {
            read = fscanf(fptr, "%d, %f\n",
                          &Daf[records].x,
                          &Daf[records].y
                          );

            if (read == 2) records++;

            else if (read == 0 ) {
                  fscanf(fptr, "%*[^\n]\n"); // eat the line
            }

      }while (!feof(fptr));

      Act->length = records;
      Act->Data = Daf;

      return Act;
}

float MSE(float Slope, float Bi, mainData * evaluated){
      float SSE = 0;

      for (int i = 0 ; i < evaluated->length; i++){
            float pred = (Slope * evaluated->Data[i].x + Bi);
            SSE += ((evaluated->Data[i].y - pred) * (evaluated->Data[i].y - pred)) ;
      }

      return SSE / evaluated->length;
}

float RMSE(float MSE){
      return sqrt(MSE);
}

float MAE(float Slope, float Bi, mainData *evaluated){
      float SAE = 0;

      for (int i = 0 ; i < evaluated->length; i++){
            float pred = (Slope * evaluated->Data[i].x + Bi);
            SAE += fabs((evaluated->Data[i].y - pred));
      }

      return SAE / evaluated->length;
}

float MAE_FuckUnion_FuckFABS(float Slope, float Bi, mainData *evaluated){
      float SAE = 0;
      u32t temp;

      for (int i = 0 ; i < evaluated->length; i++){
            float E = (evaluated->Data[i].y - (Slope * evaluated->Data[i].x + Bi));
            temp = * (u32t * ) &E;
            temp &= 0x7FFFFFFF;
            E = * (float *) &temp;
            SAE += E;
      }

      return SAE / evaluated->length;
}

mainData * Init(){
      csvDat * csvDat = calloc(sizeof(csvDat), BUFSIZ);
      mainData * ThisIsAllIhave =  calloc(sizeof(mainData), 1);
      unsigned int length = 0;

      ThisIsAllIhave->length = length;
      ThisIsAllIhave->Data = csvDat;

      return ThisIsAllIhave;
}
