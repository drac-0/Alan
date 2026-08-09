#include <stdio.h>
#include "final/lireg.h"
#include <fcntl.h>
#include <stdlib.h>

int main(){
      FILE * Pcsv = fopen("./slr_data.csv", "r");
      csvDat * data = readCSV(Pcsv);

      int Xsum = 0;
      int Ysum = 0;
      int SXsum = 0;
      int XYsum = 0;
      unsigned int i = 0;

      while(data[i].x != NULL){
            Xsum += data[i].x;
            Ysum += data[i].y;
            SXsum += (data[i].x * data[i].x);
            XYsum += (data[i].x * data[i++].y);
      }

      float S = Slope(XYsum, Xsum, Ysum, SXsum);

      float B = Bias(XYsum, Xsum, Ysum, SXsum);

      int input = 77;

      float Lg = Ligre(XYsum, Xsum, Ysum, SXsum, input);

      printf("%lf", Lg);



}
