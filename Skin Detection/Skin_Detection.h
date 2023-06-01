#ifndef SKIN_DETECTION
#define SKIN_DETECTION

#include"../BMP Programs/bmp.h"
#include "../RGB HSV/RGB_HSV.h"

void skin_detection(int(&R)[MaxBMPSizeX][MaxBMPSizeY], int(&G)[MaxBMPSizeX][MaxBMPSizeY], int(&B)[MaxBMPSizeX][MaxBMPSizeY],
    int(&r)[MaxBMPSizeX][MaxBMPSizeY], int(&g)[MaxBMPSizeX][MaxBMPSizeY], int(&b)[MaxBMPSizeX][MaxBMPSizeY], int w, int h);

#endif /* SKIN_DETECTION */
