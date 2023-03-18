#include <stdio.h>
#include <stdlib.h>
struct list{
    char *field;
    struct list *next;
} list;


int main(){
    FILE *f;
    char *estr;
    char str[50];
    int i = 0;
    char *strmas[50];
    f = fopen ("test.txt","r+");
    while (estr!=NULL)
    {
        if (i!=0){
            printf("%s", strmas[i]);
        }
        //Чтение одной строки  из файла
        estr = fgets (str,sizeof(str),f);
        strmas[i]=(char *)malloc(50);
        *(strmas+i)=*(estr);
        printf("%s", strmas[i]);
        i++;
    }
    int j=0;
    printf("\n");
    while (j!=i){
        printf("%s\n", strmas[j]);
        j++;
    }
    return 0;
}
