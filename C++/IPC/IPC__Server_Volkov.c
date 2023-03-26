#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>

struct 
{
    long mestype;
    char mes[255];
} messageto;

struct 
{
    long mestype;
    char mes[255];
} messagefrom;



int main(int argc, char **argv){
    key_t key; // ключ
    int mesid; // очередь сообщений
    int shmid; // разделяемая память
    char *buf; // указатель на буфер с разделяемой памятью
    FILE *f;
    char *filename = argv[argc - 1];
    f = fopen(filename, "r+");
    char str[255];
    char *rec1 = malloc(255);
    char *rec2 = malloc(255);
    key = ftok("channel.txt", 's');
    //printf("%d\n", key);
    mesid = msgget(key, 0666 | IPC_CREAT); // создаем очередь сообщений
    shmid = shmget(key, 255, 0666 | IPC_CREAT); // создаем разделяемую память на 255 элементов
    buf = shmat(shmid, NULL, 0); // присоединяем память к адресному пространству процесса
    int strnum = 0;
    while ((fgets(str, 255, f)) != NULL){
        strcpy(messageto.mes, str);
        messageto.mestype = 1;
        msgsnd(mesid, &messageto, 255, 0);
        msgrcv(mesid, &messagefrom, 255, 3, 0);
        strcpy(rec1, buf);
        printf("Number of the string is %d\n", strnum);
        printf("Amount of numbers in the string = %d\n", *rec1);
        messageto.mestype = 2;
        strcpy(messageto.mes, str);
        msgsnd(mesid, &messageto, 255, 0);
        msgrcv(mesid, &messagefrom, 255, 4, 0);
        strcpy(rec2, buf);
        printf("Amount of spaces in the string = %d\n", *rec2);
        strnum++;
    }
    strcpy(messageto.mes, "Q");
    messageto.mestype = 1;
    msgsnd(mesid, &messageto, 255, 0);
    messageto.mestype = 2;
    msgsnd(mesid, &messageto, 255, 0);
    msgctl(mesid, IPC_RMID, NULL);
    shmctl(shmid, IPC_RMID, NULL);
    fclose(f);
    return 0;
}