#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool hasChar(char* str, char toFind);
void showHelp();

int main(int argc, char *argv[])
{
	// Récupération du premier argument
	int seuil;
	switch(argc) {
		// 1 : filename
		// 2 : seuil
		case 3:
			seuil = atoi(argv[2]);
		break;

		// 1 : filename
		case 2:
			seuil = 85;
		break;

		default:
			showHelp();
			return 255;
	}
	char *filename = argv[1];
	printf("Seuil utilisé : %d\n", seuil);	

	FILE *file_read;
	FILE *file_write;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	file_read = fopen(filename, "rb");
	file_write = fopen("result.pgm", "wb");
	if (file_read == NULL)
		exit(EXIT_FAILURE);

	bool makeConversion;
	int lastCommLine = 0;
	char maxValue[5] = "\0\0\0\0\0";
	for(int i = 0; (read = getline(&line, &len, file_read)) != -1; i++) {
		if(line[0] == '#') lastCommLine = i;
		makeConversion = (bool)((line[0] != 'P') && (line[0] != '#') && (i > lastCommLine+2));
		if(i == lastCommLine+2) {
			strcpy(maxValue, line);
			printf("Valeur max : %s\n", maxValue);
			// strcat(maxValue, "\n");
		}

		// Effectue la comparaison
		// Si >= alors blanc
		// Sinon noir
		fputs(makeConversion ? ((atoi(line) >= seuil) ? maxValue : "0\n") : line, file_write);
	}

	fclose(file_read);
	fclose(file_write);
	if (line)
		free(line);
	exit(EXIT_SUCCESS);
}

bool hasChar(char* str, char toFind) {
	int len = strlen(str);
	for(int i = 0; i<len; i++) {
		if(str[i] == toFind) return true;
	}
	return false;
}

void showHelp() {
	printf("Usage : ./main SOURCE [SEUIL]\n");
}