#include <stdio.h>
#include <stdlib.h>
#define SIZE 512
int main (void)
{
   // Переменная, в которую будет помещен указатель на созданный поток данных
    FILE *f, *newf;
    // Переменная, в которую поочередно будут помещаться считываемые строки
    char str[SIZE];
    //Указатель, в который будет помещен адрес массива, в который считана строка, или NULL если достигнут коней файла или произошла ошибкаcv]
    char *estr;
    char *strmas[SIZE];
    int n, i=0, len=0;
    int z = 0;
    printf("Enter the number: \n");
    scanf("%d", &n);
    // Открытие файла с режимом доступа «только чтение» и привязка к нему
    // потока данных
    printf ("Opening: ");
    f = fopen ("test.txt","r+");
   // newf = fopen("newtest.txt","w+");
    // Проверка открытия файла
    if (f == NULL) {printf ("error\n"); return -1;}
    else printf ("completed\n");

    printf ("Read lines: \n");
    //Чтение (построчно) данных из файла в бесконечном цикле
    while (1)
    {
        //Чтение одной строки  из файла
        estr = fgets (str,sizeof(str),f);
        //Проверка на конец файла или ошибку чтения
        if (estr == NULL)
        {
         // Проверяем, что именно произошло: кончился файл
         // или это ошибка чтения
         if ( feof (f) != 0)
         {
            //Если файл закончился, выводим сообщение о завершении
            //чтения и выходим из бесконечного цикла
            printf ("\nReading is over\n");
            break;
         }
         else
         {
            //Если при чтении произошла ошибка, выводим сообщение
            //об ошибке и выходим из бесконечного цикла
            printf ("Error of file reading\n");
            break;
         }
        }
        if (strlen(estr)<=n+1){
            printf("STR: %s\n",estr);
            strmas[i]=estr;
            len = strlen(estr);
            printf("MASELEM: %s\n",*(strmas+i));
            printf("i: %d\n", i);
            z = i;
            i+=1;
           // fputs(str,newf);
        }
      //Если файл не закончился, и не было ошибки чтения
      //выводим считанную строку  на экран
        printf ("%s",str);
    }
    printf("I=%d\n",i);
    printf("Your mas:\n");
    int j=0;
    printf("%s", *(strmas));
    //while (j!=i){
    //    printf("%s", strmas[j]);
     //   j+=1;
   // }
    // Закрываем файл
    printf ("File close: \n");
    if ( fclose (f) == EOF) printf ("ERROR \n");
    else printf ("completed\n");
    f = fopen ("test.txt","w+");
    printf ("Opening: ");
    if (f == NULL) {printf ("error\n"); return -1;}
    else printf ("completed\n");

    printf ("Read lines: \n");
    if ( fclose (f) == EOF) printf ("ERROR \n");
    else printf ("completed\n");

    return 0;
}
