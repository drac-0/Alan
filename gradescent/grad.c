#include <stdio.h>
#include <stdlib.h>
#include "../final/lireg.h"

typedef struct{
      double dc_dm;
      double dc_db;
}GDres;

GDres * gradFunc(mainData * data, double m, double b){
      double len = data->length;
      GDres * fav = malloc(sizeof(GDres));
      fav->dc_db = 0;
      fav->dc_dm = 0;

      for (int i=0 ; i < len; i++){
            double f = (m * data->Data[i].x + b);

            fav->dc_dm += (f - data->Data[i].y) * data->Data[i].x;
            fav->dc_db += (f - data->Data[i].y);
      }

      fav->dc_db = (1/len) * fav->dc_db;
      fav->dc_dm = (1/len) * fav->dc_dm;

      return fav;
}

GDres * DescendingBeingAmonstUs(mainData * data, double alpha, int iterations){

      GDres * Oh = malloc(sizeof(GDres));
      Oh->dc_dm = 0;
      Oh->dc_db = 0;

      for (int i = 0 ; i < iterations; i++){
            GDres * InObl = gradFunc(data, Oh->dc_dm, Oh->dc_db);

            Oh->dc_dm = Oh->dc_dm - alpha * InObl->dc_dm;
            Oh->dc_db = Oh->dc_db - alpha * InObl->dc_db;
            free(InObl);
      }

      return Oh;
}

int main(){
      mainData * data = readCSVpy("../slr_data.csv");
      GDres * test = DescendingBeingAmonstUs(data, 0.0000001, 10000);

      printf("final : %lf, %lf\n", test->dc_dm, test->dc_db);
      free(test);
}
