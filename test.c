#include <stdio.h>
#include <sys/types.h>
#define absolute(x) ((unsigned int) x ^ 0xFFFFFFFF) + 1

float q_rsqrt(float number)
{
      long i;
      float x2, y;
      const float threehalfs = 1.5F;

      x2 = number * 0.5F;
      y  = number;
      i  = * ( long * ) &y;                       // evil floating point bit level hacking
      i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
      y  = * ( float * ) &i;
      y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
      y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

      return y;
}

float q_rewrite(float number){
      const float threehalfs = 1.5F;
      float x2;
      x2 = number * 0.5F;
      union {
            float y;
            u_int32_t i;

      }u = {number};
      u.i  = 0x5f3759df - (u.i >> 1 );               

      u.y  = u.y * ( threehalfs - ( x2 * u.y * u.y ) );
      u.y  = u.y * ( threehalfs - ( x2 * u.y * u.y ) );
      return u.y;
}


int main(){
      int a = -8;
      float c = -2.0;
      long temp = * (long *) &c;
      temp ^= 0xFFFFFFFF;
      float d = * (float *) &temp;
      unsigned int b = ((unsigned int) a ^ 0xFFFFFFFF) + 1;
      printf("%d , %u\n", a, b);
      printf("%f , %f\n", c, d);

      int x = -5;
      unsigned int y = absolute(x);
      printf("%d , %u\n", x, y);

      float in = 100;
      float out = q_rsqrt(in);
      float out2 = q_rewrite(in);

      printf("%f, %f %f\n", in, out, out2);

}
