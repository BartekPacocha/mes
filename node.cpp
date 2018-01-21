class node
{
	double x=0; // wspolrzedne
	double q; // strumien ciepla
	bool warunekQ = false; // na pow zadany jest strumien ciepla q
	double alfa; // wsp konwekcyjnej wymiany ciepla
	double temperaturaOtoczenia; // temp otoczenia
	bool warunekKonwekcja = false; // na pow jest zadana temp


public:

	void setX(double x)
	{
		this->x = x;
	}

	double getx()
	{
		return x;
	}

	void setQ (double q)
	{
		this->q = q;
		warunekQ = true;
	}

	void setTemperaturaOtoczenia(double alfa, double temperaturaOtoczenia)
	{
		this->alfa = alfa;
		this->temperaturaOtoczenia = temperaturaOtoczenia;
		warunekKonwekcja = true;
	}

	double getQ()
	{
		return q;
	}

	double getAlfa()
	{
		return alfa;
	}

	bool czyWarunekQ()
	{
			return warunekQ;
	}
	double getTemperaturaOtoczenia()
	{
		return temperaturaOtoczenia;
	}

	bool warunekKonwekcjae()
	{
		return warunekKonwekcja;
	}

};





