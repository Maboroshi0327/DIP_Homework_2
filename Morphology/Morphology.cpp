#include "Morphology.h"

void Noise_Removal(int(&R)[MaxBMPSizeX][MaxBMPSizeY], int(&r)[MaxBMPSizeX][MaxBMPSizeY], int w, int h)
{
    vector<vector<int>> origin(w, vector<int>(h, 0));
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            origin[i][j] = R[i][j];
        }
    }

    vector<vector<int>> result(w, vector<int>(h, 0));
    Erosion(origin, result);
    Dilation(result, origin);
    Dilation(origin, result);
    Erosion(result, origin);

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            r[i][j] = origin[i][j];
        }
    }
}

static void Erosion(vector<vector<int>>& origin, vector<vector<int>>& result)
{
    int w = (int)origin.size();
    int h = (int)origin[0].size();
    int size = 23;

    vector<vector<int>> structure(size, vector<int>(size, 255));

    for (auto& i : result)
        for (auto& j : i)
            j = 0;

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            find_match(origin, result, structure, i, j);
        }
    }
}

static void Dilation(vector<vector<int>>& origin, vector<vector<int>>& result)
{
    int w = (int)origin.size();
    int h = (int)origin[0].size();
    int size = 23;

    vector<vector<int>> structure(size, vector<int>(size, 255));

    for (auto& i : result)
        for (auto& j : i)
            j = 0;

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            filling(origin, result, structure, i, j);
        }
    }
}

static void find_match(vector<vector<int>>& origin, vector<vector<int>>& result, vector<vector<int>>& structure, int x, int y)
{
    int w = (int)structure.size();
    int h = (int)structure[0].size();

    bool flag = true;
    for (int i = 0; i < w and flag == true; i++)
    {
        for (int j = 0; j < h and flag == true; j++)
        {
            int p_x = x + i - w / 2;
            int p_y = y + j - h / 2;
            flag = 0 <= p_x and p_x <= origin.size() and 0 <= p_y and p_y <= origin[0].size() and structure[i][j] == origin[p_x][p_y];
        }
    }

    if (flag == true)
        result[x][y] = 255;
    else
        result[x][y] = 0;
}

static void filling(vector<vector<int>>& origin, vector<vector<int>>& result, vector<vector<int>>& structure, int x, int y)
{
    int w_o = (int)origin.size();
    int h_o = (int)origin[0].size();
    int w_s = (int)structure.size();
    int h_s = (int)structure[0].size();

    if (origin[x][y] == 255)
    {
        for (int i = 0; i < w_s; i++)
        {
            for (int j = 0; j < h_s; j++)
            {
                int p_x = x + i - w_s / 2;
                int p_y = y + j - h_s / 2;
                if (0 <= p_x and p_x <= w_o and 0 <= p_y and p_y <= h_o and structure[i][j] == 255)
                    result[p_x][p_y] = 255;
                else
                    result[p_x][p_y] = 0;
            }
        }
    }
}
