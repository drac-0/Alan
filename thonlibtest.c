#include <stdio.h>
#include "./forTheLoveOfGuido/lireg.h"


int main(){
      result * test = assembled("./slr_data.csv");
      for (int i = 0 ; i < test->Pred->length; i++){
            printf("%f\n", test->Y_Predict[i]);
      }


}
