#include "utils.h"

void quit(Bitmap *image) {
    for (int i = 0; i < image->infohead.height; i++) {
    free(image->imagematrix[i]);
  }
    free(image->imagematrix);
    free(image);
}

void save(char *file, Bitmap *image) {
    if (image == NULL) {
    printf("ERROR COPYING THE THING\n");
    }
    // deschidem fiserul output
    FILE *outputfile = fopen(file, "wb");

    if (outputfile == NULL) {
        printf("Error opening outputfile\n");
    }
    char *addpadding = calloc(4, sizeof(char));
    if (addpadding == NULL) {
        printf("Error padding\n");
    }
    // scriem headerul
    fwrite(&image->filehead, sizeof(bmp_fileheader), 1, outputfile);
    fwrite(&image->infohead, sizeof(bmp_infoheader), 1, outputfile);
    if (image->imagematrix == NULL) {
    printf("ERROR\n");
    }
    // aflam cat ocupa padding-ul pentru a-l adauga
    int offset = (image->infohead.width * 3) % 4;
    if (offset != 0) {
     offset = 4 - offset;
    }
    // scriem matricea
    for (int  i = 0; i < image->infohead.height; i++) {
        for (int j = 0; j < image->infohead.width; j++) {
           fwrite(&(image->imagematrix[i][j]), sizeof(Pixels), 1, outputfile);
        }
          fwrite(addpadding, offset, 1, outputfile);
    }
    fclose(outputfile);
    free(addpadding);
}

Bitmap *edit(char *file) {
  // deschidem fisierul in mod citire
  FILE *inputfile = fopen(file, "rb");
    if (inputfile == NULL) {
        printf("Error opening file\n");
        return 0;
    }
    // initializam datele imaginii
  Bitmap *imageinfo = (Bitmap *)malloc(sizeof(Bitmap));
  if (imageinfo == NULL) {
     fprintf(stderr, "invalid image\n");
  }
  // citim headerul
  fread(&imageinfo->filehead, sizeof(bmp_fileheader), 1, inputfile);
  fread(&imageinfo->infohead, sizeof(bmp_infoheader), 1, inputfile);
  // ignoram octetii alocati headerului header
  fseek(inputfile, imageinfo->filehead.imageDataOffset, SEEK_SET);
  imageinfo->imagematrix = calloc(imageinfo->infohead.height, sizeof(Pixels *));

    for (int i = 0; i < imageinfo->infohead.height; i++) {
       imageinfo->imagematrix[i] = calloc(imageinfo->infohead.width, sizeof(Pixels));
    }

    if (imageinfo->imagematrix == NULL) {
       printf("ERROR\n");
    }
    // aflam padding-ul
    int ignorepadding = (imageinfo->infohead.width * 3) % 4;
    if (ignorepadding != 0) {
       ignorepadding = 4 - ignorepadding;
    }
    // citim matricea de pixeli
    for (int i = 0; i < imageinfo->infohead.height; i++) {
      for (int j = 0; j < imageinfo->infohead.width; j++) {
      fread(&imageinfo->imagematrix[i][j], sizeof(Pixels), 1, inputfile);
    }
    fseek(inputfile, ignorepadding, SEEK_CUR);
    }
  fclose(inputfile);
    return imageinfo;
}
