/* En-t�te du programme
=========================
Auteurs		: �mile Loiselle et Francis Forest
Nom du CPP	: main.cpp
Date		: 21 avril 2017
But			: Contr�ler un automobile sur une piste de course le plus rapidement possible. */

//Lien de discussion instantan�: https://tlk.io/sfml_automobile

//Directives au pr�-processeur
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <SFML/Graphics.hpp>
#include "auto.h"
using namespace sf;

//Programme principal
int main()
{
	//Seed pour la g�n�ration al�atoire des couleures des autos
	srand(time(NULL));

	//Nombre de joueurs dans la partie
	int nbJoueurs = 2;

	//Initialisation SFML
	RenderWindow window(VideoMode(1280, 720), "Vroooom!!!");
	Texture texture;
	RenderTexture;
	Sprite sprJoueur[4];
	Event event;
	Clock horlogeDelta;			//https://en.wikipedia.org/wiki/%CE%94T

	//Limite le nombre d'images par secondes
	window.setFramerateLimit(60);

	//Variables
	automobile joueurs[4];

	//joueurs[0].setCouleur(255, 0, 255);
	//joueurs[1].setCouleur(255, 0, 0);
	//joueurs[2].setCouleur(0, 0, 255);
	//joueurs[3].setCouleur(0, 255, 0);

	for (int i = 1; i < nbJoueurs + 1; i++)
	{
		//Chargement de la texture pour l'auto sp�cifi�e
		texture.loadFromFile("car.png");
		sprJoueur[i].setTexture(texture);
		sprJoueur[i].setOrigin(12, 8);

		//G�n�re une couleur al�atoire
		joueurs[i].setCouleur(rand() % 255, rand() % 255, rand() % 255);
		sprJoueur[i].setColor(Color(joueurs[i].getRed(), joueurs[i].getGreen(), joueurs[i].getBlue()));

		//Initialisation auto
		sprJoueur[i].setPosition(100 * i, 100);
		sprJoueur[i].rotate(joueurs[i].getDegre());
	}

	//Tant que le jeu roule
	while (window.isOpen())
	{
		//Efface l'affichage pr�c�dent
		window.clear();

		//R�initialise l'horloge delta, ce qui permet une exp�rience de jeu fluide sur n'importe quelle machine
		Time tempsDelta = horlogeDelta.restart();

		//Si on appuie sur X ou Escape, on ferme le jeu
		while (window.pollEvent(event))
			if (event.type == Event::Closed || ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)))
				window.close();

		for (int i = nbJoueurs; i > 0; i--)
		{
			if (i == 1)
			{
				//Gauche
				if (Keyboard::isKeyPressed(Keyboard::Left))
					joueurs[i].setVirage(1);

				//Droite
				else if (Keyboard::isKeyPressed(Keyboard::Right))
					joueurs[i].setVirage(2);

				//Nulle
				else
					joueurs[i].setVirage(0);

				//Haut
				if (Keyboard::isKeyPressed(Keyboard::Up))
					joueurs[i].effectuerVelocite(1, tempsDelta.asMilliseconds());

				//Bas
				if (Keyboard::isKeyPressed(Keyboard::Down))
					joueurs[i].effectuerVelocite(0, tempsDelta.asMilliseconds());
			}

			else if (i == 2)
			{
				//Gauche
				if (Keyboard::isKeyPressed(Keyboard::A))
					joueurs[i].setVirage(1);

				//Droite
				else if (Keyboard::isKeyPressed(Keyboard::D))
					joueurs[i].setVirage(2);

				//Nulle
				else
					joueurs[i].setVirage(0);

				//Haut
				if (Keyboard::isKeyPressed(Keyboard::W))
					joueurs[i].effectuerVelocite(1, tempsDelta.asMilliseconds());

				//Bas
				if (Keyboard::isKeyPressed(Keyboard::S))
					joueurs[i].effectuerVelocite(0, tempsDelta.asMilliseconds());
			}

			//G�re la collision de joueur 1 vers joueur 2
			if (sprJoueur[1].getGlobalBounds().intersects(sprJoueur[2].getGlobalBounds()))
			{
				joueurs[1].collision();
			}

			//G�re la collisison de joueur 2 vers joueur 1
			else if (sprJoueur[2].getGlobalBounds().intersects(sprJoueur[1].getGlobalBounds()))
			{
				joueurs[2].collision();
			}

			//Emp�che les joueurs de virer lorsqu'il y a collisison
			else
			{
				//G�re les virages
				joueurs[i].effectuerVirage();
				sprJoueur[i].setRotation(joueurs[i].getDegre());
				joueurs[i].setVirage(0);
			}

			//G�re le mouvement du v�hicule
			sprJoueur[i].move(
				joueurs[i].getVelociteX() * cos(
					joueurs[i].convertDegreeRadian(joueurs[i].getDegre())) * tempsDelta.asSeconds(),
				joueurs[i].getVelociteY() * sin(
					joueurs[i].convertDegreeRadian(joueurs[i].getDegre())) * tempsDelta.asSeconds());

			//Affaiblissement de la v�locit�
			joueurs[i].velociteAffaiblir();

			//Affichage de l'auto en question
			window.draw(sprJoueur[i]);
		}

		//Rafra�chi l'affichage au complet
		window.display();
	}
	return 0;
}