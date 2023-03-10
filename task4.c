#include "utils.h"

void fillonepixel(int x, int y, unsigned char RedNow, unsigned char GreenNow, unsigned char BlueNow, Bitmap *image) {
     if (y >= image->infohead.width) {
        return;
     }
     if (x >= image->infohead.height) {
       return;
     }
     if (x < 0) {
        return;
     }
     if (y < 0) {
        return;
     }
if (image->imagematrix[x][y].Red == RedNow && image->imagematrix[x][y].Green == GreenNow) {
    if (image->imagematrix[x][y].Blue == BlueNow) {
         image->imagematrix[x][y] = image->pencil.Colorspixel;
         fillonepixel(x, y + 1, RedNow, GreenNow, BlueNow, image);
         fillonepixel(x, y - 1, RedNow, GreenNow, BlueNow, image);
         fillonepixel(x + 1, y, RedNow, GreenNow, BlueNow, image);
         fillonepixel(x - 1, y, RedNow, GreenNow, BlueNow, image);
    }
}
}

void fill(int *coords, Bitmap *image) {
    int y = coords[0];
    int x = coords[1];
    unsigned char RedNow = image->imagematrix[x][y].Red;
    unsigned char GreenNow = image->imagematrix[x][y].Green;
    unsigned char BlueNow = image->imagematrix[x][y].Blue;
    fillonepixel(x, y, RedNow, GreenNow, BlueNow, image);
}
