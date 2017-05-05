/* En-tête du programme
=========================
Auteurs		: Émile Loiselle et Francis Forest
Nom du CPP	: main.cpp
Date		: 21 avril 2017
But			: Contrôler un automobile sur une piste de course le plus rapidement possible. */

//Lien de discussion instantané: https://tlk.io/sfml_automobile

//Pseudo-code drifts

//Directives au pré-processeur
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "auto.h"
#include "piste.h"
#include "trafficLights.h"
using namespace sf;
using namespace std;

bool afficherMenu(RenderWindow& window, Font font);


//Programme principal
int main()
{
	//Variables
	trafficLights lights;
	piste pisteCourse("mapFinale2");													//objet Piste
	automobile joueurs[4];

	int nbJoueurs = 4;	        //Nombre de joueurs, entre 1 et 4
	bool canDrive = false;			//voiture peut pas bouger pendant traffic lights
	bool jouer = false;
	bool quitter = false;
  double diff = 0;

	//Initialisation SFML
	RenderWindow window(VideoMode(1280, 768), "Vroooom!!!");					//fenetre
	window.setFramerateLimit(60);

	Texture textureCar;															//texture voiture

	//TEMPS ET CLOCKS
	Clock horlogeDelta;															//https://en.wikipedia.org/wiki/%CE%94T
	Clock tempsJeu;																//temps depuis debut partie

	Time temps;																	//utilisé pour prendre le temps de clock tempsJeu
	Time tempsTest;
	Clock tempsMenu;

	//EVENT
	Event event;
  
  //Font et texts
	Font font;
	Text chrono;
  
	font.loadFromFile("Roboto-Italic.ttf");
	chrono.setFont(font);
	chrono.setPosition(20, 20);

  Sprite sprJoueur[4];
  
	//Change les couleures de chaque joueurs
	joueurs[0].setCouleur(0, 255, 0);
	joueurs[1].setCouleur(255, 0, 0);
	joueurs[2].setCouleur(0, 255, 255);
	joueurs[3].setCouleur(255, 255, 0);

	//Applique les touches à utiliser pour chaques joueurs
	joueurs[0].setKeys(Keyboard::Up, Keyboard::Down, Keyboard::Left, Keyboard::Right);
	joueurs[1].setKeys(Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D);
	joueurs[2].setKeys(Keyboard::I, Keyboard::K, Keyboard::J, Keyboard::L);
	joueurs[3].setKeys(Keyboard::T, Keyboard::G, Keyboard::F, Keyboard::H);

	//Chargement de chaque joueurs
	for (int i = 0; i < nbJoueurs; i++)
	{
		//Chargement de la texture pour l'auto spécifiée
		textureCar.loadFromFile("car.png");
		sprJoueur[i].setTexture(textureCar);
		sprJoueur[i].setOrigin(12, 8);
		sprJoueur[i].setColor(Color(joueurs[i].getRed(), joueurs[i].getGreen(), joueurs[i].getBlue()));

		//Initialisation automobile
		sprJoueur[i].setPosition(100 + (100 * i), 100);
		sprJoueur[i].rotate(joueurs[i].getDegreAuto());
	}
	//Limite le nombre d'images par secondes

	lights.setPosition(585, 300);

	while (!quitter)
	{
		
		jouer = afficherMenu(window, font);
		tempsJeu.restart();

		if (!jouer)															//On quitte le programme
		{
			return 0;
		}

		while (jouer)														//Tant que le jeu roule
		{

			//Attend les événements de fermeture
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed || ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)))
				{
					if (jouer)
					{
						jouer = false;
					}
					else
					{
						return 0;
					}
				}
			}

			temps = tempsJeu.getElapsedTime();

			if (temps.asSeconds() >= 5)												//pas bouger pendant traffic lights
			{
				canDrive = true;
			}
			else
			{
				canDrive = false;
			}

			//Réinitialise l'horloge
			Time tempsDelta = horlogeDelta.restart();

			//Événements de jeu
			for (int i = 0; i < nbJoueurs; i++)
			{
				//Si le départ n'a pas été lancé
				if (canDrive == false)
					break;

				//Gauche
				if (Keyboard::isKeyPressed(joueurs[i].getLeft()))
					joueurs[i].setVirage(1);

				//Droite
				else if (Keyboard::isKeyPressed(joueurs[i].getRight()))
					joueurs[i].setVirage(2);

				//Nulle
				else
					joueurs[i].setVirage(0);

				//Haut
				if (Keyboard::isKeyPressed(joueurs[i].getUp()))
				{
					joueurs[i].changerDirection(1);
					joueurs[i].effectuerVelocite(tempsDelta.asMilliseconds());
        }
        
        //Bas
				if (Keyboard::isKeyPressed(joueurs[i].getDown()))
				{
					joueurs[i].changerDirection(0);
					joueurs[i].effectuerVelocite(tempsDelta.asMilliseconds());
        }

				//Gère les collisions entre chaque autos
				for (int j = 0; j < nbJoueurs; j++)
				{
					//Si on touche une auto
					if (i != j && sprJoueur[i].getGlobalBounds().intersects(sprJoueur[j].getGlobalBounds()))
					{
						joueurs[i].collision();
						break;
					}
          
					//Gère les virages
					joueurs[i].effectuerVirage();
					sprJoueur[i].setRotation(joueurs[i].getDegreAuto());
					joueurs[i].setVirage(0);
				}

				//MOUVEMENT DES AUTOS*******************************************************************
				//**************************************************************************************
				sprJoueur[i].move(
					joueurs[i].getVelociteX() * cos(
						joueurs[i].convertDegreeRadian(joueurs[i].getDegre())) * tempsDelta.asSeconds(),
					joueurs[i].getVelociteY() * sin(
						joueurs[i].convertDegreeRadian(joueurs[i].getDegre())) * tempsDelta.asSeconds());

        //AFFICHAGE*****************************************************************************
			//**************************************************************************************
			joueurs[i].calculDrift();
        
				//Affaiblissement de la vélocité
				joueurs[i].velociteAffaiblir(0);
			}

			//Efface l'affichage précédent
			window.clear(Color(0, 125, 0));

			//Affiche la piste
			window.draw(pisteCourse.getSprite());

			//affiche chrono
			if (temps.asSeconds() >= 5)
			{
				chrono.setString(to_string(temps.asSeconds() - 5));
				window.draw(chrono);
			}

			//Affiche toutes les formes de collisions --> afin de tester collisions
			for (int i = 0; i < pisteCourse.getNbCollisions(); i++)
			{
				window.draw(pisteCourse.getCollisions(i));
			}

			//Affiche la lumière au départ
			lights.changerLumiere(tempsJeu);

			if (temps.asSeconds() <= 6)
			{
				window.draw(lights.getSprite());
			}

			//Affichage de tous les joueurs
			for (int i = 0; i < nbJoueurs; i++)
			{
				window.draw(sprJoueur[i]);
			}

			//Rfraîchi l'affichage
			window.display();
		}

	}
	return 0;
}


bool afficherMenu(RenderWindow& window, Font font)
{
	//TEXTURES ET SPRITES
	Texture textureMenu;
	Sprite spriteMenu;

	Text txtJouer;

	textureMenu.loadFromFile("titleScreen.png");
	spriteMenu.setTexture(textureMenu);

	txtJouer.setFont(font);
	txtJouer.setString("Appuyez sur espace pour jouer");

	window.draw(spriteMenu);
	window.draw(txtJouer);
	window.display();

	while (1)
	{
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			return true;
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			return false;
		}
	}
}