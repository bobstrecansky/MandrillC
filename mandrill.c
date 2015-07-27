#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXAPIKEYS 255
#define APIKEYLENGTH 30

const char *MANDRILLDOTFILE = "mandrillrc";


int addApiKey(){
	FILE * mandrillDotFile;
	char apiKey[30];
	printf ("Enter New API Key: ");
	//fgets (apiKey,30,stdin);
	scanf("%s", apiKey);
	mandrillDotFile = fopen (MANDRILLDOTFILE,"a+");
	fputs (apiKey,mandrillDotFile);
	fclose (mandrillDotFile);
	return 0;
}

void printBanner(){
printf("\n-------------------------------------------------------------\n");
printf("#     #                                              #####\n");
printf("##   ##   ##   #    # #####  #####  # #      #      #     #\n");
printf("# # # #  #  #  ##   # #    # #    # # #      #      #      \n"); 
printf("#  #  # #    # # #  # #    # #    # # #      #      #      \n"); 
printf("#     # ###### #  # # #    # #####  # #      #      #      \n");
printf("#     # #    # #   ## #    # #   #  # #      #      #     #\n");
printf("#     # #    # #    # #####  #    # # ###### ######  #####\n");
printf("-------------------------------------------------------------\n\n");
}

int readDotFile(){
int i;
char * keys[MAXAPIKEYS];
FILE * mandrillDotFile;
mandrillDotFile = fopen(MANDRILLDOTFILE, "r");
	for(i=0; i<MAXAPIKEYS; i++){
		fscanf(mandrillDotFile, "%s", keys[i]);
	}	
}

int dotFileCheck(){
	if( access( MANDRILLDOTFILE, F_OK ) != -1 ) {
    	// file exists
		readDotFile();
	}	 

	else {
		//file doesn't exist
    	printf("It appears you don't have a mandrill dotfile yet.  Create one? (y/n):");
		char resp;
		scanf("%c", &resp);
			if(resp == 'y'){
				addApiKey();
			}
			else return 0;
	}
}

int main(void){
printBanner();
dotFileCheck();

//addApiKey();
}
