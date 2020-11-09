#ifndef __OPGGAVE_2__
#define __OPPGAVE_2__

#pragma pack(1)
typedef struct NODE {
	char *inputString;
	int totalLetters;
	struct NODE *pArr;
} NODE;	
#pragma pack()

void GetIndex(NODE node);
void Bubblesort();
void Swap();

#endif // __OPPGAVE_2__
