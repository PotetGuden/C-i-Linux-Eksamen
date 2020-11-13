#ifndef _OPPGAVE_3_
#define _OPPGAVE_3_

#define OK      0
#define ERROR   1
#define MAX_SIZE_BUFF 256

typedef unsigned char BYTE;		// en "vanlig" char har values fra -128 - 127, men når det skal representeres bokstaver vha. ascii verdier, så bruker vi ikke minus values, så man kan define en unsigned char for at values skal gå fra 0-255 istedenfor, har forsovet ikke noe å si i dette tilfelle, men har det med bare for å vise at det funker.

typedef struct _LIST {
   	struct _LIST *pNext;
   	struct _LIST *pPrev;
   	int age;
   	   	
   	BYTE name[MAX_SIZE_BUFF];
   	BYTE municipality[MAX_SIZE_BUFF];
} LIST;

typedef struct _LISTHEAD {		// Holder styr på head/tail på linked listen _LIST
   	LIST *pHead;
   	LIST *pTail;
} LISTHEAD;

// funksjonene nedenfor returnerer OK eller ERROR.

int AddToList (LISTHEAD **ppHead, void *name, int age, void *municipality);
int RemoveFromList (LISTHEAD **ppHead, LIST *pToDelete);
int GetElement(LISTHEAD **ppHead, int n);
int GetElementByName(LISTHEAD **ppHead, char *name);
int DeleteNameNode(LISTHEAD **ppHead, char *name);
int RemoveAllLessThanN (LISTHEAD **ppHead, int N);

#endif // _OPPGAVE_3_
