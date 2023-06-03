#ifndef FFT
#define FFT

#include "../BMP Programs/bmp.h"

extern double sp_re[MaxBMPSizeX][MaxBMPSizeY]; // real part of the spectrum
extern double sp_im[MaxBMPSizeX][MaxBMPSizeY]; // imaginary part of the spectrum
extern double tmp[MaxBMPSizeX][MaxBMPSizeY];

void Removal_of_Periodic_Noise(int(&R)[MaxBMPSizeX][MaxBMPSizeY], int(&r)[MaxBMPSizeX][MaxBMPSizeY], int w, int h);

static void fft1(double data[], int nn, int isign);
static void fft2(double data[], int nn, int isign);
static void spectrum_shift(int mm); // mm is one half of the original image width

#endif /* FFT */