#include <stdio.h>
#include <stdlib.h>

int binarynumber(int x)
{
 int mask = 1;
    mask = mask << 31;
    for (int i = 0; i < 32; i++){
        printf("%u", (x&mask) == mask);
        x = x << 1;
    }
    return 0;
}

int main1(){
    int x;
    binarynumber(x);
}
