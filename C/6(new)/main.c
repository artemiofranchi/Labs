#include <stdio.h>
#include <stdlib.h>

int length(FILE* f) {
    char c = '0';
    int count = 0;
    while ((c != EOF) && (c != '\n') && (c != 13)) {
        c = fgetc(f);
       // printf("\np = %d\n", c);
        count++;
    }
    count--;
   // printf("count = %d", count);
    return count;
}

int more(int s, int num, int linenum, FILE* f) {
    char c;
    int p = 0;
    int count;
    long tbos;
    if (!(feof(f))) {
        if (linenum > 1) {
            for(int i = 1; i < linenum; i++) {
                c = fgetc(f);
                while ((c != EOF) && (c != '\n')) {
                    c = fgetc(f);
                }
                if (c == EOF)
                    return 1;
            }
        }
        if (s == 0) {
            for(int i = 0; i < num; i++) {
                c = fgetc(f);
                while ((c != EOF) && (c != '\n')) {
                    printf("%c", c);
                    c = fgetc(f);
                }
                if (c == EOF)
                    return 1;
                else printf("%c", c);
            }
        }
        else {
            for(int i = 0; i < num; i++) {
                c = '0';
                tbos = ftell(f);
                //printf("x %ld", tbos);
                count = length(f);
                if ((count != 0) && (p == 1))
                    p = 0;
                fseek(f, tbos, SEEK_SET);
                while ((c != EOF) && (c != '\n') && (c != 13)) {
                    c = fgetc(f);
               //   printf("\n%d %d %d\n", count, p, c);
                    if ((count == 0) && (p == 0)) {
                        if (c == 13) {
                            c = fgetc(f);
                        }
                        printf("%c", c);
                        p = 1;
                    }
                    else if (count != 0) {
                        printf("%c", c);
                        if (c == 13) {
                            c = fgetc(f);
                            printf("%c", c);
                        }
                    }
                }
                if (c == EOF) return 1;
            }
        }
    }
    printf("-----");
    return 0;
}

int main(int argc, char** argv)
{
    FILE* f = fopen(argv[argc - 1], "r");
    int s = 0, num = 10, linenum = 1;
    for(int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 's') s = 1;
            else num = -atoi(argv[i]);
        }
        if (argv[i][0] == '+') {
            linenum = atoi(argv[i]);
        }
    }
    printf("s = %d\nnum = %d\nlinenum = %d\n", s, num, linenum);
    int end = 0;

    char c = '\n';
   // printf("r%d\n", c);
    while ((c != 'q') && (end != 1)) {
        end = more(s, num, linenum, f);
        c = getchar();
    }
    return 0;
}
