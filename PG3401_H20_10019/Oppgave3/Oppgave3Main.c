// ex3.c: Lession 7, exercise 3
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Oppgave3.h"

void PrintList (LISTHEAD *ppHead);
int ContinueOrNot();

int main (void){

	LISTHEAD *ppHead = (LISTHEAD*) malloc (sizeof(LISTHEAD));
   	ppHead->pHead = NULL;
   	ppHead->pTail = NULL;
   
   	int iRc = OK;   	
   	
	char input;
	char *szBuffer = malloc(sizeof(char*));
	int *number = malloc(sizeof(int*));
	memset(number,0,sizeof(int*));
	
	while(input != 'x'){		// midtlertidig løsning
		if(input != '\n'){		// for å slippe unna loop nr.2 pga enter knappen og getchar()
				printf("Du får nå 5 alternativer:\n");
			   	printf("1. Legge til et element i en liste\n");
			   	printf("2. Hente ut element N fra listen (du velger N)\n");
			   	printf("3. Hente ut element som matcher navn og får tilbake element nr den har\n");
			   	printf("4. Sletter alle elementer med ditt gitte navn\n");
			   	printf("5. Sletter alle elementer som har alder mindre enn det du oppgir\n\n");
			   	
			   	printf("OBS: Husk at du må legge til minst ett element først\n");
			   	printf("Skriv inn tallet til det alternativet du vil gjøre noe med: ");	   	
		}
		
		input = getchar();
		
		
		
		switch(input){
			case '1':
				printf("Du har valgt 1: Legg til et element\n\n");
				printf("Skriv inn et navn og alder (med mellomrom imellom): ");
				scanf("%s %d", szBuffer, &number);
				AddToList(&ppHead, szBuffer, number);				// Legger til bruker input i linked list
				//free(number);
				printf("\nDu har lagt til '%s' inn i databasen\n\n", szBuffer);
				PrintList(ppHead);									// Printer ut hele current linked list
				if(ContinueOrNot() == ERROR) input = 'x';				// Spør bruker om de vil fortsette, alt utenom "yes" vil resultere i exit
				break;
			case '2':
				printf("Du har valgt 2: Hent ut et element ved å oppgi en index\n");
				printf("Skriv inn et tall: ");
				scanf("%s", szBuffer);
				number = atoi(szBuffer);
				GetElement(&ppHead, number);						// Henter en "index" fra linked list
				//free(number);
				printf("\n");
				if(ContinueOrNot() == ERROR) input = 'x';
				break;
			case '3':
				printf("Du har valgt 3: Finn index ved å oppgi navn: ");
				scanf("%s", szBuffer);
				GetElementByName(&ppHead, szBuffer);				// Henter navn og index utifra navnet bruker oppgir
				printf("\n");
				if(ContinueOrNot() == ERROR) input = 'x';
				break;
			case '4':
				printf("Du har valgt 4: Slett et element ved å oppgi navn: ");
				scanf("%s", szBuffer);
				DeleteNameNode(&ppHead, szBuffer);					// Sletter navn bruker oppgir fra linked listen
				printf("\n");
				PrintList(ppHead);
				if(ContinueOrNot() == ERROR) input = 'x';
				break;
			case '5':
				printf("Du har valgt 5: Slett alle elementer hvor alder er mindre enn ditt tall: ");
				scanf("%d", &number);
				RemoveAllLessThanN(&ppHead, number);
				//free(number);
				printf("\n");
				PrintList(ppHead);
				if(ContinueOrNot() == ERROR) input = 'x';
				break; 
			case '\n':	// For å slippe unna med scanf og enter-knappen
				break;
			default: 
				printf("Du har skrevet inn noe ugyldig\n");
				exit(1); // FIKS DETTE
				break;
		}
	}
   	
	free(ppHead);
	free(szBuffer);
	free(number);
	return 0;
}

int ContinueOrNot(){
	int iRc = ERROR;
	char *yesOrNo = malloc(sizeof(char*));
	printf("Hvis du vil fortsette skriv \"ja\": ");
	scanf("%s", yesOrNo);
	if(strcmp(yesOrNo, "ja") == 0){
		printf("\n");					// Bare for å lage et mellomrom mellom neste tekst
		iRc = OK;
		free(yesOrNo);
		return iRc;
	} else{
		printf("Closing the program...\n");
		free(yesOrNo);
		return iRc;
	}
}

void PrintList (LISTHEAD *ppHead){
   
   int i = 0;
   LIST *curr = ppHead->pHead;
   printf("The currently linked list is as follows:\n");
   while (curr) {
      printf ("%d: Name = \"%s\" Age = %d\n", ++i, curr->byBuf, curr->iSze);
      curr = curr->pNext;
   }
   printf ("\n");
}

