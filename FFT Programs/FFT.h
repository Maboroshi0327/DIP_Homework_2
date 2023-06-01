#ifndef FFT
#define FFT

#include "../BMP Programs/bmp.h"

extern float sp_re[MaxBMPSizeX][MaxBMPSizeY]; // real part of the spectrum
extern float sp_im[MaxBMPSizeX][MaxBMPSizeY]; // imaginary part of the spectrum
extern float tmp[MaxBMPSizeX][MaxBMPSizeY];

void fft1(float data[], int nn, int isign);
void fft2(float data[], int nn, int isign);
void spectrum_shift(int mm); // mm is one half of the original image width

#endif /* FFT */