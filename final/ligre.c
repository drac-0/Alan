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

result * assembled(char * path){
      csvDat * csvDat = calloc(sizeof(csvDat), BUFSIZ);
      mainData * data = readCSVpy(path);

      int Xsum = 0;
      float Ysum = 0;
      int SXsum = 0;
      float XYsum = 0;

      for (int i = 0; i < data->length ; i++){
            Xsum += data->Data[i].x;
            Ysum += data->Data[i].y;
            SXsum += (data->Data[i].x * data->Data[i].x);
            XYsum += (data->Data[i].x * data->Data[i].y);
      }

      float S = Slope(XYsum, Xsum, Ysum, SXsum, data->length);

      float B = Bias(XYsum, Xsum, Ysum, SXsum, data->length);

      int input = 0;

      float Lg = Ligre(XYsum, Xsum, Ysum, SXsum, input,data->length);

      float m = MSE(S, B, data);

      float Rm = RMSE(m);

      float ma = MAE(S, B, data);

      float ma2 = MAE_FuckUnion_FuckFABS(S, B, data);

      free(data->Data);
      free(data);

      result * Ret = malloc(sizeof(result));

      *Ret = (result){S,B, Lg, m,ma,Rm,};

      return Ret;
}


