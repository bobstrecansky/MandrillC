#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <curl/curl.h>

// Static Length Definitions
#define MAXAPIKEYS 255
#define APIKEYLENGTH 30

// File Defintiions
const char *MANDRILLDOTFILE = "mandrillrc";

// Function Definitions
int homeSelection();






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


// Make a cURL Request with Specified Parameters
void curlRequest(){
  CURL *curl;
  CURLcode res;
 
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://mandrillapp.com/api/1.0/users/ping.json");
    /* example.com is redirected, so we tell libcurl to follow redirection */ 
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    printf("present");
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
}

// Add an API Key to the #MANDRILLDOTFILE
void addApiKey(){
	FILE * mandrillDotFile;
	char apiKey[30];
	printf ("Enter New API Key: ");
	scanf("%s", apiKey);
	mandrillDotFile = fopen (MANDRILLDOTFILE,"a+");
	fputs (apiKey,mandrillDotFile);
	fclose (mandrillDotFile);
	homeSelection();
}

// Home Menu Selection Switch Statement
int homeSelection(){
int menuSelection;
printf("Make your selection:");
printf("\n1.) Add Additional API Key");
printf("\n2.) Info Request [/users/info.json]");
scanf("%d", &menuSelection);
	switch (menuSelection){

		case 1: addApiKey();
		case 2:	curlRequest();
		default:
			return 0;
	}
}

// Read the API Keys into an Array
void readDotFile(){
FILE *mandrillDotFile;
mandrillDotFile = fopen(MANDRILLDOTFILE, "r");

char apiKeyArray[MAXAPIKEYS];
int i;

	for(i=0; i<MAXAPIKEYS; i++){
		fscanf(mandrillDotFile, "%s", &apiKeyArray[i]);
	}

printf("choose the API key you wish to use:");
//printf("%s", &apiKeyArray[0]);
homeSelection();
}

// Check for the Validity of a the #MANDRILLDOTFILE
int dotFileCheck(){
	if( access( MANDRILLDOTFILE, F_OK ) != -1 ) {
    	// file exists
		//homeSelection();
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
return 0;
}

int main(void){
printBanner();
dotFileCheck();
return 0;
}
