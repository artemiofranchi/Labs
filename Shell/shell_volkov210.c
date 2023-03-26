#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#define extramem 128

char *readstr(){ // reading the string
    int strsize = extramem;
    char *str = (char *)malloc(strsize*sizeof(char));
    int symb = fgetc(stdin);
    int i = 0;
    int j = 0;
    if (symb == EOF || symb == '\n'){
            str[i]='\0';
            return str;
    }
    else{
        int checker = 0;
        //str[i] = symb;
        while (symb!=EOF && symb!='\n'){
            //if (i>=strsize){
            //    strsize+=extramem;
            //    str = realloc(str, strsize);
            //}
            //i++;
            if (symb == ' '){
                str[i] = symb;
                while (symb == ' ') symb = fgetc(stdin);
            }
            else if (symb == '|' && i > 0){
                if (str[i-1] != ' ' && str[i-1] != '|'){
                    str[i] = ' ';
                    i++;
                }
                str[i] = '|';
                symb = fgetc(stdin);
                //printf("Symb = %c\n", symb);
                if ((symb != ' ') && (symb != '|')){
                    str[i+1] = ' ';
                    i++;
                }
            }
            else{
                str[i]=symb;
                symb = fgetc(stdin);
            }
            i++;
            //printf("current str = %s\n", str);
        }
        if (symb == EOF || symb == '\n'){
            str[i]='\0';
            return str;
        }
    }
}


int ind = 0;
void linedivision(char *str, char *arrofstr1[]){ // Dividing the line from the terminal - making an array of strings(commands)
    int memory = extramem;
    char *pointer;
    pointer = strtok(str, " ");
    while (pointer != NULL){
        arrofstr1[ind] = pointer;
        ind++;
        pointer = strtok(NULL, " ");
    }
    arrofstr1[ind] = "\0";
}



int idir = 0;
int *redirection(char **arrayy, int descriptorarray[]){ // redirecting input/output if ">" or "<" or ">>"
    int rinput = -1;
    int routput = -1;
    char *operations[3];
    operations[0] = "<";
    operations[1] = ">";
    operations[2] = ">>";
    char *fname;
    int checker = -1;
    int lens = 0;
    while (arrayy[lens] != NULL){
        //printf("Member = %s\n", arrayy[lens]);
        lens++;
    }
    for (int i = 0; i < lens; i++){
        for (int j = 0; j < 3; j++){
            //printf("Comparison : %s = %s\n", arrayy[i], operations[j]);
            if (strcmp(arrayy[i],operations[j]) == 0 && (i+1) != (lens)){
                checker = j;
                //printf("checker = %d\n", checker);
                fname = arrayy[i+1]; // name of the file, connected to the redirection
            }
        }
        //printf("Member = %s\n", arrayy[i]);
        if (checker == 0){
            rinput = open(fname, O_RDONLY);
        }
        else if (checker == 1){
            routput = open(fname, O_WRONLY|O_CREAT|O_TRUNC, S_IREAD|S_IWRITE);
        }
        else if (checker == 2){
            routput = open(fname, O_WRONLY|O_CREAT|O_APPEND, S_IREAD|S_IWRITE);
        }
    }
    descriptorarray[0] = rinput;
    descriptorarray[1] = routput;
}


