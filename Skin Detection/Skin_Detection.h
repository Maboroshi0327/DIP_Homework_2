#ifndef SKIN_DETECTION
#define SKIN_DETECTION

#include <vector>
#include"../BMP Programs/bmp.h"
#include "../RGB HSV/RGB_HSV.h"

using std::vector;

void Skin_Detection(int(&R)[MaxBMPSizeX][MaxBMPSizeY], int(&G)[MaxBMPSizeX][MaxBMPSizeY], int(&B)[MaxBMPSizeX][MaxBMPSizeY],
    int(&r)[MaxBMPSizeX][MaxBMPSizeY], int(&g)[MaxBMPSizeX][MaxBMPSizeY], int(&b)[MaxBMPSizeX][MaxBMPSizeY], int w, int h);

#endif /* SKIN_DETECTION */
