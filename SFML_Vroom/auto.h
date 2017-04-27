/*En-t�te du fichier d'en-t�te
================================
Auteurs		: �mile Loiselle et Francis Forest
Nom du .h	: auto.h
Date		: 21 avril 2017
But			: G�rer toutes les variables int�ressantes pour une automobile.*/

//On s'assure que si ce fichier est #include plus d'une fois, il ne sera inclus qu'une seule fois pour tout le programme
#pragma once

using namespace sf;

//Constantes
const double PI = atan(1) * 4;

//Classe
class automobile
{

private:

	//Touches pour le joueur
	Keyboard::Key _autoControles[4];

	//�tats de l'auto
	double _velociteX;
	double _velociteY;
	int _derniereDirection;

	int _virage;
	double _degree;
	double _radian;

	//Autres options
	double _vitesseMax;

	//Acc�l�rations
	double _vitesseIncrementation;
	double _angleIncrementation;
	double _vitesseAffaiblir;

	//Couleur de l'auto
	int _autoRGB[3];

public:

	//Constructeur / D�constructeur
	automobile();
	~automobile();

	//Obtient v�locit�
	double getVelociteX();
	double getVelociteY();

	//Acc�l�ration / Vitesse Max
	double getVitesseIncrementation();
	double getVitesseMax();

	//Obtient Degr� / Vitesse de virage
	double getDegre();
	double getAngleIncrementation();
	int getRed();
	int getGreen();
	int getBlue();

	//Change v�locit�
	void setVelociteY(double velociteY);
	void setVelociteX(double velociteX);
	void changerDirection(int direction);

	//Change Degr� / Virage
	void setDegre(double degre);
	void setVirage(int virage);
	void setCouleur(int red, int green, int blue);

	double convertDegreeRadian(double degre);
	void effectuerVirage();
	void effectuerVelocite(double tempsDelta);
	void velociteAffaiblir(int multiple);

	void collision();

	//Get touches joueur
	Keyboard::Key getUp();
	Keyboard::Key getDown();
	Keyboard::Key getLeft();
	Keyboard::Key getRight();

	//Set touches joueur
	void setKeys(Keyboard::Key up, Keyboard::Key down, Keyboard::Key left, Keyboard::Key right);
};

automobile::automobile()
{
	//�tats de l'auto
	_velociteX = 0;					//La vitesse actuelle de l'auto�(sur l'axe des X)
	_velociteY = 0;					//La vitesse actuelle de l'auto�(sur l'axe des Y)
	_virage = 0;					//1 = Gauche, 2 = Droite, 0 = Nulle
	_degree = 90;					//L'angle actuel, en degr�, de l'auto
	_radian = 0;					//L'angle actuel, en radian, de l'auto
	_derniereDirection = 1;

	//Autres options
	_vitesseMax = 250;				//Vitesse maximale

	//Acc�l�rations
	_vitesseIncrementation = 0.4;		//La vitesse � laquelle l'auto fais son acc�l�ration
	_angleIncrementation = 4;		//La vitesse � laquelle l'auto fais ses virage
	_vitesseAffaiblir = 0.995;		//La vitesse � laquelle l'auto ralenti naturellement

	//Couleur de l'auto
	_autoRGB[0] = 125;
	_autoRGB[1] = 125;
	_autoRGB[2] = 125;
}

automobile::~automobile()
{

}

//==Get==
#pragma region "Getters"
//Informations vitesse
double automobile::getVelociteX()
{
	return _velociteX;
}

double automobile::getVelociteY()
{
	return _velociteY;
}

double automobile::getVitesseIncrementation()
{
	return _vitesseIncrementation;
}

double automobile::getVitesseMax()
{
	return _vitesseMax;
}

//Informations d'angle
double automobile::getDegre()
{
	return _degree;
}

double automobile::getAngleIncrementation()
{
	return _angleIncrementation;
}

//Get couleur du v�hicule
int automobile::getRed()
{
	return _autoRGB[0];
}

int automobile::getGreen()
{
	return _autoRGB[1];
}

int automobile::getBlue()
{
	return _autoRGB[2];
}

//Get contr�les du v�hicule
Keyboard::Key automobile::getUp()
{
	return _autoControles[0];
}

Keyboard::Key automobile::getDown()
{
	return _autoControles[1];
}

Keyboard::Key automobile::getLeft()
{
	return _autoControles[2];
}

Keyboard::Key automobile::getRight()
{
	return _autoControles[3];
}
#pragma endregion

//==Set==
#pragma region "Setters"
void automobile::setVelociteX(double velociteX)
{
	_velociteX = velociteX;
}

void automobile::setVelociteY(double velociteY)
{
	_velociteY = velociteY;
}

void automobile::changerDirection(int direction)
{
	_derniereDirection = direction;
}

void automobile::setDegre(double degree)
{
	_degree = degree;
}

void automobile::setVirage(int virage)
{
	_virage = virage;
}

void automobile::setKeys(Keyboard::Key up, Keyboard::Key down, Keyboard::Key left, Keyboard::Key right)
{
	_autoControles[0] = up;
	_autoControles[1] = down;
	_autoControles[2] = left;
	_autoControles[3] = right;
}

//Changes la couleur d'une auto (RGB)
void automobile::setCouleur(int red, int green, int blue)
{
	_autoRGB[0] = red;
	_autoRGB[1] = green;
	_autoRGB[2] = blue;
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
void automobile::effectuerVelocite(double tempsDelta)
{
	//Si on avance
	if (_derniereDirection == 1)
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
	else if (_derniereDirection == 0)
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

//D�c�l�ration naturelle de la v�locit�
void automobile::velociteAffaiblir(int multiple)
{
	_velociteX *= (_vitesseAffaiblir - multiple);
	_velociteY *= (_vitesseAffaiblir - multiple);

}

//G�re la collision d'un auto
void automobile::collision()
{
	if (_derniereDirection == 1)
		if (_velociteX > 0 && _velociteY > 0)
		{
			_velociteX = -(_velociteX / 2);
			_velociteY = -(_velociteY / 2);
		}

	else if (_derniereDirection == 0)
		if (_velociteX < 0 && _velociteY < 0)
		{
			_velociteX = -(_velociteX / 2);
			_velociteY = -(_velociteY / 2);
		}
}