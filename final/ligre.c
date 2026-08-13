#include "lireg.h"

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



float absolutefloat(){

}




