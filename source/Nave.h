#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

//Definimos cuales son las 3 direcciones de la nave

enum direccion { izquierda, derecha, parado };

//Definimos cuales son los posibles estados de la nave
enum estado { normal, pegamento, disparo };

class Nave
{
public:
	

	float velocidadNave;
	unsigned int MAX_WIDTH;
	unsigned int MAX_HEIGHT;
	direccion dNave;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::FloatRect boundingBox;
	sf::RectangleShape rectBox;
	unsigned int naveAncho;
	unsigned int naveAlto;
	//Aqui guardaremos las coordenadas locales del raton
	sf::Vector2i mouseCoords;

	Nave(unsigned int lvl_width, unsigned int lvl_height, float velocidad_nave_ini);



	void draw(sf::RenderWindow &window, bool debug);
	void actualizarPos(double dt, sf::Vector2i mouseCoords);

	/*
	* Funciones auxiliares para obtener los datos del sprite de "Nave"
	*/

	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();
};

