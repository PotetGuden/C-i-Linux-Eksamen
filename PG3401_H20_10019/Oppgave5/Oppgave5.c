#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "Oppgave5.h"

int main(int argc, char *argv[]){

	FILE *inputFile;
	FILE *outputFile;
	
	if((inputFile = fopen("base64.txt", "r")) == NULL){
		printf("Fant ikke filen du oppga..\nAvslutter program..\n");
		exit(1);
	}
	outputFile = fopen("outputBase64.txt", "w");		// Oppretter ny fil om det ikke finnes noe med det navnet
	
	
	char data[1000];
	char *output;
	//size_t outLength;
	
	fscanf(inputFile, "%s", data);
	printf("Data fra filen:\n%s\n", data);
	fclose(inputFile);
	
	//printf("Data: %s\n", data);

	size_t outLength = strlen(data)/4*3;				// size av data / 4*3 pga det er scalingen fra b64 til encoding format
	//outLength = decodeSize;    							// +1 er for 0-terninering
	output = malloc(outLength);

	if (!b64Decoder(data, (unsigned char *)output, outLength)) {  
		printf("Decode Failure\n");
		return 1;
	}
	
	output[outLength] = '\0';							// Legger til en 0-terminering på slutten av output

	printf("\nDekodet:\n\"%s\"\n", output);
	
	free(output);	
}

// Decoding table  går utifra ascii bokstav verdiene når der er shiftet? -1 er placeholder for bokstaver som ikke er med i b64 table
int decodingTable[] = { 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58,
	59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5,
	6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28,
	29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
	43, 44, 45, 46, 47, 48, 49, 50, 51 };

int b64Decoder(char *data, char *output, size_t outLength){
	size_t dataLength;
	size_t i;
	size_t j;
	int    v;

	if (data == NULL || output == NULL){
		return 0;
	}

	dataLength = strlen(data);
	if (dataLength % 4 != 0)
		return 0;

	for (i = 0, j = 0; i < dataLength; i += 4, j += 3) {
		v = decodingTable[data[i]-43];
		v = (v << 6) | decodingTable[data[i+1]-43];
		v = data[i+2]=='=' ? v << 6 : (v << 6) | decodingTable[data[i+2]-43];
		v = data[i+3]=='=' ? v << 6 : (v << 6) | decodingTable[data[i+3]-43];

		output[j] = (v >> 16) & 0xFF;
		if (data[i+2] != '=')
			output[j+1] = (v >> 8) & 0xFF;
		if (data[i+3] != '=')
			output[j+2] = v & 0xFF;
	}
	return 1;
}

/*

//printf("%i %li\n", decodeSize, b64DecodedSize(data)+1);


size_t b64DecodedSize(char *data){
	size_t len;
	size_t ret;
	size_t i;

	if (data == NULL)
		return 0;

	len = strlen(data);
	ret = len / 4 * 3;

	for (i=len; i-->0; ) {
		if (data[i] == '=') {
			ret--;
		} else {
			break;
		}
	}
	return ret;
}
*/




// QXJiZWlkZXQgbWVkIGRldHRlIGVtbmV0IHNrYWwgZ2kgc3R1ZGVudGVuIGlubmZyaW5nIGkgcHJvZ3JhbW1lcmluZ3NzcHJrZXQgQyBvZyBodm9yZGFuIGRldHRlIGthbiBicnVrZXMgdGlsICBpbnRlcmFnZXJlIGRpcmVrdGUgbWVkIG9wZXJhdGl2c3lzdGVtZXQuIERldCBza2FsIG9ncyBnaSBmb3JzdGVsc2UgYXYgb3BlcmF0aXZzeXN0ZW1ldCBMaW51eCBvZyBrdW5uc2thcCBvbSBodm9yZGFuIGRldHRlIHZpcmtlci4=