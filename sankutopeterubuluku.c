#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include<math.h>

#define LOOP 100

static uint32_t xorsft_x = 123456789;
static uint32_t xorsft_y = 362436069;
static uint32_t xorsft_z = 521288629;
static uint32_t xorsft_w = 88675123;

void initrand(uint32_t seed){
    do {
        seed = seed*1812433253 + 1; seed ^= seed<<13; seed ^= seed>>17;
        xorsft_x = 123464980 ^ seed;
        seed = seed*1812433253 + 1; seed ^= seed<<13; seed ^= seed>>17;
        xorsft_y = 3447902351 ^ seed;
        seed = seed*1812433253 + 1; seed ^= seed<<13; seed ^= seed>>17;
        xorsft_z = 2859490775 ^ seed;
        seed = seed*1812433253 + 1; seed ^= seed<<13; seed ^= seed>>17;
        xorsft_w = 47621719 ^ seed;
    } while(xorsft_x==0 && xorsft_y==0 && xorsft_z==0 && xorsft_w==0);
}

double urand(){
    uint32_t t;
    t = xorsft_x ^ (xorsft_x<<11);
    xorsft_x = xorsft_y;
    xorsft_y = xorsft_z;
    xorsft_z = xorsft_w;
    xorsft_w ^= t ^ (t>>8) ^ (xorsft_w>>19);
    return ((xorsft_x+0.5) / 4294967296.0 + xorsft_w) / 4294967296.0;
}

int main(){
    int i;
    initrand((unsigned int)time(NULL));

    int x, sankahi = 0;
    int ave = 0;
    x = LOOP * log2(LOOP);
    printf("フェアだとされる金額は%dです。\n", x);
    for(int k=0; k<100; k++){
      sankahi = 0;
      for(i=0; i<LOOP; i++){
        int mem = 1;
        int j = 0;
        while(1){
          if(j == 0){
            if(urand() >= 0.5) break;
          } else {
            if(urand() < 0.5){
              // printf("裏");
              mem *= 2;
            }
            else {
              // printf("表\n");
              break;
            }
          }
          sankahi += mem;
          j++;
        }
      }
      // printf("獲得金は%dです。\n", sankahi);
      ave += sankahi;
    }
    printf("獲得金の平均は%dです。\n", ave/100);
    return 0;
}
