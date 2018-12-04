/**
 * Usage :
 * ./main seuil [seuil] [image]
 * ./main moyenne [image]
 * ./main mediane [image]
 * ./main otsu [image]
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool hasChar(char* str, char toFind);
void showHelp();
void fonction_seuil(char *filename, int seuil);
int fonction_moyenne(char *filename);
int fonction_mediane(char *filename);
int fonction_otsu(char *filename);

int main(int argc, char *argv[])
{
    // Show help if no arguments
    if(argc <= 1) {
        printf("Nombre d'arguments : %d", argc);
        showHelp();
        return 0;
    }

    // Seuil
    if(strcmp(argv[1], "seuil") == 0) {
        int seuil = (argc == 3) ? 85 : atoi(argv[2]);
        char *filename = (argc == 3) ? argv[2] : argv[3];
        printf("Seuillage du fichier %s avec un seuil de %d\n", filename, seuil);
        fonction_seuil(filename, seuil);
    }

    // Moyenne
    else if (strcmp(argv[1], "moyenne") == 0) {
        char *filename = argv[2];
        int moyenne = fonction_moyenne(filename);
        printf("Seuillage du fichier %s selon la moyenne des valeurs : %d\n", filename, moyenne);
        fonction_seuil(filename, seuil);
    }

    // Mediane
    else if (strcmp(argv[1], "mediane") == 0) {
        char *filename = argv[2];
        printf("Seuillage du fichier %s selon la mediane des valeurs\n", filename);
    }

    // Otsu
    else if (strcmp(argv[1], "otsu") == 0) {
        char *filename = argv[2];
        printf("Seuillage du fichier %s selon la méthode otsu des valeurs\n", filename);
    }

    // Autre
    else {
        printf("La méthode %s n'est pas prise en compte\n", argv[1]);
        showHelp();
        return 0;
    }

    exit(EXIT_SUCCESS);
}

/**
 * Renvoi true ou false si la chaîne contient un charactère
 */
bool hasChar(char* str, char toFind) {
    int len = strlen(str);
    for(int i = 0; i<len; i++) {
        if(str[i] == toFind) return true;
    }
    return false;
}

/**
 * Affiche l'aide
 */
void showHelp() {
    printf("Usage : \n\t- ./main seuil [seuil] [image]\n\t- ./main moyenne [image]\n\t- ./main mediane [image]\n\t- ./main otsu [image]\n");
}

/**
 * Crée un nouveau fichier en utilisant le seuil passé en paramètre
 */
void fonction_seuil(char *filename, int seuil) {
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
    printf("Seuillage terminé\n");
}

/**
 * Calcul la moyenne des valeurs du fichier
 */
int fonction_moyenne(char *filename) {
    FILE *file_read;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    file_read = fopen(filename, "rb");
    int lastCommLine = 0;

    int sumValues = 0;
    int nbValues = 0;

    for(int i = 0; (read = getline(&line, &len, file_read)) != -1; i++) {
        if(line[0] == '#') lastCommLine = i;
        if(((line[0] != 'P') && (line[0] != '#') && (i > lastCommLine+2))) {
            nbValues++;
            sumValues += atoi(line);
        }
    }

    fclose(file_read);
    return (sumValues / nbValues);
}

/**
 * Calcul la mediane des valeurs du fichier
 */
int fonction_mediane(char *filename) {
    FILE *file_read;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    file_read = fopen(filename, "rb");
    int lastCommLine = 0;

    const int pas = 10:
    int valeursPourMediane1 = [pas];
    int valeursPourMediane2 = [pas];
    int compteur1 = 0;
    int compteur2 = 0;
    
    for(int i = 0; (read = getline(&line, &len, file_read)) != -1; i++) {
        if(line[0] == '#') lastCommLine = i;
        if(((line[0] != 'P') && (line[0] != '#') && (i > lastCommLine+2))) {
            compteur1++;

            if(compteur1 != 0 && (compteur1 %10 == 0)) {
                // Calcul de la médianne
                // Réinitialisation du tableau

                compteur1 = 0;
            }
        }
    }

    fclose(file_read);
    return 0;
}

/**
 * Calcul la otsu des valeurs du fichier
 */
int fonction_otsu(char *filename) {
    FILE *file_read;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    file_read = fopen(filename, "rb");
    int lastCommLine = 0;

    for(int i = 0; (read = getline(&line, &len, file_read)) != -1; i++) {
        if(line[0] == '#') lastCommLine = i;
        if(((line[0] != 'P') && (line[0] != '#') && (i > lastCommLine+2))) {
            // Traitement de la ligne
            // TODO
        }
    }

    fclose(file_read);
    return 0;
}

/**
 * Calcul la médiane d'un tableau de nombres
 */
int mediane(int numbers[], unsigned int taille) {
    // Tri dans l'ordre croissant
    for(int i = 0, temp=0; i<taille-1; i++) {
        if(numbers[i] > numbers[i+1]) {
            temp = numbers[i];
            numbers[i] = numbers[i+1];
            numbers[i+1] = temp;
        }
    }

    // Renvoi la médianne
    return number[(int)taille/2];
}