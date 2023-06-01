#include <iostream>
#include <vector>
#include <cstdlib>
#include "BMP Programs/bmp.h"
#include "Skin Detection/Skin_Detection.h"
#include "FFT Programs/FFT.h"

using namespace std;

int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int r[MaxBMPSizeX][MaxBMPSizeY];
int g[MaxBMPSizeX][MaxBMPSizeY];
int b[MaxBMPSizeX][MaxBMPSizeY];

int main()
{
    int width, height;

#pragma region Problem 1
    open_bmp((char*)"test images/skin_det_1.bmp", R, G, B, width, height);

    skin_detection(R, G, B, r, g, b, width, height);

    save_bmp((char*)"test images\\Problem_1.bmp", r, g, b);
    cout << "Problem 1 Job Finished!" << endl;
    close_bmp();
#pragma endregion Problem 1

#pragma region Problem 2
    open_bmp((char*)"test images/periodic_noise3.bmp", R, G, B, width, height);



    save_bmp((char*)"test images\\Problem_2.bmp", r, g, b);
    cout << "Problem 2 Job Finished!" << endl;
    close_bmp();
#pragma endregion Problem 2

    system("PAUSE");
    return 0;
}
