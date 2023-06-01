#include "RGB_HSV.h"

void rgb_to_hsv(int(&R)[MaxBMPSizeX][MaxBMPSizeY], int(&G)[MaxBMPSizeX][MaxBMPSizeY], int(&B)[MaxBMPSizeX][MaxBMPSizeY],
    vector<vector<double>>& H, vector<vector<double>>& S, vector<vector<double>>& V)
{
    int w = (int)H.size();
    int h = (int)H[0].size();

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            find_HSV(R[i][j], G[i][j], B[i][j], H[i][j], S[i][j], V[i][j]);
        }
    }
}

static void find_HSV(int R, int G, int B, double& H, double& S, double& V)
{
    double R_temp = (double)R / 255;
    double G_temp = (double)G / 255;
    double B_temp = (double)B / 255;
    vector<double> Array = { R_temp ,G_temp ,B_temp };
    sort(Array.begin(), Array.end());
    double& Cmax = Array.back();
    double& Cmin = Array.front();
    double delta = Cmax - Cmin;

    if (delta == 0)
        H = 0;
    else if (Cmax == R_temp)
        H = 60 * (G_temp - B_temp) / delta;
    else if (Cmax == G_temp)
        H = 60 * (2 + (B_temp - R_temp) / delta);
    else if (Cmax == B_temp)
        H = 60 * (4 + (R_temp - G_temp) / delta);

    if (Cmax == 0)
        S = 0;
    else
        S = delta / Cmax;

    V = Cmax;
}
