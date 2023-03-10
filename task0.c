#include "utils.h"
#define MAXLENGTH 4000000
#define UINT_MAX_HEIGHT 768
#define UINT_MAX_WIDTH 1024

void tipcom(char *comanda, char *file, Bitmap **image, int *coords) {
     if (strstr(comanda, "edit")) {
        *image = edit(file);
        if (image == NULL) {
            printf("Error loading file in buffer\n");
        }
     }
      if (strstr(comanda, "insert")) {
         insert(file, *image, coords);
     }
      if (strstr(comanda, "save")) {
        save(file, *image);
     }
      if (strstr(comanda, "quit")) {
        quit(*image);
     }
     if (strstr(comanda, "set draw_color")) {
         draw_color(coords, *image);
     }
     if (strstr(comanda, "set line_width")) {
         line_width(coords, *image);
     }
     if (strstr(comanda, "draw line")) {
         line(coords, *image);
     }
     if (strstr(comanda, "draw rectangle")) {
         rectangle(coords, *image);
     }
     if (strstr(comanda, "draw triangle")) {
         triangle(coords, *image);
     }
     if (strstr(comanda, "fill")) {
         fill(coords, *image);
     }
}


int main() {
    // alocam dinamic "stringul" de char care contin comanda
    char *comanda = malloc(MAXLENGTH * sizeof(char));
    if (comanda == NULL) {
       printf("Alocare nereusita pentru comanda\n");
    }

    char *actiune = malloc(MAXLENGTH * sizeof(char));
    if (actiune == NULL) {
        printf("Alocare nereusita pentru actiune\n");
        return -1;
    }

    char  *file = malloc(MAXLENGTH * sizeof(char));
    if (file == NULL) {
        printf("Alocare nereusita\n");
        return -1;
    }

    Bitmap *image = NULL;
    // citim din fiserul de input
    while (scanf("%[^\n]%*c", comanda) != EOF) {
        // copiem comanda in alta variabila ca sa o folosim cu strtok
        snprintf(actiune, strlen(comanda) + 1, "%s", comanda);
        // vector de coordonate
        int *coords = malloc(MAXLENGTH * sizeof(int));
        if (coords == NULL) {
          printf("Error allocating coords\n");
        }
        // aflam coordonatele si fisierul de imagine
        int increment = 0;
        char *word = strtok(actiune, " ");
         while (word != NULL) {
            if (strstr(word, "bmp")) {
                snprintf(file, strlen(word) + 1, "%s", word);
          }
          if (!(word[0] >= 'a' && word[0] <= 'z') && !(word[0] >= 'A' && word[0] <= 'Z') && !(word[0] == '\0')) {
           int num = atoi(word);
             coords[increment] = num;
             increment++;
         }
              word = strtok(NULL, " ");
          }
          // aflam tipul de actiune cu functia tipcom
          tipcom(comanda, file, &image, coords);
          free(coords);
    }

    free(comanda);
    free(actiune);
    free(file);
    return 0;
}

