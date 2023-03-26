#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rread(FILE *f){
	char c = 'a';
    	int i = 0;
    	while (c != EOF) {
       	c = fgetc(f);
        	while ((c != EOF) && (c != '\n'))
          		  c = fgetc(f);
        	i++;
    	}
    	fseek(f, 0, SEEK_SET);
    	return i;
}


int main(int argc, char **argv){
	printf("I AM HERE, HELP\n");
	char c = 'a';
	int num;
	char *name1 = argv[argc - 2];
	char *name2 = argv[argc - 1];
	FILE *f, *fres;
	f = fopen(name1, "r+");
	fres = fopen(name2, "w");
	int count = rread(f);
	//long mas[count];
	//int leng[count];
	//int len = 0;
	int i = 0;
	printf("%d\n",i);
	
	fclose(f);
	fclose(fres);
}
//while (c!=EOF){
	//	mas[i] = ftell(f);
	//	printf("%ld\n", mas[i]);
	//	while (c!='\n'){
	//		len += 1;
	//		c = getc(f);
	//	}
	//	leng[i] = len;
	//	len = 0;
	//}
