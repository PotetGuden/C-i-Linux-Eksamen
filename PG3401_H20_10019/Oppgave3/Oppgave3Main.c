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
	char *name = (char*) malloc(sizeof(char*));
	memset(name,0,sizeof(char*));
	
	char *municipality = (char*) malloc(sizeof(char*));
	memset(municipality,0,sizeof(char*));
	
	int number = 0;
	
	// BLI FERDIG MED municipality
	
	while(input != '6'){
		if(input != '\n'){		// for å slippe unna loop nr.2 pga enter knappen og getchar()
				printf("Du får nå 6 alternativer:\n");
			   	printf("1. Legge til et element i en liste\n");
			   	printf("2. Hente ut element N fra listen (du velger N)\n");
			   	printf("3. Hente ut element som matcher navn og får tilbake element nr den har\n");
			   	printf("4. Sletter alle elementer med ditt gitte navn\n");
			   	printf("5. Sletter alle elementer som har alder mindre enn det du oppgir\n");
			   	printf("6. For å avslutte.\n\n");
			   	
			   	printf("OBS: Husk at du må legge til minst ett element først\n");
			   	printf("Skriv inn tallet til det alternativet du vil gjøre noe med: ");	   	
		}
		
		input = getchar();
		
		switch(input){
			case '1':
				printf("Du har valgt 1: Legg til et element\n\n");
				printf("Skriv inn et navn, alder og kommune (med mellomrom imellom): ");
				memset(name,0,sizeof(char*));
				memset(municipality,0,sizeof(char*));
				scanf("%s %d %s", name, &number, municipality); 
				if(AddToList(&ppHead, name, number, municipality) == ERROR) break;				// Legger til bruker input i linked list
				printf("\nDu har lagt til '%s' inn i databasen\n\n", name);
				PrintList(ppHead);													// Printer ut hele current linked list
				if(ContinueOrNot() == ERROR) input = '6';							// Spør bruker om de vil fortsette, alt utenom "ja" vil resultere i at input = x, som avslutter loop
				break;
			case '2':
				printf("Du har valgt 2: Hent ut et element ved å oppgi en index\n");
				printf("Skriv inn et tall: ");
				scanf("%d", &number);
				GetElement(&ppHead, number);										// Henter en "index" fra linked list
				printf("\n");
				if(ContinueOrNot() == ERROR) input = '6';
				break;
			case '3':
				printf("Du har valgt 3: Finn index ved å oppgi navn: ");
				memset(name,0,sizeof(char*));
				scanf("%s", name);
				GetElementByName(&ppHead, name);									// Henter navn og index utifra navnet bruker oppgir
				printf("\n");
				if(ContinueOrNot() == ERROR) input = '6';
				break;
			case '4':
				printf("Du har valgt 4: Slett et element ved å oppgi navn: ");
				memset(name,0,sizeof(char*));
				scanf("%s", name);
				DeleteNameNode(&ppHead, name);										// Sletter navn bruker oppgir fra linked listen
				printf("\n");
				PrintList(ppHead);
				if(ContinueOrNot() == ERROR) input = '6';
				break;
			case '5':
				printf("Du har valgt 5: Slett alle elementer hvor alder er mindre enn ditt tall: ");
				scanf("%d", &number);
				RemoveAllLessThanN(&ppHead, number);
				printf("\n");
				PrintList(ppHead);
				if(ContinueOrNot() == ERROR) input = '6';
				break; 
			case '6':
				printf("Du har valgt å avslutte applikasjonen..\n");
				break;
			case '\n':	// For å slippe unna med scanf og enter-knappen
				break;
			default: 
				printf("Du har skrevet inn noe ugyldig\n");
				input = '6'; 
				break;
		}
	}
	
	
	// For å frigjøre alle elementer som fortsatt er i linked listen
	LIST *curr = ppHead->pHead;
	int p = 1;
	while (curr != NULL) {
  		if(curr->pPrev != NULL){
  			free(curr->pPrev); 
  		} 
  		if(curr->pNext == NULL){
  			free(curr);
  			break;
  		}
  		p++;
  		curr = curr->pNext;
	}
	free(name);
	free(municipality);
	free(ppHead);
	
	return 0;
}

// Liten bug om man skriver feil sva
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
   printf("Den foreløpig linked listen er som følger:\n");
   while (curr) {
      printf ("%d: Navn = \"%s\" Alder = %d  Kommune = \"%s\"\n", ++i, curr->name, curr->age, curr->municipality);
      curr = curr->pNext;
   }
   printf ("\n");
}

