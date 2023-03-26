#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/shm.h>

struct 
{
    long mestype;
    char mes[255];
} messagefrom;

struct
{
    long mestype;
    char mes[255];
} messageto;



int main(int argc, char **argv){
    key_t key;
    int mesid;
    char str[255] = "1";
    int shmid;
    char *buf; // указатель на буфер с разделяемой памятью
    key = ftok("channel.txt", 's');
    //printf("%d\n", key);
    mesid = msgget(key, 0666);
    shmid = shmget(key, 255, 0666); // создаем разделяемую память на 255 элементов
    buf = shmat(shmid, NULL, 0); // присоединяем память к адресному пространству процесса
    while (strcmp(str, "Q") != 0){
        msgrcv(mesid, &messagefrom, 255, 2, 0);
        strcpy(str, messagefrom.mes);
        int counter = 0;
        for (int i = 0; i < strlen(str); i++){ // подсчет количества пробелов в строке
            if (str[i] == ' '){
                counter++;
            }
        }
        *buf = counter;
        messageto.mestype = 4;
        strcpy(messageto.mes, "ok");
        msgsnd(mesid, &messageto, 255, 0);
    }
    shmdt(buf);
    return 0;
}