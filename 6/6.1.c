#include <stdio.h>
#include <stdlib.h>
#define SIZE 512
int main (void)
{
   // ����������, � ������� ����� ������� ��������� �� ��������� ����� ������
    FILE *f, *newf;
    // ����������, � ������� ���������� ����� ���������� ����������� ������
    char str[SIZE];
    //���������, � ������� ����� ������� ����� �������, � ������� ������� ������, ��� NULL ���� ��������� ����� ����� ��� ��������� ������cv]
    char *estr;
    char *strmas[SIZE];
    int n, i=0, len=0;
    int z = 0;
    printf("Enter the number: \n");
    scanf("%d", &n);
    // �������� ����� � ������� ������� ������� ������ � �������� � ����
    // ������ ������
    printf ("Opening: ");
    f = fopen ("test.txt","r+");
   // newf = fopen("newtest.txt","w+");
    // �������� �������� �����
    if (f == NULL) {printf ("error\n"); return -1;}
    else printf ("completed\n");

    printf ("Read lines: \n");
    //������ (���������) ������ �� ����� � ����������� �����
    while (1)
    {
        //������ ����� ������  �� �����
        estr = fgets (str,sizeof(str),f);
        //�������� �� ����� ����� ��� ������ ������
        if (estr == NULL)
        {
         // ���������, ��� ������ ���������: �������� ����
         // ��� ��� ������ ������
         if ( feof (f) != 0)
         {
            //���� ���� ����������, ������� ��������� � ����������
            //������ � ������� �� ������������ �����
            printf ("\nReading is over\n");
            break;
         }
         else
         {
            //���� ��� ������ ��������� ������, ������� ���������
            //�� ������ � ������� �� ������������ �����
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
      //���� ���� �� ����������, � �� ���� ������ ������
      //������� ��������� ������  �� �����
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
    // ��������� ����
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
