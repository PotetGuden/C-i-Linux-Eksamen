#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

//#include "Oppgave4.h"

typedef struct _CCD{
	char digit[17];
	int convert;
	struct _CCD* p;	
} CCD;

int ProcessCreditcardPayment(int a, char* c, char* e, char* n);
int Backendprocesspayment(int a, int64_t c, CCD* p, const char* n, int b);

int main(){
	
	ProcessCreditcardPayment(0,"4242123999999999","","");		 			
}
int ProcessCreditcardPayment(int a, char* cardnumber, char* e, char* n){       	
	int64_t llCreditcard = 0; // C99 type, our compiler supports this...
	//char *i = (char*)c;
	CCD *node = (CCD*) malloc(sizeof(CCD)*4);		// 4 segmenter
	memset(node,0,sizeof(CCD));
	
	//CCD node[4];
	// Create 4 linked structures that holds one 4 digit segment of cardnumber
	int i = 0;
	int j = 0;
	int k = 0;
	for(i = 0; i < 16; i++){
		//node->digit = (int64_t*)cardnumber;
	}
	
	printf("digit: %ld\n", atoi((int64_t)cardnumber));

/*
	printf("utenfor while-loop: node->digit = %s\n\n", node->digit);		
	// Check that card starts with 4242, if not card is from another bank so we fail:
	if(strcmp(node->digit, "4242") != 0){
		printf("CARD IS NOT STARTING WITH 4242, FREE(CC)\n");
		free(node);
		free(node->p->p->p);				
		free(node->p->p);
		free(node->p);
		return 6; 		
	}
	
	// Calculate the cardnumber as a 64 bit integer
	for(j = 12; node; node = node->p, j -=4){    		
		node->convert = atoi(node->digit);
		llCreditcard += ((int64_t)node->convert) * pow(10, j);			
		printf("llCreditCard += %ld * pow(10, j) // aka (%f)  // j = %d\n",((int64_t)node->convert), pow(10,j), j); 
	}
	printf("\nllCreditCard = %ld\n", llCreditcard);			
	
	// If next section is 123x it is a bonus card with cash-back, we send type(x) to backend below: Set j to the type of bonus card
	if(strncmp(node->p->digit, "123", 3) == 0){		
		j = node->p->digit[3];																	
	}
	
	printf("Ascii character: %d, tallverdi: %c\n", j, j);
	// Call backend function:
	Backendprocesspayment(a, llCreditcard, node, n, j);	
	

	free(node->p->p->p);				// FEIL NR 3
	free(node->p->p);
	free(node->p);
	
	
	free(node);

*/
	return 0;
	
}

int Backendprocesspayment(int a, int64_t c, CCD* p, const char* n, int b){






}