int execution(char **arrofstr, int *indx){
    int systemstatus = 0;
    int background = 0;
    int i = *indx;
    int j = i;
    while ((strcmp(arrofstr[j],"&") != 0) && (strcmp(arrofstr[j],"|") != 0) && (strcmp(arrofstr[j],";") != 0) && (strcmp(arrofstr[j], "\0") != 0) && strcmp(arrofstr[j], "||")!= 0 && strcmp(arrofstr[j], "&&") != 0){
        j++;
    }
    //printf("i = %d, j = %d\n", i,j);
    if (strcmp(arrofstr[j], "&") == 0){
        background = 1;
    }
    char *currentarray[j-i+1];
    for (int k = 0; k < (j-i); k++){
        currentarray[k] = arrofstr[i+k];
        //printf("Currentarray elem = %s\n", currentarray[k]);
    }
    int s = j - i;
    currentarray[s] = NULL;
    //printf("Currentarray elem = %s\n", currentarray[s]);
    if (background){
        int k = *indx;
            while (strcmp(arrofstr[k],"&") != 0)
                k++;
            *indx = k++;
            if (fork() == 0) {
                if (fork() == 0) { // внук
                    signal(SIGINT, SIG_IGN);
                    int fd[2];
                    fd[0] = open("/dev/null", O_RDONLY); // Фоновый процесс не имеет доступа к терминалу, т.е. не должен читать со стандартного ввода (это достигается перенаправлением стандартного ввода на файл устройства /dev/null, чтение из которого сразу дает EOF).
                    dup2(fd[0], 0);
                    if (execvp(currentarray[0], currentarray) == -1){
                        systemstatus = -1;
                    }
                }
                else {
                    exit(0);
                }
            }
            else {
                wait(NULL);
            }
    }
    else{
        j++;
        *indx = j;
        if (fork() == 0){
            int descriptorarray[2];
            redirection(currentarray, descriptorarray);
            int input;
            int output;
            input = descriptorarray[0], output = descriptorarray[1];
            if (descriptorarray[0]!= -1 || descriptorarray[1] != -1){
                //printf("%d\n", input);
                //printf("%d\n", output);
                int change = 0;
                if (input!=-1){
                    dup2(input, 0);
                    change += 2;

                }
                if (output!=-1){
                    dup2(output, 1);
                    change += 2;
                }
                //printf("sssssssss\n");
                int delcheck = 0;
                char *newcurarray[s-change+1];
                //printf("S= %d", s);
                int p = 0;
                for (int l = 0; l < s; l++){
                    if (strcmp(currentarray[l], ">") != 0 && strcmp(currentarray[l], ">>") != 0 && strcmp(currentarray[l], "<") != 0 && delcheck == 0){
                        newcurarray[p] = currentarray[l];
                        //printf("NEW : %s\n", newcurarray[l]);
                        //printf("OLD : %s\n", currentarray[l]);
                        p++;
                    }
                    else{
                        if (delcheck == 0) delcheck = 1;
                        else if (delcheck == 1) delcheck = 0;
                    }
                }
                newcurarray[p] = NULL;
                //for (int k = 0; k<s-1; k++){
                //    printf("ELEM = %s\n", newcurarray[k]);
                //}
                if (execvp(newcurarray[0], newcurarray) == -1){
                    systemstatus = -1;
                }
            }
            else{
               // printf("CCCommand = %s\n", currentarray[0]);
                if (execvp(currentarray[0], currentarray) == -1){
                    systemstatus = 1;
                }
                //printf("status in execution = %d\n", systemstatus);
                
            }
            exit(systemstatus);
        }
        else{
            wait(&systemstatus);
        }
    }
    if (systemstatus != 0){
        systemstatus = 1;
    }
    return systemstatus;
}


