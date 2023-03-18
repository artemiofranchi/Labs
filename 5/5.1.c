#include <stdio.h>
#include <stdlib.h>
#define BINPRINT(x) do { \
    long long mask = 1; \
    int i=0; \
    mask = mask << (sizeof(x)*8)-1; \
    printf("Binary form of X = "); \
    do { \
    printf("%u", (x&mask) == mask); \
    x = x<<1; \
    i+=1; \
    }while (i<sizeof(x)*8); \
    printf("\n"); \
    } while(0)

int main(){
    int x1 = -91;
    BINPRINT(x1);
    char c=-3;
    if(c) BINPRINT(c); else printf("Zero!\n");
    short sh = 7;
    BINPRINT(sh);
    long x=15;
    if(x) BINPRINT(x); else printf("Zero!\n");
    long long ll = 15;
    BINPRINT(ll);
}
