/*En-t�te du fichier d'en-t�te
================================
Auteurs		: �mile Loiselle et Francis Forest
Nom du .h	: piste.h
Date		: 27 avril 2017
But			: Traffics Lights. Permet au joueur de s'avoir quand la course d�bute. De couleur rouge, change � jaune puis � vert 
			  selon le temps de jeu �coul�.*/

//On s'assure que si ce fichier est #include plus d'une fois, il ne sera inclus qu'une seule fois pour tout le programme
#pragma once

//Directives au pr�-processeur
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>

using namespace std;
using namespace sf;

//Objet
class trafficLights
{
private:
	string _nom;							//nom du trafficLights
	Texture _texture;						//texture du trafficLights
	Sprite _sprite;							//sprite du trafficLights
						
public:
	trafficLights();						//Constructeur sans param�tre. Charge la texture de la lumi�re rouge et la met dans le sprite
	~trafficLights();						//destructeur

	void setPosition(int x, int y);			//set la position du sprite

	void changerLumiere(Clock clock);		//change la couleur de la lumi�re selon le temps de jeu pass� en param�tre

	Sprite getSprite();						//fet le sprite

};

//Constructeur sans param�tre. Charge la texture de la lumi�re rouge et la met dans le sprite
trafficLights::trafficLights()
{
	_nom = "trafficLights";

	_texture.loadFromFile(_nom + "rouge.png", IntRect(0, 0, 200, 137));
	

	_sprite.setTexture(_texture);
}

//destructeur
trafficLights::~trafficLights()
{
}

//change la couleur de la lumi�re selon le temps de jeu pass� en param�tre
void trafficLights::changerLumiere(Clock clock)
{
	Time temps;											//evalue temps pass�

	temps = clock.getElapsedTime();
	
	if (temps.asSeconds() <= 3)							//lumi�re rouge
	{
		_texture.loadFromFile(_nom + "Rouge.png", IntRect(0, 0, 200, 137));
		

		_sprite.setTexture(_texture);
	}

	else if (temps.asSeconds() <= 5)					//lumi�re jaune
	{
		_texture.loadFromFile(_nom + "Jaune.png", IntRect(0, 0, 200, 137));
		

		_sprite.setTexture(_texture);
	}
	else if (temps.asSeconds() <= 6)					//lumi�re verte
	{
		_texture.loadFromFile(_nom + "Verte.png", IntRect(0, 0, 200, 137));
		

		_sprite.setTexture(_texture);
	}
}

//get le sprite
Sprite trafficLights::getSprite()
{
	return _sprite;
}

//set la position du sprite
void trafficLights::setPosition(int x, int y)
{
	_sprite.setPosition(x, y);
}
