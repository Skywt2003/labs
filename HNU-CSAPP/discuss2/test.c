#include<stdio.h>

int main(){
    int i = 0;
    int a[] = {10, 20, 30};
    int r = 1 * a[i++] + 2 * a[i++] + 3 * a[i++];
    int j = 4;
    j = j++;
    printf("r=%d,j=%d", r, j);
}
