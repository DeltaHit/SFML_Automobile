/*En-t�te du fichier d'en-t�te
================================
Auteurs		: �mile Loiselle et Francis Forest
Nom du .h	: auto.h
Date		: 21 avril 2017
But			: G�rer toutes les variables int�ressantes pour une automobile.*/

//On s'assure que si ce fichier est #include plus d'une fois, il ne sera inclus qu'une seule fois pour tout le programme
#pragma once

//Constantes
const double PI = atan(1) * 4;

//Classe
class automobile
{

private:

	float _velociteX;
	float _velociteY;
	double _vitesseIncrementation;
	float _vitesseMax;
	float _vitesseAffaiblir;

	double _degree;
	double _radian;
	double _angleIncrementation;

	int _virage;

public:

	//Constructeur / D�constructeur
	automobile();
	~automobile();

	//Obtient v�locit�
	float getVelociteX();
	float getVelociteY();

	//Acc�l�ration / Vitesse Max
	double getVitesseIncrementation();
	float getVitesseMax();

	//Obtient Degr� / Vitesse de virage
	double getDegre();
	double getAngleIncrementation();

	//Change v�locit�
	void setVelociteY(float velociteY);
	void setVelociteX(float velociteX);

	//Change Degr� / Virage
	void setDegre(double degre);
	void setVirage(int virage);

	double convertDegreeRadian(double degre);
	void effectuerVirage();
	void effectuerVelocite(int direction, double tempsDelta);
	void velociteAffaiblir();
};

automobile::automobile()
{
	_velociteX = 0;					//La vitesse actuelle de l'auto
	_velociteY = 0;
	_vitesseMax = 250;
	_vitesseAffaiblir = 0.995;
	_degree = 270;					//L'angle actuel, en degr�, de l'auto
	_radian = 0;					//L'angle actuel, en radian, de l'auto

	_vitesseIncrementation = 0.4;		//La vitesse � laquelle l'auto fais son acc�l�ration
	_angleIncrementation = 4;		//La vitesse � laquelle l'auto fais ses virage

	_virage = 0;					//1 = Gauche, 2 = Droite, 0 = Nulle
}

automobile::~automobile()
{

}

//==Get==
#pragma region "Getters"
float automobile::getVelociteX()
{
	return _velociteX;
}

float automobile::getVelociteY()
{
	return _velociteY;
}

double automobile::getVitesseIncrementation()
{
	return _vitesseIncrementation;
}

float automobile::getVitesseMax()
{
	return _vitesseMax;
}

double automobile::getDegre()
{
	return _degree;
}

double automobile::getAngleIncrementation()
{
	return _angleIncrementation;
}
#pragma endregion

//==Set==
#pragma region "Setters"
void automobile::setVelociteX(float velociteX)
{
	_velociteX = velociteX;
}

void automobile::setVelociteY(float velociteY)
{
	_velociteY = velociteY;
}

void automobile::setDegre(double degree)
{
	_degree = degree;
}

void automobile::setVirage(int virage)
{
	_virage = virage;
}
#pragma endregion

//Convertit un angle en degree vers un radian
double automobile::convertDegreeRadian(double degree)
{
	return 2 * PI * (degree / 360);
}

//Effectue un virage selon l'angle actuel et la direction du virage d�sir�e
void automobile::effectuerVirage()
{
	//Gauche
	if (_virage == 1)
	{
		_degree = _degree - _angleIncrementation;
	}
	//Droite
	else if (_virage == 2)
	{
		_degree = _degree + _angleIncrementation;
	}
}

//Ajuste la v�locit� bas�e sur la direction d�sir�e et le temps �coul�
void automobile::effectuerVelocite(int direction, double tempsDelta)
{
	//Si on avance
	if (direction == 1)
	{
		//Si la v�locit�e est plus petite que la vitesse maximale
		if (_velociteX < _vitesseMax)
			//On ajoute de la vitesse
			_velociteX += _vitesseIncrementation * tempsDelta;

		//M�me chose pour Y
		if (_velociteY < _vitesseMax)
			_velociteY += _vitesseIncrementation * tempsDelta;
	}

	//Si on recule
	else if (direction == 0)
	{
		//Si on a pas atteint la vitesse maximale sur X � reculons
		if (_velociteX > -(_vitesseMax / 2))
			//On recule plus vite
			_velociteX -= (_vitesseIncrementation / 2) * tempsDelta;
		else
			//Sinon la vitesse du reculons est celle maximale
			_velociteX = -(_vitesseMax / 2);

		//M�me chose pour le Y
		if (_velociteY > -(_vitesseMax / 2))
			_velociteY -= (_vitesseIncrementation / 2) * tempsDelta;
		else
			_velociteY = -(_vitesseMax / 2);
	}
}

void automobile::velociteAffaiblir()
{
	_velociteX *= _vitesseAffaiblir;
	_velociteY *= _vitesseAffaiblir;

}