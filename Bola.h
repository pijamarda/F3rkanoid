#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


class Bola
{
public:

	double ballVelocity;	
	
	//Nos indicara el ancho y alto maximo del NIVEL que no de la ventana
	unsigned int MAX_WIDTH;
	unsigned int MAX_HEIGHT;	
	sf::Vector2f velocidadBola;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::FloatRect boundingBox;
	sf::RectangleShape rectBox;
	sf::VertexArray direcLine;
	unsigned int bolaAncho;
	unsigned int bolaAlto;
	float anguloBola;
	float ANGULO_INICIAL;


	//Constructor principal, al que le pasamos directamente el ancho y alto que tiene el nivel
	// y la velocidad de la bola
	Bola(unsigned int lvl_width, unsigned int lvl_height, double velocidad_inicial, float angulo_inicial);

	void draw(sf::RenderWindow &window, bool debug);	
	
	//Vamos a utilizar los grados a los que mira la bola para actualizar su posicion
	//esta actualizacion se va a basar en el angulo
	void actualizarPos(double dt);
	void resetPosition();
	
	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();

	//Esta funcion pretende convertir cualquier angulo, obtenido de las operaciones de rebote de la bola,
	//en un angulo normalizado, es decir que el angulo no sea negativo ni mayor de 360
	// --> 0 < angulo < 360  <--
	float normalizaAngulo(float angulo);

};