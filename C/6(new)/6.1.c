#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lenn(FILE *f){
	char c = 'a';
    	int i = 0;
    	int j = 0;
    	while (c != EOF) {
       	c = fgetc(f);
       	i++;
        	while ((c != EOF) && (c != '\n')){
          		  c = fgetc(f);
          		  i++;
          	}
          	if (i>j){
          	 j = i;
          	}
          	i = 0;
    	}
    	fseek(f, 0, SEEK_SET);
    	return j;
}

int main(int argc, char **argv)
{
    FILE *f, *fnew;
    char *name = argv[argc - 2];
    int n = atoi(argv[argc - 1])+1;
    int counter = 0;
    f = fopen(name, "r+");
    if (f == NULL){
    	printf("Opening error\n");
    } 
    counter = lenn(f);
    //printf("%d\n", counter);
    char mst[counter]; // current string
    char *str; // string's pointer
    fnew = fopen("newfile.txt", "w");
    str = fgets(mst,sizeof(mst),f);
    while (str!=NULL){
    	if (strlen(str)<=n){
    		fputs(str, fnew);
    	}
    	str = fgets(mst,sizeof(mst),f);
    }
    
    
    fclose(f);
    fclose(fnew);
    remove(name);
    rename("newfile.txt", name);
    return 0;
}
