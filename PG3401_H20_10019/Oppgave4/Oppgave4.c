#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "Oppgave4.h"

typedef struct _CCD{
	char digit[5];
	int convert;
	struct _CCD* p;	// "All identifiers that begin with an underscore and either an uppercase letter or another underscore are always reserverd for any use" fra ISO c99 p7.1.3  -   Har ikke noe å si i dette tilfelle, men er egentlig ikke lurt å gi navn på denne måten ettersom det en gang i fremtiden kan bli reservert
} CCD;

int ProcessCreditcardPayment(int a, char* c, char* e, char* n);
int Backendprocesspayment(int a, int64_t c, CCD* p, const char* n, int b);

int main(){
	
	ProcessCreditcardPayment(0,"4242123099999999","","");		 			// Første string må være 4242 ellers kræsj 
}
int ProcessCreditcardPayment(int a, char* c, char* e, char* n){       		// *e brukes ikke, int a/char n -> backend
	int64_t llCreditcard = 0; // C99 type, our compiler supports this...
	char *i = (char*)c;
	int j = 0;
	CCD *pc, *cc = (CCD*) malloc(sizeof(CCD));		// malloc 1
	if(!cc) 
		exit(1);
	else 
		pc = cc;		

	memset(cc,0,sizeof(CCD));
	// Create 4 linked structures that holds one 4 digit segment of cardnumber
	while(i[0]){ 
		pc->digit[j++] = i++[0];
		if(!i[0]){						// Sette if-setning her for å slippe unna å lage siste pointer, som vil ødelegge for for-loopen senere..
			break;																																// FEIL NR 2
		}
		printf("pc->digit[j++] = i++[0]  er det samme som: %c = %c\n", pc->digit[j-1], (i-1)[0]);	// TEST   // (i-1)=forrige pointer fordi vi har brukt i++[0]
		if(strlen(pc->digit) == 4){		
			pc->p = (CCD*) malloc(sizeof(CCD));	// mallco 4x
			if(!pc->p) 
				exit(1);
			else{
				memset(pc->p,0,sizeof(CCD));
				pc = pc->p;
				j = 0;
			}
		}
		printf("pc->digit = %s\n", pc->digit);	// TEST
	}
	
	printf("utenfor while-loop: pc->digit = %s\n\n", pc->digit);				// TEST
	// Check that card starts with 4242, if not card is from another bank so we fail:
	if(strcmp(cc->digit, "4242") != 0){
		printf("CARD IS NOT STARTING WITH 4242, FREE(CC)\n"); // TEST
		free(cc);
		free(cc->p->p->p);				// FEIL NR 3
		free(cc->p->p);
		free(cc->p);
		return 6; 		
	}
	
	// Calculate the cardnumber as a 64 bit integer
	for(j = 12, pc = cc; pc; pc = pc->p, j -=4){    		// ville egentlig loopet 5 ganger, men har gjort en fiks lenger opp i koden
		pc->convert = atoi(pc->digit);
		llCreditcard += ((int64_t)pc->convert) * pow(10, j);			// Kanskje caste pow til in64_t
		printf("llCreditCard += %ld * pow(10, j) // aka (%f)  // j = %d\n",((int64_t)pc->convert), pow(10,j), j); // TEST
	}
	printf("\nllCreditCard = %ld\n", llCreditcard);			// 4242 0000 0000 000 <- ble output i starten..
	
	// If next section is 123x it is a bonus card with cash-back, we send type(x) to backend below: Set j to the type of bonus card
	if(strncmp(cc->p->digit, "123", 3) == 0){				//Triggres ikke..
		//printf("her skjer det noe\n");
		j = cc->p->digit[3];								// fjerde tall i andre digit segment    											// FEIL NR 1
		//printf("Hei: %d\n",cc->p->digit[cc->p->digit[3]/((cc->p->digit[3]-'0')%9)]);							// fjern all den stygge koden for å fikse feil
		//        1239		  '9' 		/		(('9'-'0') % 9) === 0				(9/0) = feil
		
	}
	printf("Ascii character: %d, tallverdi: %c\n", j, j);
	// Call backend function:
	Backendprocesspayment(a, llCreditcard, cc, n, j);		// a = int a fra argument, n = char *N fra argument
	

	free(cc->p->p->p);				// FEIL NR 3
	free(cc->p->p);
	free(cc->p);
	
	
	free(cc);
	return 0;
	
}

int Backendprocesspayment(int a, int64_t c, CCD* p, const char* n, int b){






}






