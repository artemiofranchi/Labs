#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int linecheck = 0;

int lenn(FILE *f, long t){
	char c = 'a';
    	int i = 0;
    	int j = 0;
    	fseek(f, 0, SEEK_SET);
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
    	fseek(f, t, SEEK_SET);
    	return (j+1);
}

void console_enter(int argc, char **argv, int *s, int *num, int *linenum){
    	if (argc > 2) {
        	for (int i = 1; i < argc - 1; i++){
            	if ((argv[i][0] == '-') && (argv[i][1] == 's')){
                	*s = 1;
            	}
            	else if (argv[i][0] == '-'){
                	*num = atoi(argv[i]+1);
            	}
            	else if (argv[i][0] =='+'){
               	 *linenum = atoi(argv[i]+1);
            	}
        	}
    	}
}

int more(FILE *f, int s, int num, int linenum){
	if (feof(f)==0 && num!=0){
		long t = ftell(f);
		int SIZE = lenn(f,t);
		char mst[SIZE]; // current string
    		char *str; // string's pointer
    		int counter = 0; // to count 'empty' strings in a row
    		int i = 1;
		char sym;
		while (i<=linenum && feof(f)==0){
			str = fgets(mst,sizeof(mst),f);
			//printf("%s", str);
			if (feof(f)){
				printf("That's the end of file");
				return 0;
			}
			i++;
		}
    		int j = 1;
    		while (feof(f)==0 && j<=num){
    			if (*(str)=='\n' && counter == 0 && s==1){
    				printf("\n");
    				counter +=1;
    				j++;
    			}
    			else if (s==0 || (s==1 && *(str)!='\n')){
    				printf("%s", str);	
    				counter = 0;				
    				j++;
    			}

    			if (j<=num) str = fgets(mst,sizeof(mst),f);
    		}
    	printf("----------");
    	return 1;
    	}
    	else{
    		return 0;
    	}
}
		
		
int main(int argc, char **argv){
	FILE *f;
	f = fopen(argv[argc-1],"r");
	int s = 0;
	int num = 10;
	int linenum = 1;
	console_enter(argc,argv,&s,&num,&linenum);
	char enter = '\n';
	char c = '\n';
	printf("----------\n");
    	while (c != 'q') {
        	if (more(f, s, num, linenum) == 0){
            		printf("\nNothing more. End of file.\n");
            		break;
        	}
        	linecheck = 1;
        	c = getchar();
    	}
    	if (c=='q') printf("Oops, seems like you decided to abort reading\n");
    	fclose(f);
    	return 0;
}
		
