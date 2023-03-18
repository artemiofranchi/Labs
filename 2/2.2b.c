#include <stdio.h>
#include <stdlib.h>

char *painting(char *u, int m, int n, char x){
    for (int i = 0; i<n; i++){
        for (int j = 0; j<m; j++){
                if (*(u+i*m+j) == x){
                        for (int i1 = 0; i1<n; i1++){
                            *(u+i1*m+j) = '#';
                        }
                        for (int j1 = 0; j1<m; j1++){
                            *(u+i*m+j1) = '#';

                        }
                }
        }
    }
    return u;
}
void *outputt(char *u, int m, int n){
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            printf("%c\t", *(u+i*m+j));
        }
        printf("\n");
    }
}

int main(){
    char x;
    printf("Enter number x: ");
    scanf("%c", &x);
    int n,m;
    printf("Enter matrix's size nxm\n");
    printf("n=");
    scanf("%d",&n);
    printf("m=");
    scanf("%d",&m);
    char matr[n][m];
    char *u = &matr[0][0];

    printf("Enter matrix: \n");
    for (int i = 0; i<n; i++){
        for (int j = 0; j<m; j++){
            char c=getchar();
            if (c=='\n') j--;
           else matr[i][j]=c;
        }
    }

    printf("Matr[n][m]=");
    printf("\n");
    outputt(u,m,n);
    u = painting(u, m, n, x);
    printf("\n");
    printf("Changed matrix: \n");
    outputt(u,m,n);
    return 0;
    }

