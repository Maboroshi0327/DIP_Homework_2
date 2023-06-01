#ifndef RGB_HSV
#define RGB_HSV

#include <vector>
#include <algorithm>
#include "../BMP Programs/bmp.h"

using namespace std;

void rgb_to_hsv(int(&R)[MaxBMPSizeX][MaxBMPSizeY], int(&G)[MaxBMPSizeX][MaxBMPSizeY], int(&B)[MaxBMPSizeX][MaxBMPSizeY],
    vector<vector<double>>& H, vector<vector<double>>& S, vector<vector<double>>& V);

static void find_HSV(int R, int G, int B, double& H, double& S, double& V);

#endif /* RGB_HSV */
