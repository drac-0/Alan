#include <stdio.h>
#include <fcntl.h>

struct sales{
      int Pin ;
      float Pout;
}; 


int main(){
      FILE * csv = fopen("./slr_data.csv", "r") ;

      struct sales s1[1024];

      int read = 0;
      int records = 0;


      do{
            read = fscanf(csv, 
                          "%d, %f\n",
                          &s1[records].Pin,
                          &s1[records].Pout);

            printf("%d %lf\n", s1[records].Pin, s1[records].Pout);
            if (read == 2){
                  records++;
            }

      }while (!feof(csv));
      
      fclose(csv);

      for (int i = 0 ; i < records ; i++){
            printf("%d %lf\n", s1[i].Pin, s1[i].Pout);
      }
}
