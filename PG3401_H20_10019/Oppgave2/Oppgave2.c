#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Oppgave2.h"

int main(int argc, char *argv[]){
										
	if(argc < 2){
		printf("Du må legge ved din tekst etter %s\nAvslutter program..\n", argv[0]);
		exit(1);
	}
	
	int iStrings = argc-1;  
	int counter;
	
	NODE *array = malloc(sizeof(NODE)* iStrings);   
	memset(array,0,sizeof(array));
	
	for(counter = 0; counter < iStrings; counter++){
		NODE *node = malloc(sizeof(NODE));
		memset(node,0,sizeof(NODE));
		
		node->inputString = argv[counter+1];
		node->totalLetters = strlen(node->inputString);
		node->pArr = &array[0];
		
		array[counter] = *node;
		
		//GetIndex(*node);					// Hvis du som sensor vil teste denne funksjonen
		free(node);
	}

	Bubblesort(array, iStrings);
	
	//GetIndex(array[1]);  					// Denne måten å kalle funksjonen, krever at man faktisk har nok elementer i listen
	
	free(array);
}

void Bubblesort(struct NODE arr[], int iStrings){
	int i, j, k = 0;
	
	printf("\nUsortert:\n");
	
	for(k = 0; k < iStrings; k++){		
		printf("\"%s\" denne strengen har %d bokstaver\n", arr[k].inputString, arr[k].totalLetters);  // 'æ' 'ø' 'å' vil telles som 2 bokstaver 
	}													   

	for(i = 0; i < iStrings; i++){
		for(j = 0; j < iStrings-1; j++){
			if(strcmp((arr[i].inputString), (arr[j].inputString)) < 0){
				Swap(&arr[i], &arr[j]);
			}
		}
	}
	
	printf("\nSortert:\n");
	for(k = 0; k < iStrings; k++){
		printf("\"%s\" denne strengen har %d bokstaver\n", arr[k].inputString, arr[k].totalLetters);
	}
	
	printf("\n");
}

void Swap(NODE *arr, NODE *arr2){
	NODE temp = *arr;
	*arr = *arr2;
	*arr2 = temp;
}

void GetIndex(NODE node){

	int counter = 0;
	
	NODE *curr = node.pArr;
	while(curr){
		if(strcmp(node.inputString, curr->inputString) == 0){
			printf("Node \"%s\" found at index: %d\n",curr->inputString, counter);
			break;
		}
		curr++;
		counter++;
	}
}






