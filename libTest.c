#include <stdio.h>
#include "final/lireg.h"
#include <fcntl.h>
#include <stdlib.h>


int main(){
      FILE * Pcsv = fopen("./slr_data.csv", "r");
      //mainData * data = readCSV(Pcsv);
      mainData * data = readCSVpy("./slr_data.csv");

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
      printf("input : ");
      scanf("%d", &input);

      float Lg = Ligre(XYsum, Xsum, Ysum, SXsum, input,data->length);
      printf("%f\n", Lg);

      float m = MSE(S, B, data);
      printf("%f\n",m);

      float Rm = RMSE(m);
      printf("%lf\n",Rm);

      float ma = MAE(S, B, data);
      printf("%f\n",ma);

      float ma2 = MAE_FuckUnion_FuckFABS(S, B, data);
      printf("%f\n",ma2);

      //it's time to create array for the Y pred. Therefore i can visualize it later with matplotlib
      //Fuck python

      float * Y_Pred = malloc(sizeof(float) * data->length);

      for (int i = 0 ; i < data->length ; i++){
            Y_Pred[i] = Ligre(XYsum, Xsum, Ysum, SXsum, data->Data[i].x,data->length);
      }

      free(data->Data);
      free(data);
}
