#include "utils.h"
#define MAX 4
#define cinci 5
void draw_color(int *coords, Bitmap *image) {
    int R = coords[0];
    int G = coords[1];
    int B = coords[2];

     image->pencil.Colorspixel.Red = R;
     image->pencil.Colorspixel.Green = G;
     image->pencil.Colorspixel.Blue = B;
}

void line_width(int *coords, Bitmap *image) {
    image->pencil.width = coords[0];
}

void punct(Bitmap *image, int x, int y) {
      int xmijloc = image->pencil.width / 2;
      int ymijloc = image->pencil.width / 2;

     int diffx = x - xmijloc;
     int diffy = y - ymijloc;

     int plusx = x + xmijloc;
     int plusy = y + ymijloc;

     for (int i = diffx; i <= plusx; i++) {
         if (i < 0 || i >= image->infohead.height) {
            continue;
         }
         for (int j = diffy; j <= plusy; j++) {
            if (j < 0 || j >= image->infohead.width) {
               continue;
            }
             image->imagematrix[i][j] = image->pencil.Colorspixel;
         }
     }
}

void line(int *coords, Bitmap *image) {
     int y1 = coords[0];
     int x1 = coords[1];
     int y2 = coords[2];
     int x2 = coords[3];

     if (y2 > image->infohead.width) {
        y2 = image->infohead.width - 1;
     }
     if (x2 > image->infohead.height) {
        x2 = image->infohead.height - 1;
     }
     if (x2 < 0) {
        x2 = 0;
     }
     if (y2 < 0) {
        y2 = 0;
     }
     if (y1 > image->infohead.width) {
         return;
     }
     if (x1 > image->infohead.height) {
        return;
     }
     if (x1 < 0) {
        x1 = 0;
     }
     if (y1 < 0) {
        y1 = 0;
     }
     // pentru linia verticala
     if (y1 == y2) {
        if (x1 < x2) {
           for (int i = x1; i <= x2; i++) {
             punct(image, i, y1);
           }
        } else if (x1 > x2) {
          for (int i = x1; i >= x2; i--) {
             punct(image, i, y1);
           }
        }
     }
     // pentru linia orizontala
     if (x1 == x2) {
        if (y1 < y2) {
           for (int j = y1; j <= y2; j++) {
              punct(image, x1, j);
           }
       } else if (y1 > y2) {
         for (int j = y1; j >= y2; j--) {
             punct(image, x1, j);
           }
        }
     }
     // linie oblica
      int xdif = 0, ydif = 0;
     if (x1 < x2) {
         xdif = x2 - x1;
     } else if (x2 < x1) {
         xdif = x1 - x2;
     }
     if (y1 < y2) {
         ydif = y2 - y1;
     } else if (y2 < y1) {
         ydif = y1 - y2;
     }
// in cazul in care dif de x este mai mica decat dif y
     if (xdif < ydif) {
        if (y1 < y2) {
        for (int j = y1; j <= y2; j++) {
              int x = ((j - y1) * (x2 - x1) + x1 * (y2 - y1)) / (y2 - y1);
             punct(image, x, j);
    }
     } else if (y1 > y2) {
        for (int j = y1; j >= y2; j--) {
             int x = ((j - y2) * (x1 - x2) + x2 * (y1 - y2)) / (y1 - y2);
             punct(image, x, j);
        }
    }
// in cazul in care dif de x mai mare decat dif y
     } else if (xdif > ydif) {
        if (x1 < x2) {
        for (int i = x1; i <= x2; i++) {
             int  y = ((i - x1) * (y2 - y1) + y1 * (x2 - x1)) / (x2 - x1);
            punct(image, i, y);
     }
     }   else if (x2 < x1) {
    for (int i = x1; i >= x2; i--) {
     int  y = ((i - x2) * (y1 - y2) + y2 * (x1 - x2)) / (x1 - x2);
            punct(image, i, y);
     }
  }
// in cazul in care diferentele sunt egale
  } else if (xdif == ydif) {
    if ((x2 - x1 < 0) && (y2 - y1)) {
    for (int i = x1; i <= x2; i++) {
        int y = 0 - i + y1 - x1;
         punct(image, i, y);
    }
    }
    if ((x2 - x1 > 0) && (y2 > y1 )) {
        for (int i = x1; i <= x2; i++) {
            int y = i + y1 - x1;
            punct(image, i, y);
        }
        }
    if (((x2 - x1 > 0) && (y2 < y1)) || ((x1 - x2 < 0) && (y2 < y1))) {
            for (int i = x1; i <= x2; i++) {
                int y = 0 - i + x1 + y1;
                punct(image, i, y);
            }
        }
    }
}

void rectangle(int *coords, Bitmap *image) {
    int *coordonatedrept = malloc( MAX * sizeof(int));
    if (coordonatedrept == NULL) {
        printf("Error\n");
    }
    // linie orizontala jos
    coordonatedrept[0] = coords[0];  // y
    coordonatedrept[1] = coords[1];  // x
    coordonatedrept[2] = coords[2] + coords[0];  // width
    coordonatedrept[3] = coords[1];  // height
    line(coordonatedrept, image);
    // linie verticala stanga
    coordonatedrept[2] = coords[0];
    coordonatedrept[3] = coords[1] + coords[3];
    line(coordonatedrept, image);
    // linie verticala dreapta
    coordonatedrept[0] = coords[2] + coords[0];
    coordonatedrept[2] = coords[2] + coords[0];
    coordonatedrept[3] = coords[1] + coords[3];
    line(coordonatedrept, image);
    // linie orizontala sus
    coordonatedrept[0] = coords[0];
    coordonatedrept[1] = coords[1] + coords[3];
    coordonatedrept[2] = coords[0] + coords[2];
    coordonatedrept[3] = coords[1] + coords[3];
    line(coordonatedrept, image);
    free(coordonatedrept);
}

void triangle(int *coords, Bitmap *image) {
    int *coordonatetriunghi = malloc( MAX * sizeof(int));
    if (coordonatetriunghi == NULL) {
        printf("Error\n");
    }
    coordonatetriunghi[0] = coords[0];
    coordonatetriunghi[1] = coords[1];
    coordonatetriunghi[2] = coords[2];
    coordonatetriunghi[3] = coords[3];
    line(coordonatetriunghi, image);
    coordonatetriunghi[2] = coords[4];
    coordonatetriunghi[3] = coords[cinci];
    line(coordonatetriunghi, image);
    coordonatetriunghi[0] = coords[2];
    coordonatetriunghi[1] = coords[3];
    line(coordonatetriunghi, image);
    free(coordonatetriunghi);
}
