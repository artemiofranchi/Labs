#include <stdio.h>
#include <stdlib.h>
#define b 4

char *readstr(){
    char *str;
    char sym;
    str = (char *) malloc (b);
    sym = getchar();
    int i = 0;
    while ((sym != '\n') && (sym != EOF)){
        *(str+i) = sym;
        i++;
        str = (char *) realloc(str, i*b);
        sym = getchar();
    }
    return str;
}
int main(){
    char *s;
    printf("Enter your string: \n");
    s = readstr();
    printf("%s",s);
    free(s);
    return 0;

}
