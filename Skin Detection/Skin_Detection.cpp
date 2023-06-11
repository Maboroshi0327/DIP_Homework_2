#include "Skin_Detection.h"

void Skin_Detection(int(&R)[MaxBMPSizeX][MaxBMPSizeY], int(&G)[MaxBMPSizeX][MaxBMPSizeY], int(&B)[MaxBMPSizeX][MaxBMPSizeY],
    int(&r)[MaxBMPSizeX][MaxBMPSizeY], int(&g)[MaxBMPSizeX][MaxBMPSizeY], int(&b)[MaxBMPSizeX][MaxBMPSizeY], int w, int h)
{
    vector<vector<double>> H(w, vector<double>(h, 0));
    vector<vector<double>> S(w, vector<double>(h, 0));
    vector<vector<double>> V(w, vector<double>(h, 0));
    rgb_to_hsv(R, G, B, H, S, V);

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (6 <= H[i][j] and H[i][j] <= 38 and 0.23 <= S[i][j] and S[i][j] <= 0.68)
            {
                r[i][j] = 255;
                g[i][j] = 255;
                b[i][j] = 255;
            }
            else
            {
                r[i][j] = 0;
                g[i][j] = 0;
                b[i][j] = 0;
            }
        }
    }
}
