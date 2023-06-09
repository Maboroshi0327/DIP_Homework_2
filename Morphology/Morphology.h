#ifndef MORPHOLOGY
#define MORPHOLOGY

#include <vector>
#include <algorithm>
#include "../BMP Programs/bmp.h"

using std::vector;

void Noise_Removal(int(&R)[MaxBMPSizeX][MaxBMPSizeY], int(&r)[MaxBMPSizeX][MaxBMPSizeY], int w, int h);

static void Erosion(vector<vector<int>>& origin, vector<vector<int>>& result);
static void Dilation(vector<vector<int>>& origin, vector<vector<int>>& result);
static void find_match(vector<vector<int>>& origin, vector<vector<int>>& result, vector<vector<int>>& structure, int x, int y);
static void filling(vector<vector<int>>& origin, vector<vector<int>>& result, vector<vector<int>>& structure, int x, int y);

#endif /* MORPHOLOGY */