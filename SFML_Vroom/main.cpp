/* En-t�te du programme
=========================
Auteurs		: �mile Loiselle et Francis Forest
Nom du CPP	: main.cpp
Date		: 21 avril 2017
But			: Contr�ler un automobile sur une piste de course le plus rapidement possible. */

//Directives au pr�-processeur
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "auto.h"
#include "piste.h"
#include "trafficLights.h"
using namespace sf;
using namespace std;

//Programme principal
int main()
{
	//Initialisation SFML
	RenderWindow window(VideoMode(1280, 768), "Vroooom!!!");					//fenetre
	Texture textureCar;															//texture voiture
	RenderTexture;				

	piste pisteCourse("points4");												//objet Piste

	Sprite car;																	//sprite voiture

	Clock horlogeDelta;			//https://en.wikipedia.org/wiki/%CE%94T
	Clock tempsJeu;																//temps depuis debut partie
	Time temps;																	//utilis� pour prendre le temps de clock tempsJeu

	automobile joueur;															//premier joueur
	bool canDrive = false;														//voiture peut pas bouger pendant traffic lights
	trafficLights lights;

	Event event;

	window.setFramerateLimit(60);												//Limite le nombre d'images par secondes

	textureCar.loadFromFile("orange32x16.png", IntRect(0, 0, 32, 16));			//Chargement des textures
	
	car.setTexture(textureCar);													//Insertion des textures dans leur sprite r�spectifs
	
	car.setOrigin(12, 8);														//offre rotation plus juste
	pisteCourse.setPosition(120, 100);
	lights.setPosition(585, 300);

	car.setPosition(190, 395);													//Initialisation auto
	car.rotate(joueur.getDegre());
	
	while (window.isOpen())														//Tant que le jeu roule
	{
		Time tempsDelta = horlogeDelta.restart();								//R�initialise l'horloge

		//Attend les �v�nements
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
				window.close();

		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))						//Gauche
			joueur.setVirage(1);

		
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))				//Droite
			joueur.setVirage(2);
	
		else
			joueur.setVirage(0);												//Nulle

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))						//Haut
			joueur.effectuerVelocite(1, tempsDelta.asMilliseconds());

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))						//Bas
			joueur.effectuerVelocite(0, tempsDelta.asMilliseconds());

		temps = tempsJeu.getElapsedTime();
		
		if (temps.asSeconds() >= 5)												//pas bouger pendant traffic lights
		{
			canDrive = true;
		}

		//G�re les virages
		if (canDrive == true)								//course est commenc�e --> voiture peut bouger
		{
			joueur.effectuerVirage();
			car.setRotation(joueur.getDegre());
			joueur.setVirage(0);

			//G�re le mouvement du v�hicule
			car.move(joueur.getVelociteX() * cos(joueur.convertDegreeRadian(joueur.getDegre())) * tempsDelta.asSeconds(),
					 joueur.getVelociteY() * sin(joueur.convertDegreeRadian(joueur.getDegre())) * tempsDelta.asSeconds());

			//Affaiblissement de la v�locit�
			joueur.velociteAffaiblir();

		}

		//G�re l'affichage
		window.clear(Color(0, 150, 0));
		window.draw(pisteCourse.getSprite());						//affiche piste

		for (int i = 0; i < pisteCourse.getNbCollisions(); i++)		//affiche toutes les formes de collisions --> afin de tester collisions
		{
			window.draw(pisteCourse.getCollisions(i));
		}

		window.draw(car);											//affiche voiture

		lights.changerLumiere(tempsJeu);
		window.draw(lights.getSprite());

		window.display();


	}
	return 0;
}
