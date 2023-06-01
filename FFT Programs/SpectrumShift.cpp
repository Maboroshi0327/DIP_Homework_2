#include "FFT.h"

float sp_re[MaxBMPSizeX][MaxBMPSizeY]; // real part of the spectrum
float sp_im[MaxBMPSizeX][MaxBMPSizeY]; // imaginary part of the spectrum
float tmp[MaxBMPSizeX][MaxBMPSizeY];

void spectrum_shift(int mm) {
	for (int i = 0; i < mm; i++) {
		for (int j = 0; j < mm; j++) {
			//------------------------ the real part
			tmp[i][j] = sp_re[i][j]; // upper-left <-> lower-right
			sp_re[i][j] = sp_re[mm + i][mm + j];
			sp_re[mm + i][mm + j] = tmp[i][j];
			tmp[i][j] = sp_re[i][mm + j]; // upper-right <-> lower-left
			sp_re[i][mm + j] = sp_re[mm + i][j];
			sp_re[mm + i][j] = tmp[i][j];
			//--------------------------- the imag. part
			tmp[i][j] = sp_im[i][j]; // upper-left <-> lower-right
			sp_im[i][j] = sp_im[mm + i][mm + j];
			sp_im[mm + i][mm + j] = tmp[i][j];
			tmp[i][j] = sp_im[i][mm + j]; // upper-right <-> lower-left
			sp_im[i][mm + j] = sp_im[mm + i][j];
			sp_im[mm + i][j] = tmp[i][j];
		}
	}
}