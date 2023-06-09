#include "FFT.h"

void Removal_of_Periodic_Noise(int(&R)[MaxBMPSizeX][MaxBMPSizeY], int(&r)[MaxBMPSizeX][MaxBMPSizeY], int w, int h)
{
    double* data = new double[MaxBMPSizeX * MaxBMPSizeY * 2];

    // convert to the long 1D array
    int ptr = 0;
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            data[ptr] = R[i][j];    // real part of the input data
            data[ptr + 1] = 0;      // imaginary part of the input data
            ptr += 2;
        }
    }

    fft2(data, w, 1);   // perform the forward fft2

    // fetch the 2D spectrum from the long 1-D spectrum array
    ptr = 0;
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            sp_re[i][j] = data[ptr];        // real part of the 2D spectrum
            sp_im[i][j] = data[ptr + 1];    // imaginary part of the 2D spectrum
            ptr += 2;
        }
    }

    // shift the 2-D spectrum
    int mm = w / 2;     // mm is one half of the original image width
    spectrum_shift(mm);

    sp_re[132][124] = 1;
    sp_im[132][124] = 1;
    sp_re[124][132] = 1;
    sp_im[124][132] = 1;

    // shift the 2-D spectrum back
    spectrum_shift(mm);

    // convert to the long 1D array
    ptr = 0;
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            data[ptr] = sp_re[i][j];
            data[ptr + 1] = sp_im[i][j];
            ptr += 2;
        }
    }

    fft2(data, w, -1);  // perform the inverse fft2

    // convert back to the 2D image
    vector<double> sort_array(MaxBMPSizeX * MaxBMPSizeY);
    ptr = 0;
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            sort_array[i * h + j] = data[ptr];
            sp_re[i][j] = data[ptr];
            ptr += 2;
        }
    }
    sort(sort_array.begin(), sort_array.end());
    double& Cmax = sort_array.back();
    double& Cmin = sort_array.front();
    double delta = Cmax - Cmin;
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            r[i][j] = (int)((sp_re[i][j] - Cmin) / delta * 255);
        }
    }

    delete data;
}

static inline void SWAP(double& a, double& b)
{
    double tempr = a;
    a = b;
    b = tempr;
}

/** 1-D fft program
  * Replace data by its discrete Fourier transform if isign is input as 1,
    or replace data by its inverse discrete Fourier transform if
    isign is input as -1.  "data" is a complex array of length nn, input
    as a real array data [1..2*nn], nn must be an integer power of 2.

  * If your data array is zero-offset, that is the range of data is
    [0..2*nn-1], you have to decrease the pointer to data by one when
    fft1 is invoked, for example fft1(data-1,256,1).
    The real part of the first output will now be return in data[0],
    the imaginary part in data[1] and so on.
  */
static void fft1(double data[], int nn, int isign)
{
    int n, mmax, m, j, istep, i;
    double wtemp, wr, wpr, wpi, wi, theta;
    float tempr, tempi;
    n = nn << 1;
    j = 1;
    for (i = 1; i < n; i += 2) {
        if (j > i) {
            SWAP(data[j], data[i]);
            SWAP(data[j + 1], data[i + 1]);
        }
        m = n >> 1;
        while (m >= 2 && j > m) {
            j -= m;
            m >>= 1;
        }
        j += m;
    }
    mmax = 2;
    while (n > mmax) {
        istep = 2 * mmax;
        theta = 6.28318530717959 / (-isign * mmax);
        wtemp = sin(0.5 * theta);
        wpr = -2.0 * wtemp * wtemp;
        wpi = sin(theta);
        wr = 1.0;
        wi = 0.0;
        for (m = 1; m < mmax; m += 2) {
            for (i = m; i <= n; i += istep) {
                j = i + mmax;
                tempr = (float)(wr * data[j] - wi * data[j + 1]);
                tempi = (float)(wr * data[j + 1] + wi * data[j]);
                data[j] = data[i] - tempr;
                data[j + 1] = data[i + 1] - tempi;
                data[i] += tempr;
                data[i + 1] += tempi;
            }
            wr = (wtemp = wr) * wpr - wi * wpi + wr;
            wi = wi * wpr + wtemp * wpi + wi;
        }
        mmax = istep;
    }

    if (isign == -1) {
        for (i = 1; i <= n; ++i)
            data[i] = data[i] / nn;
    }
}

/** 2-D fft2 program
  * nn is the dimension of the 2-D array..assuming square.
  * The input is read by row ordering and stored in "data" in complex form.
  * For example, if your input is
         1  2
         3  4
    That is, nn = 2, data will have dimension [0..2*nn*nn-1],
    which is [0..7]. You have to store the input as
    data[0] = real part of the (0,0)th element,
    data[1] = imaginary part of the (0,0)th element.
  * Thus, we have data[0] = 1.0, data[1] = 0.0,
    data[2] = 2.0, data[3] = 0.0, data[4] = 3.0, data[5] = 0.0,
    data[6] = 4.0, data[7] = 0.0.

  * Note that the data in this program is zero-offset, that is
  *  the range of data is [0..2*nn*nn-1]. So, you can invoke fft2.c
  *  by, for example, fft2(data,256,1).

  * isign = 1 means 2-D discrete Fourier transform.
  * isign = -1 means 2-D inverse Fourier transform.
  * When you are using inverse fft, there is no need to divide
    the results by (nn*nn), since it will be done in the program.
  */
static void fft2(double data[], int nn, int isign)
{
    int i, j, ii, jj, k, m;
    double dd[512] = { 0 };

    m = nn << 1;

    /* read data by row ordering */
    for (i = 0; i < nn; ++i) {
        k = i << 1;
        for (j = 0; j < nn; ++j) {
            jj = j << 1;
            ii = m * j;
            dd[jj] = data[ii + k];
            dd[jj + 1] = data[ii + 1 + k];
        }

        fft1(dd - 1, nn, isign);

        for (j = 0; j < nn; ++j) {
            jj = j << 1;
            ii = m * j;
            data[ii + k] = dd[jj];
            data[ii + 1 + k] = dd[jj + 1];
        }
    }    /* end of i loop */

    for (i = 0; i < nn; ++i) {
        for (j = 0; j < nn; ++j) {
            jj = j << 1;
            ii = m * i;
            dd[jj] = data[ii + jj];
            dd[jj + 1] = data[ii + jj + 1];
        }

        fft1(dd - 1, nn, isign);
        for (j = 0; j < nn; ++j) {
            jj = j << 1;
            ii = m * i;
            data[ii + jj] = dd[jj];
            data[ii + jj + 1] = dd[jj + 1];
        }
    }    /* end of i loop */

}  /* end of main */
/* ---------------------------------------------------------- */

double sp_re[MaxBMPSizeX][MaxBMPSizeY]; // real part of the spectrum
double sp_im[MaxBMPSizeX][MaxBMPSizeY]; // imaginary part of the spectrum
double tmp[MaxBMPSizeX][MaxBMPSizeY];

static void spectrum_shift(int mm) {
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