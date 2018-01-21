
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;




const double eps = 1e-12; // stala przybli¿enia zera

// Funkcja realizuje algorytm eliminacji Gaussa
//---------------------------------------------
bool eliminacjaGaussa(int n, double ** H, double * P, double* X)
{

    double** AB = new double*[n];

    for (int i = 0; i < n; i++)
    {
        AB[i] = new double[n+1];

        for (int j = 0; j < n; j++)
        {
            AB[i][j] = H[i][j];
        }


        AB[i][n] = -P[i];
    }

    int i, j, k;
    double m, s;

    // eliminacja wspólczynników

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (fabs(AB[i][i]) < eps) return false;
            m = -AB[j][i] / AB[i][i];
            for (k = i + 1; k <= n; k++)
                AB[j][k] += m * AB[i][k];
        }
    }

    // wyliczanie niewiadomych

    for (i = n - 1; i >= 0; i--)
    {
        s = AB[i][n];
        for (j = n - 1; j >= i + 1; j--)
            s -= AB[i][j] * X[j];
        if (fabs(AB[i][i]) < eps) return false;
        X[i] = s / AB[i][i];
    }
    return true;
}
