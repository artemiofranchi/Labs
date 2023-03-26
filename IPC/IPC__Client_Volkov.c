#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

struct 
{
    long mestype;
    char mes[255];
} messagefrom;

struct
{
    long mestype;
    long mes;
} messageto;



int main(int argc, char **argv){
    key_t key;
    int mesid;
    char str[255];
    char *channel;
    key = ftok("channel.txt", 's');
    //printf("%d\n", key);
    mesid = msgget(key, 0666);
    while (1){
        msgrcv(mesid, &messagefrom, 255, 1, 0);
        strcpy(str, messagefrom.mes);
        if (strcmp(str, "quit") == 0){
            break;
        }
        printf("Str = %s", str);
       // msgsnd(mesid, &messageto, 255, 0);
        
        






    }
    return 0;
}