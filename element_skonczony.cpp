#include "node.cpp"

class ElementSkonczony
{
    node * node1;
    node * node2;
    double s, k, dl;
    int idGlobalne1, idGlobalne2;
    double** hLokalne;
    double* pLokalne;

public:



    ElementSkonczony(node* node1, node*node2, double s, double k, int idGlobalne1, int idGlobalne2)
    {
        this->node1 = node1;
        this->node2 = node2;
        this->s = s;
        this->k = k;
        this->idGlobalne1 = idGlobalne1;
        this->idGlobalne2 = idGlobalne2;
        this->dl = node2->getx() - node1->getx();

        hLokalne = new double*[2];

        for (int i = 0; i < 2; i++)
        {
            hLokalne[i] = new double[2];
            for (int j = 0; j < 2; j++)
                hLokalne[i][j] = 0;
        }

        pLokalne = new double[2];

        for (int k = 0; k < 2; k++)
            pLokalne[k] = 0;


    }

    void obliczHLokalne()
    {
        double c = 0;
        c = (s*k) / dl;

        // wyliczanie macierzy lokalnej H

        hLokalne[0][0] = c;
        hLokalne[0][1] = -c;
        hLokalne[1][0] = -c;
        hLokalne[1][1] = c;

        // warunki brzegowe

        if (node1->warunekKonwekcjae() == true)
            hLokalne[0][0] = c + node1->getAlfa()*s;

        if (node2->warunekKonwekcjae() == true)
            hLokalne[1][1] = c + node2->getAlfa()*s;

    }


    // wyliczanie macierzy lokalnej P

    void obliczPLokalne()
    {
        if (node1->czyWarunekQ() == true)
            pLokalne[0] = node1->getQ()*s;

        if (node2->czyWarunekQ() == true)
            pLokalne[1] = node2->getQ()*s;

        if (node1->warunekKonwekcjae() == true)
            pLokalne[0] = -node1->getAlfa()*s*node1->getTemperaturaOtoczenia();

        if (node2->warunekKonwekcjae() == true)
            pLokalne[1] = -node2->getAlfa()*s*node2->getTemperaturaOtoczenia();

    }


    int getIdGlobalne1()
    {
        return idGlobalne1;
    }

    int getIdGlobalne2()
    {
        return idGlobalne2;
    }

    double** getHLokalne()
    {
        return hLokalne;
    }

    double* getPLokalne()
    {
        return pLokalne;
    }



};
