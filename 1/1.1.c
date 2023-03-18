#include <stdio.h>
#include <stdlib.h>

int main()
{
    double e;
    double x,xi1,xi2;
    printf("Enter epsilon: ");
    scanf("%lf",&e);
    printf("Enter x: ");
    while (scanf("%lf",&x)){
        if (x >= 0){
                xi1 = 1;
                xi2 = (xi1 + x/xi1)/2;
                while ((xi1 - xi2) >= e || (xi2 - xi1) >=e) {
                    xi1=xi2;
                    xi2=(xi1+x/xi1)/2;
            }
            printf("sqrt(x) = %f\n", xi2);
            printf("sqrt(x) = %g\n", xi2);
            printf("sqrt(x) = %e\n", xi2);
            printf("sqrt(x) = %.10g\n", xi2);
            printf("sqrt(x) = %G\n", xi2);
            printf("sqrt(x) = %E\n", xi2);
        }
        else
        {
            printf("X must be >=0\n");
        }
        printf("Enter new x or print '.': ");
    }

    return 0;
}
