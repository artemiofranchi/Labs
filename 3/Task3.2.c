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
    *(str+i) = '\0';
	str = (char *) realloc(str, b*i);
    return str;
}

char *check(char *s, char *p){
    int i=0;
    int j=0;
    char *nach = NULL;
    int ch = 0;
    int f = 0;
    while (*(s+i)!='\0'){
        if (ch == 0){
            while ((*(s+i) == *(p+j)) && (*(p+j)!='\0') && (*(s+i)!='\0')){
                if (j==0){
                    nach = (s+i);
                }
                j++;
                i++;
            }
            f = i;
            if (*(p+j) == '\0'){
                ch = 1;
            }
        }
        j = 0;
        i++;
    }
    if (ch == 0){
        return NULL;
    }
    else{
        printf("'Tail' of your string: \n");
        printf("%s\n", (s+f));
        return nach;
    }
}

int main(){
    int ind = 0;
    char *s, *p;
    char *adr;
    int dif;
    printf("Enter your string: \n");
    s = readstr();
    printf("Enter substring you want: \n");
    p = readstr();
    if ((s!=NULL)&&(p!=NULL)){
        adr = check(s,p);
        dif = adr - s;
        while (*(p+ind)!='\0'){
            ind++;
        }
        char *newstr;
        while (adr != NULL){
            newstr = (s+(dif+ind));
            adr = check(newstr,p);
            dif = adr - s;
        }
        printf("The substring is no longer contained in the string. \n");
    }
    else{
        printf("Your string or substring is empty!\n");
    }
    free(s);
    free(p);


    return 0;

}