int conveyor(char **arrofstr, int *indx){
    int fd[2];
    int commnds = 0;
    int i = *indx;
    int j = *indx;
    int lastchannel = 0;
    int systemstatus = 0;
    int status = 0;
    while (strcmp(arrofstr[i],"&") != 0 && strcmp(arrofstr[i],"|") != 0 && strcmp(arrofstr[i],";") != 0 && strcmp(arrofstr[i], "\0") != 0 && strcmp(arrofstr[i], "||")!= 0 && strcmp(arrofstr[i], "&&") != 0){
        pipe(fd);
        if (fork() == 0){
            i = *indx;
            if (commnds>0){
                dup2(lastchannel, 0); // передаем вывод предыдущей команды на вход следующей
                close(lastchannel);
            }
            while (strcmp(arrofstr[i],"|") != 0 && strcmp(arrofstr[i],"&") != 0 && strcmp(arrofstr[i],";") != 0 && strcmp(arrofstr[i], "\0") != 0 && strcmp(arrofstr[i], "||") != 0 && strcmp(arrofstr[i], "&&") != 0){
                i++;
            }
            if (strcmp(arrofstr[i], "|") == 0){  // смотрим, есть ли еще команды
                dup2(fd[1], 1);  // делаем стандартным выводом файловый дескриптор канала для записи
            }
           // printf("command = %s\n", arrofstr[*indx]);
            close(fd[0]);
            close(fd[1]);
           //printf("I =(conv) %d\n", i);
            //printf("command = %s\n", arrofstr[*indx]);
            status = execution(arrofstr, indx);
            //printf("returned status = %d\n", status);
            exit(status);
        }
        else {
            lastchannel = fd[0];
            close(fd[1]);
            while (strcmp(arrofstr[i],"|") != 0 && strcmp(arrofstr[i],"&") != 0 && strcmp(arrofstr[i],";") != 0 && strcmp(arrofstr[i], "\0") != 0 && strcmp(arrofstr[i], "||") != 0 && strcmp(arrofstr[i], "&&") != 0){
                i++;
            }
            if (strcmp(arrofstr[i], "|") == 0){
                commnds++;
                i++;
            }
            *indx = i;
            //printf("I =(conv) %d\n", i);
        }
    }
    while (commnds >= 0){
        wait(&status);
        commnds-=1;
    }
    if (status != 0){
        status = 1;
    }
   // printf("status = %d\n", status);
    *indx = j;
    //printf("I =(conv) %d\n", i);
    return status;
}

void cycle(char **arrofstr) {
    int i = 0;
    int statuscheck = 0;
    while (strcmp(arrofstr[i], "\0") != 0){
        printf("status in the cycle = %d\n", statuscheck);
        printf("Current element is %s\n", arrofstr[i]);
        printf("I = %d\n", i);
        if (strcmp(arrofstr[i], "&&") == 0 && statuscheck == 1){
            while (strcmp(arrofstr[i],"&") != 0 || strcmp(arrofstr[i],"|") != 0 || strcmp(arrofstr[i],";") != 0 || strcmp(arrofstr[i], "\0") != 0 || strcmp(arrofstr[i], "||")!= 0 || strcmp(arrofstr[i], "&&") != 0){
                i++;
            }
        }
        else if (strcmp(arrofstr[i], "||") == 0 && statuscheck == 0){
            while ((strcmp(arrofstr[i],"&") != 0) && (strcmp(arrofstr[i], "|") != 0) && (strcmp(arrofstr[i], ";") != 0) && (strcmp(arrofstr[i], "\0") != 0) && (strcmp(arrofstr[i], "||")!= 0) && (strcmp(arrofstr[i], "&&") != 0)){
                printf("arrofstr[i] = %s\n", arrofstr[i]);
                if (strcmp(arrofstr[i], "\0") == 0){
                    printf("WHAT\n");
                }
                i++;
                printf("iiiiiiiiii = %d\n", i);
            }
        }
        else if (strcmp(arrofstr[i], "&&") != 0 && strcmp(arrofstr[i], "||") != 0){
            statuscheck = conveyor(arrofstr, &i);
            if (strcmp(arrofstr[i], "\0") != 0) i++;
        }
        else{
            if (strcmp(arrofstr[i], "\0") != 0) i++;
        }
    }
}


int main(int argc, char **argv){
    while (1){
        char *str;
        str = readstr();
       // printf("str = %s\n", str);
        char *arrofstr[extramem];
        ind = 0;
        linedivision(str, arrofstr);
       // for (int i = 0; i < ind; i++){
       //     printf("%s\n", arrofstr[i]);
       // }
        cycle(arrofstr);
    }
    return 0;
}
