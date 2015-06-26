#pragma once
#include <vector>
#include <iostream>
#include <random>

#include <cstdlib> 
#include <ctime>

#include <SFML/Graphics.hpp>

/*
* Esta clase define el bloque completo de ladrillos
*
*
*
*/

class Brick
{
public:
	//Ancho y Alto designan el numereo de ladrillos que hay y su distribucion
	const unsigned int ANCHO = 1;
	const unsigned int ALTO = 1;
	//NUM_COLORES es el numero de ladrillos distintos que tenemos, ahora mismo
	//utilizamos 6 imagenes distintas
	const unsigned int NUM_COLORES = 6;

	unsigned int MAX_WIDTH;
	unsigned int MAX_HEIGHT;
	unsigned int BORDE_WIDTH;

	unsigned int num_ladrillos;
	int ladrillos_restantes;

	//Cada ladrillo esta formado por un sprite y las funciones necesarias
	struct Ladrillo
	{
		sf::Sprite sprite;		

		float x() { return sprite.getPosition().x; }
		float y() { return sprite.getPosition().y; }
		float left() { return sprite.getGlobalBounds().left; }
		float right() { return sprite.getGlobalBounds().left + sprite.getGlobalBounds().width; }
		float top() { return sprite.getGlobalBounds().top; }
		float bottom() { return sprite.getGlobalBounds().top + sprite.getGlobalBounds().height; }
	};

	//Guardamos todos los ladrillos en un vector
	std::vector<Ladrillo> ladrillos;
	//Para que sea sencillo su seleccion aleatoria guardamos las texturas
	//en un vector
	std::vector<sf::Texture> tipoLadrillos;

	// Para el constructor facilitamos el ancho y alto del nivel LVL_WIDTH y LVL_HEIGHT
	// el ancho y alto del nivel tienen en cuenta los bordes del propio nivel, es decir
	// que no es el ancho total de la ventana, ademas le pasamos el ancho de la pared para
	//calcular donde colocar los ladrillos dejando el espacio adecuado
	Brick(int nivel, unsigned int LVL_WIDTH, unsigned int LVL_HEIGHT, unsigned int PARED_WIDTH);

	void draw(sf::RenderWindow &window);

};