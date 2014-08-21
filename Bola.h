#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


class Bola
{
public:

	double ballVelocity;

	std::vector<float> ballVelocityVector;
	
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
	float anguloBola;



	Bola(unsigned int lvl_width, unsigned int lvl_height, std::vector<float> vector_velocidades);
	Bola(unsigned int lvl_width, unsigned int lvl_height, double velocidad_inicial);

	void draw(sf::RenderWindow &window, bool debug);
	
	void actualizarPos(double dt, sf::Vector2i localMouseCoords);
	
	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();

};