#include "utils.h"

void insert(char *file, Bitmap *image, int *coords) {
     int y = coords[0];
     int x = coords[1];

     Bitmap *insertfile = edit(file);

     if (insertfile == NULL) {
        printf("Void insert\n");
     }

     int height = image->infohead.height;
     int width = image->infohead.width;

     int h = insertfile->infohead.height;
     int w = insertfile->infohead.width;
    for (int i = x, index = 0; i < height && index < h; i++, index++) {
        for (int j = y, contor = 0; j < width && contor < w; j++, contor++) {
            image->imagematrix[i][j] = insertfile->imagematrix[index][contor];
        }
    }
    quit(insertfile);
}
