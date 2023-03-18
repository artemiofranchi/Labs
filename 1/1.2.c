#include <stdio.h>
#include <stdlib.h>

int Binary(int x){
    int a, n = 1;
    n = n << 31;
    for (int i = 0; i < 32; i++){
        a = x&n;
        if (a == n){
            printf("%u", 1);
        }
        else
        {
            printf("%u", 0);
        }
        x = x << 1;
    }
    return 0;
}

int main(){
    int x;
    scanf("%d", &x);
    printf("Binary form of X = ");
    Binary(x);
}
