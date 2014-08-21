#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


class Bola
{
public:

	double ballVelocity;

	std::vector<float> ballVelocityVector;
	
	//Nos indicara el ancho y alto maximo del NIVEL que no de la ventana
	unsigned int MAX_WIDTH;
	unsigned int MAX_HEIGHT;
	sf::Vector2f direcBola;
	sf::Vector2f velocidadBola;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::FloatRect boundingBox;
	sf::RectangleShape rectBox;
	sf::VertexArray direcLine;
	unsigned int bolaAncho;
	unsigned int bolaAlto;
	int anguloBola;


	Bola(unsigned int lvl_width, unsigned int lvl_height, std::vector<float> vector_velocidades);

	//Constructor principal, al que le pasamos directamente el ancho y alto que tiene el nivel
	// y la velocidad de la bola
	Bola(unsigned int lvl_width, unsigned int lvl_height, double velocidad_inicial);

	void draw(sf::RenderWindow &window, bool debug);
	
	void actualizarPos(double dt, sf::Vector2i localMouseCoords);
	//Vamos a utilizar los grados a los que mira la bola para actualizar su posicion
	//esta actualizacion se va a basar en el angulo
	void actualizarPosAngulo(double dt);
	
	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();

};