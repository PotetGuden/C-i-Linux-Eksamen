#ifndef _OPPGAVE_3_
#define _OPPGAVE_3_

#define OK      0
#define ERROR   1
#define MAX_SIZE_BUFF 256

typedef unsigned char BYTE;

typedef struct _LIST {
   	struct _LIST *pNext;
   	struct _LIST *pPrev;
   	int iSze;
   	   	
   	BYTE name[MAX_SIZE_BUFF];
   	BYTE kommune[MAX_SIZE_BUFF];
	BYTE byBuf[MAX_SIZE_BUFF];
	//char kommune[];
} LIST;

typedef struct _LISTHEAD {		// Holder styr på hele listen
   	LIST *pHead;
   	LIST *pTail;
} LISTHEAD;

// funksjonene nedenfor returnerer OK eller ERROR.

int AddToList (LISTHEAD **ppHead, void *pvData, int iSze);
int RemoveFromList (LISTHEAD **ppHead, LIST *pToDelete);
int GetElement(LISTHEAD **ppHead, int n);
int GetElementByName(LISTHEAD **ppHead, char *name);
int DeleteNameNode(LISTHEAD **ppHead, char *name);
int RemoveAllLessThanN (LISTHEAD **ppHead, int N);

#endif // _OPPGAVE_3_
