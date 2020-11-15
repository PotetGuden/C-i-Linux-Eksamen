#ifndef __OPPGAVE_6__
#define __OPPGAVE_6__

#pragma (1)			// Fjerne padding 
typedef struct MyStruct {
	char buff[11];	// [11] brukes som 0-terminering
	int totalLetters;
	char *fileName;
	int endOfFile;
} MyStruct;
#pragma()

#define SEM_PRODUCER_NAME "semproducer"
#define SEM_RECEIVER_NAME "semreceiver"
#define MODE 0644	// 0 = prefix for octal, 6 = read/write permission(user), 4 = read perm.(group), 4 = read perm.(others)  (Kunne gitt andre verdier, så lenge user har r/w permisison) 
#define TRUE 1
#define FALSE 0

void *WorkThread (void *ms);

#endif // __OPPGAVE_6__
