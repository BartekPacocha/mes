#include <iostream>
#include <fstream>
#include "element_skonczony.cpp"


using namespace std;


bool eliminacjaGaussa(int n, double ** H, double * P, double* X);


node * wczytajWezly(fstream & input, int liczbaWezlow)
{
    node * wezly = new node[liczbaWezlow];
    for (int i = 0; i < liczbaWezlow; i++)
    {
        int id;
        input >> id;
        double x;
        input >> x;
        wezly[id - 1].setX(x);
    }
    return wezly;
};

ElementSkonczony** wczytajElementy(fstream & input, int liczbaElementow, node * wezly)
{
    ElementSkonczony** elementy = new ElementSkonczony*[liczbaElementow];

    for (int i = 0; i < liczbaElementow; i++)
    {
        int id;
        input >> id;
        int idw1;
        input >> idw1;
        int idw2;
        input >> idw2;
        double s;
        input >> s;
        double k;
        input >> k;
        elementy[id - 1] = new ElementSkonczony(&wezly[idw1 - 1], &wezly[idw2 - 1], s, k, idw1 - 1, idw2 - 1);
    }
    return elementy;

};

void wczytajWarunkiBrzegowe(fstream & input, int liczbaWaronkow, node *& wezly)
{
    for (int i = 0; i < liczbaWaronkow; i++)
    {
        int idwezla, typwar;
        input >> idwezla;
        input >> typwar;
        if (typwar == 1)
        {
            double q;
            input >> q;
            wezly[idwezla - 1].setQ(q);
        }
        else if (typwar == 2)
        {
            double a, temperaturaOtoczenia;
            input >> a;
            input >> temperaturaOtoczenia;
            wezly[idwezla - 1].setTemperaturaOtoczenia(a, temperaturaOtoczenia);
        }
    }
}

int wczytaj(int & liczbaWezlow, node *& wezly, int & liczbaElementow, int & liczbaWaronkow, ElementSkonczony**& elementy)
{
    fstream input;
    input.open("input.txt");
    if (input.good() != true)
    {
        cout << "blad pliku";
        return 1;
    }

    input >> liczbaWezlow;
    wezly = wczytajWezly(input, liczbaWezlow);

    input >> liczbaElementow;
    elementy = wczytajElementy(input, liczbaElementow, wezly);

    input >> liczbaWaronkow;
    wczytajWarunkiBrzegowe(input, liczbaWaronkow, wezly);

    input.close();
};

// utworzenie macierzy 1xnh i wyzerowanie
double* przygotujMacierz(int n)
{
    double* macierz = new double[n];
    for (int i = 0; i < n; i++)
    {
        macierz[i] = 0;
    }
    return macierz;
}

// utworzenie macierzy nh x nh i wyzerowanie
double** przygotujMacierzDwuwymiarowa(int n)
{
    double** macierz = new double *[n];
    for (int i = 0; i < n; i++)
    {
        macierz[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            macierz[i][j] = 0;
        }
    }
    return macierz;
}


void mes(int liczbaElementow, ElementSkonczony ** elementy, double**& hGlobalne, double *& pGlobalne)
{
    // obliczenie H i P lokalne wszystkich elementow
    for (int i = 0; i < liczbaElementow; i++)
    {
        elementy[i]->obliczHLokalne();
        elementy[i]->obliczPLokalne();
    }


    // budowa HG i PG w oparciu o H i P lokalne
    for (int i = 0; i < liczbaElementow; i++)
    {
        int idGlobalne1 = elementy[i]->getIdGlobalne1();
        int idGlobalne2 = elementy[i]->getIdGlobalne2();

        double ** hLokalne = elementy[i]->getHLokalne();
        hGlobalne[idGlobalne1][idGlobalne1] += hLokalne[0][0];
        hGlobalne[idGlobalne1][idGlobalne2] += hLokalne[0][1];
        hGlobalne[idGlobalne2][idGlobalne1] += hLokalne[1][0];
        hGlobalne[idGlobalne2][idGlobalne2] += hLokalne[1][1];

        double * pLokalne = elementy[i]->getPLokalne();
        pGlobalne[idGlobalne1] += pLokalne[0];
        pGlobalne[idGlobalne2] += pLokalne[1];


    }

}

 void zapis(double * temp, int liczbaWezlow)
    {
        ofstream wynik;
    wynik.open("wynik.txt");


    for (int i = 0; i < liczbaWezlow; i++)
    {
        wynik << temp[i] << " | ";
        cout << temp[i] << " | ";
    }

    wynik.close();
    cout << endl;
    }

int main()
{

    int liczbaWezlow;
    int liczbaElementow;
    node* wezly;
    ElementSkonczony** elementy;
    int liczbaWaronkow;

    wczytaj(liczbaWezlow, wezly, liczbaElementow, liczbaWaronkow, elementy);

    double** hGlobalne = przygotujMacierzDwuwymiarowa(liczbaWezlow);
    double * pGlobalne = przygotujMacierz(liczbaWezlow);
    double* temp = przygotujMacierz(liczbaWezlow);

    mes(liczbaElementow, elementy, hGlobalne, pGlobalne);

    eliminacjaGaussa(liczbaWezlow, hGlobalne, pGlobalne, temp);

    zapis(temp, liczbaWezlow);






    return 0;
}
