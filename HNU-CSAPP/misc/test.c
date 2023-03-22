#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
  srand(time(NULL));
  int x = random();
  int y = random();
  int z = random();

  double dx = (double) x;
  double dy = (double) y;
  double dz = (double) z;

  //printf("%d", (double)(float)x == dx);
  while ((double)(float)x == dx){
    x = random();
    dx = (double) x;
  }
  printf("1: x=%d\n",x);

  //printf("%d", dx + dy == (double)(x+y));
  while (dx + dy == (double)(x+y)){
    x = random();
    dx = (double) x;
    y = random();
    dy = (double) y;
  }
  printf("2: x=%d y=%d\n",x,y);

  //printf("%d", dx + dy + dz == dz + dy + dx);
/*
  while (dx + dy + dz == dz + dy + dx){
    x = random(); y = random(); z = random();
    dx = (double)x; dy = (double)y; dz = (double)z;
  }
  printf("3: x=%d y=%d z=%d\n",x,y,z);
*/

  //printf("%d", dx * dy * dz == dz * dy * dx);
  while (dx * dy * dz == dz * dy * dx){
    x = random(); y = random(); z = random();
    dx = (double)x; dy = (double)y; dz = (double)z;
  }
  printf("4: x=%d y=%d z=%d\n",x,y,z);

/*
  //printf("%d", dx / dx == dy / dy);
  while (dx / dx == dy / dy){
    x = random(); y = random();
    dx = (double)x; dy = (double)y;
  }
  printf("5: x=%d y=%d\n",x,y);
*/
}
