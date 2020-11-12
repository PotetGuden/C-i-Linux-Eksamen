#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Oppgave3.h"

LIST *CreateNode (void *name, int age){		
   	LIST *pThis = malloc (sizeof(LIST));		// + age?
   	if (pThis != NULL) {
      	memset (pThis, 0, sizeof(LIST));		// + age?
      	pThis->age = age;
      	memcpy (pThis->name, name, sizeof(name));
   	}
   	return pThis;
}

int AddToList (LISTHEAD **ppHead, void *name, int age){
   	int iRc = ERROR;
   	
   	if(strlen(name) > MAX_SIZE_BUFF){
		printf("Navnet du har skrevet inn er for stort, prøv igjen..\n");
		
		return iRc;
	}
	
   	LIST *pThis = CreateNode (name, age);
   	if (pThis != NULL) {
      	if ((*ppHead)->pTail == NULL && (*ppHead)->pHead == NULL) { // Ingen i listen fra før av, dette blir da eneste element i listen
         	(*ppHead)->pHead = pThis;			
         	(*ppHead)->pTail = pThis;
         	pThis->pNext = NULL;
		
         	iRc = OK;
      	}
      	else {
      	 	(*ppHead)->pTail->pNext = pThis;	// Setter current tail -> next til denne noden
         	pThis->pPrev = (*ppHead)->pTail;	// Setter pPrev til å være forrige tail
         	(*ppHead)->pTail = pThis;			// Ny tail = denne noden
         	pThis->pNext = NULL;				 
         
         	iRc = OK;
      	}
   	}
   	//free(pThis);		// Mulig jeg ikke burde free() her?
   	return iRc;
}

int GetElement(LISTHEAD **ppHead, int n){
	int iRc = ERROR;
	int i = 1;
	
	if(!n){
		printf("Du har gitt en ugyldig informasjon..\n");
		return iRc;
	}
	
	LIST *curr = (*ppHead)->pHead;
   	
   	
   	while (curr) {
   		if(i == n){
   			printf("\nFant riktig nummer: %d, Navnet for denne indexen er: %s\n", n, curr->name);
   			iRc = OK;			
   			return iRc;			// Avslutt loop
   		} 
      	curr = curr->pNext;
      	i++;
   	}
   	
   	// Hvis man har kommet forbi while-loopen så har har man ikke funnet N 				
   	printf("Du skrev inn et ugyldig tall, vær sikkert på at det er nok elementer..\n");

   	return iRc;
}

int GetElementByName(LISTHEAD **ppHead, char *name){
	int iRc = ERROR;
	int i = 1;
   	LIST *curr = (*ppHead)->pHead;
   	while (curr) {
   		if(strcmp(curr->name, name) == 0){
   			printf("Fant riktig navn: \"%s\", index: %d\n", curr->name, i);
   			iRc = OK;			
   			return iRc;   		// Avslutt loop
   		} 
      	curr = curr->pNext;
      	i++;
   	}
   	
   	printf("Fant ikke navnet \"%s\" i databasen..\n", name);
   	return iRc;
}

int DeleteNameNode(LISTHEAD **ppHead, char *name){
	int iRc = ERROR;
	int i = 1;
	
   	LIST *curr = (*ppHead)->pHead;
   	
   	while (curr) {
   		if(strcmp(curr->name, name) == 0){
   			printf("Fjernet navnet \"%s\" fra databasen\n", name);
   			iRc = RemoveFromList(&*ppHead, curr);
   						
   			
   			//return iRc;   	
   		} 
      	curr = curr->pNext;
      	i++;
   	}
	if(iRc == OK){
		free(curr);
	} else{
   		printf("\nFant ikke navnet \"%s\" i databasen..\n", name);
   	}
   	return iRc;
}
// Liten feil som ikke fjernet siste navn i linked list, om alder var mindre enn det som var oppgitt
int RemoveAllLessThanN (LISTHEAD **ppHead, int n){
	int iRc = ERROR;
	int i = 1;
	
   	LIST *curr = (*ppHead)->pHead;
  
   	while (curr) {
   		if(curr->age < n){
   			printf("\nFjernet navnet \"%s\" som er: %d år gammel.\n", curr->name, curr->age);
   			iRc = RemoveFromList(&*ppHead, curr);
   			
   		} 
      	curr = curr->pNext;
      	i++;
   	}
   	if(iRc == OK) free(curr);  
   	return iRc;
}

int RemoveFromList (LISTHEAD **ppHead, LIST *pToDelete){
   	int iRc = ERROR;
   	LIST *pThis = (LIST*) malloc (sizeof(LIST));
   	memset(pThis,0,sizeof(LIST));

   	if((*ppHead)->pHead == pToDelete && (*ppHead)->pTail == pToDelete){	// Bare om det er 1 node i listen
   		(*ppHead)->pHead = pToDelete->pNext;
   		(*ppHead)->pTail = pToDelete->pNext;
   		iRc = OK;
   	} else if ((*ppHead)->pHead == pToDelete) {							// Bare om det er første nodem
      	(*ppHead)->pHead = pToDelete->pNext;
      	(*ppHead)->pHead->pPrev = NULL;
      	iRc = OK;
   	} else if((*ppHead)->pTail == pToDelete){							// Bare om det er siste noden
   		(*ppHead)->pTail = pToDelete->pPrev;
   		(*ppHead)->pTail->pNext = NULL;
   		iRc = OK;
   	} else {															// Ellers bla igjennom listen og flytt pekerene
      	pThis = (*ppHead)->pHead;
      	while (pThis != NULL) {
         	if (pThis == pToDelete) {
            	pThis->pPrev->pNext = pThis->pNext;
            	pThis->pNext->pPrev = pThis->pPrev;
            	iRc = OK;
				break;
         	}
         	pThis = pThis->pNext;	
      	}
   	}
   	//free(pThis);
	return iRc;
}
