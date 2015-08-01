#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <curl/curl.h>

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

void curlRequest(){
  CURL *curl;
  CURLcode res;
 
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    /* example.com is redirected, so we tell libcurl to follow redirection */ 
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);

    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
}


int homeSelection(){
int menuSelection;
printf("Make your selection:");
printf("\n1.) Users Calls []");
scanf("%d", &menuSelection);
	switch (menuSelection){
		case '1':
			printBanner();
		default:
			return 0;
	}
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
		homeSelection();
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
