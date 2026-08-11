#include <stdio.h>
#include <math.h>

int main(){
      int arrp[5][2] = {
            {1,3},
            {2,4},
            {3,7},
            {4,8},
            {5,10}
      };

      int Xsum = 0;
      int Ysum = 0;
      int SXsum = 0;
      int XYsum = 0;

      for (int i = 0 ; i < 5; i++){
            Xsum += arrp[i][0];
            Ysum += arrp[i][1];
            SXsum += (arrp[i][0] * arrp[i][0]);
            XYsum += (arrp[i][0] * arrp[i][1]);
      }

      printf("Xsum = %d\nYsum = %d\nSXsum = %d\n", Xsum, Ysum, SXsum);
      printf("XYsum = %d\n", XYsum);

      float Slope = (float)((5 * XYsum) - (Xsum * Ysum)) / (float)((5 * SXsum) - (Xsum * Xsum));
      printf("%d, %d, %d, %d\n", 5* XYsum, Xsum * Ysum, 5 * SXsum, Xsum * Xsum);

      printf("%f\n", Slope);

      float Bias = ((float)Ysum - ((float)Xsum * Slope)) / 5;
      int input ;
      printf("input : ");
      scanf("%d", &input);
      float ff = Slope * input + Bias;

}
