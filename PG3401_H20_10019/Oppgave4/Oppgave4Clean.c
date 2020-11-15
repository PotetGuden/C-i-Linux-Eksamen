#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

typedef struct _CCD{
	char digit[5];
	int convert;
	struct _CCD* p;	
} CCD;

int ProcessCreditcardPayment(int a, char* c, char* e, char* n);
int Backendprocesspayment(int a, int64_t c, CCD* p, const char* n, int b);

int main(){
	
	ProcessCreditcardPayment(0,"4242123999999999","12/20","");		 			
}
int ProcessCreditcardPayment(int a, char* c, char *e, char* n){       	
	time_t exactTime;
	struct tm * timeinfo;
	
	time(&exactTime);
	timeinfo = localtime(&exactTime);
	printf("Lokal tid: Måned %d År %d\n", timeinfo->tm_mon+1, (timeinfo->tm_year)%100);
	
	int localMonth = timeinfo->tm_mon+1;
	int localYear = (timeinfo->tm_year)%100;
	
	char tempArr[5];
	int count;
	for(count = 0; count < 5; count++){
		tempArr[count] = e[count];
	}
	char *input;
	input = strtok(tempArr,"/");
	int iMonth;
	if((iMonth = atoi(input)) > 12){		
		printf("Du har skrevet inn en ugyldig utløpsmåned\n");
		return 0;
	}
	
	input = strtok(NULL,"\0");
	int iYear = atoi(input);			
	
	printf("Din utløpsdato: %d/%d\n",iMonth,iYear);
	if(iYear < localYear){									
		printf("Ditt kort har utløpt");
	} else if(iYear == localYear && iMonth < localMonth){		
		printf("Ditt kort har utløpt i år");
	} else if(iYear == localYear && iMonth >= localMonth){	
		printf("Ditt kort kommer til å bli utløpt i år");
	} else if(iYear > localYear){								
		printf("Ditt kort har ikke utløpt");
	}
	printf("\n\n");

	int64_t llCreditcard = 0; 
	int j = 0;
	CCD *pc, *cc = (CCD*) malloc(sizeof(CCD));	
	if(!cc) 
		exit(1);
	else 
		pc = cc;		

	memset(cc,0,sizeof(CCD));
	// Create 4 linked structures that holds one 4 digit segment of cardnumber
	while(c[0]){ 					
		pc->digit[j++] = c++[0];
		if(!c[0]){						
			break;																																
		}	
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
	}
				
	// Check that card starts with 4242, if not card is from another bank so we fail:
	if(strcmp(cc->digit, "4242") != 0){
		printf("CARD IS NOT STARTING WITH 4242, FREE(CC)\n"); 
		free(cc->p->p->p);				
		free(cc->p->p);
		free(cc->p);
		free(cc);
		return 6; 		
	}
	
	// Calculate the cardnumber as a 64 bit integer
	for(j = 12, pc = cc; pc; pc = pc->p, j -=4){    		
		pc->convert = atoi(pc->digit);
		llCreditcard += ((int64_t)pc->convert) * pow(10, j);		
		printf("llCreditCard += %ld	* pow(10, j) // aka (%f)  // j = %d\n",((int64_t)pc->convert), pow(10,j), j);  // Fremprovoserer en feil som gjorde at forloopen kjørte 5 ganger.
	}
	
	if(strncmp(cc->p->digit, "123", 3) == 0){				
		j = cc->p->digit[3];	// Henter siste tall i blokk 2 av creditcard
		//j = cc->p->digit[cc->p->digit[3]/((cc->p->digit[3]-'0')%9)];
		printf("\nj = %c\n",j);
	}
	
	// Call backend function:
	Backendprocesspayment(a, llCreditcard, cc, n, j);		
	
	free(cc->p->p->p);		
	free(cc->p->p);
	free(cc->p);
	free(cc);
	return 0;
	
}

int Backendprocesspayment(int a, int64_t c, CCD* p, const char* n, int b){
	return 0;
}






