#include "Bola.h"
#include <iostream>
#include <cmath>

Bola::Bola(unsigned int lvl_width, unsigned int lvl_height, double velocidad_inicial)
{

	//Angulo inicial de la bola
	anguloBola = 60;

	//inicializamos el vector que guarda las velocidades de las bolas
	//no se puede utiilizar el metodo c++11 vector<int> vi = {1,2,3,4}

	ballVelocity = velocidad_inicial;//vector_velocidades[0];

	//velocidadBola = sf::Vector2f(ballVelocity, ballVelocity);
	
	MAX_WIDTH = lvl_width;
	MAX_HEIGHT = lvl_height;
	if (!texture.loadFromFile("img/png/ballBlue.png"))
	{
		// error...
	}
	sprite.setTexture(texture);
	bolaAncho = sprite.getTextureRect().width;
	bolaAlto = sprite.getTextureRect().height;
	sprite.setPosition(sf::Vector2f(MAX_WIDTH / 2 - bolaAncho / 2, MAX_HEIGHT / 2));

	direcBola = sf::Vector2f(0.0f, 0.0f);
	//velocidadBola = sf::Vector2f(ballVelocity, ballVelocity);
	anguloBola = sprite.getRotation();

	boundingBox = sprite.getGlobalBounds();

	rectBox.setSize(sf::Vector2f(boundingBox.width, boundingBox.height));
	rectBox.setOutlineThickness(-2);
	rectBox.setOutlineColor(sf::Color::Red);
	rectBox.setFillColor(sf::Color::Transparent);

	direcLine = sf::VertexArray(sf::Lines, 2);

	direcLine[0].position = sf::Vector2f(boundingBox.left + boundingBox.width / 2, boundingBox.top + boundingBox.height / 2);
	direcLine[0].color = sf::Color::Red;
	direcLine[1].position = sf::Vector2f(20, 70);
	direcLine[1].color = sf::Color::Red;

}

void Bola::draw(sf::RenderWindow &window, bool debug)
{
	window.draw(sprite);
	if (debug)
	{
		window.draw(rectBox);
		window.draw(direcLine);
	}
}

void Bola::actualizarPos(double dt, sf::Vector2i localMouseCoords)
{
	sf::Vector2f position = sprite.getPosition();
	
	if (position.x <= 0)
		velocidadBola.x = ballVelocity;
	if (position.x >= MAX_WIDTH)
		velocidadBola.x = -ballVelocity;
	if (position.y <= 0)
		velocidadBola.y = ballVelocity;
	//Esto indica que la bola se ha caido por abajo y la volvemos a colocar en el centro
	if (position.y >= MAX_HEIGHT)
	{
		velocidadBola.y = -ballVelocity;
		sprite.setPosition(sf::Vector2f(MAX_WIDTH / 2 - bolaAncho / 2, MAX_HEIGHT / 2));
	}
	
	velocidadBola.x = velocidadBola.x * dt;
	velocidadBola.y = velocidadBola.y * dt;

	sprite.move(velocidadBola);

	//direcLine.clear();
	direcLine[0].position = sf::Vector2f(boundingBox.left + boundingBox.width / 2, boundingBox.top + boundingBox.height / 2);
	direcLine[0].color = sf::Color::Red;
	direcLine[1].position = sf::Vector2f(localMouseCoords.x, localMouseCoords.y);
	direcLine[1].color = sf::Color::Red;

	boundingBox = sprite.getGlobalBounds();

	rectBox.setPosition(sf::Vector2f(boundingBox.left, boundingBox.top));
}
void Bola::actualizarPosAngulo(double dt)
{
	sf::Vector2f position = sprite.getPosition();	
	
	if (position.x <= 0)
		anguloBola = - (anguloBola - 180);
	if (position.x >= MAX_WIDTH)
		anguloBola = 180 - anguloBola;
	if (position.y <= 0)
		anguloBola = - anguloBola;
	//Esto indica que la bola se ha caido por abajo y la volvemos a colocar en el centro
	if (position.y >= MAX_HEIGHT)
	{
		anguloBola = 45;
		sprite.setPosition(sf::Vector2f(MAX_WIDTH / 2 - bolaAncho / 2, MAX_HEIGHT / 2));
	}
	

	//Aqui debemos introducir el calculo del seno y coseno
	//convertimos nuestro angulo de grados a radianes que es como trabaja c++
	double anguloBolaRadianes = anguloBola * 3.141592653589793 / 180.0;
	//Ahora calculamos cuanto se ha desplazado en el eje de las X utilizando el Coseno
	velocidadBola.x = ballVelocity * std::cos(anguloBolaRadianes) * dt;
	//Ahora calculamos cuanto se ha desplazado en el eje de las Y utilizando el Seno
	velocidadBola.y = ballVelocity * std::sin(anguloBolaRadianes) * dt;

	sprite.move(velocidadBola);

	//direcLine.clear();
	direcLine[0].position = sf::Vector2f(boundingBox.left + boundingBox.width / 2, 
										 boundingBox.top + boundingBox.height / 2);
	direcLine[0].color = sf::Color::Red;
	direcLine[1].position = sf::Vector2f(std::cos(anguloBolaRadianes) + boundingBox.left + boundingBox.width / 2, 
							std::sin(anguloBolaRadianes) + boundingBox.top + boundingBox.height / 2);
	direcLine[1].color = sf::Color::Red;

	boundingBox = sprite.getGlobalBounds();

	rectBox.setPosition(sf::Vector2f(boundingBox.left, boundingBox.top));

}

float Bola::x() { return sprite.getPosition().x; }
float Bola::y() { return sprite.getPosition().y; }
float Bola::left() { return sprite.getGlobalBounds().left; }
float Bola::right() { return sprite.getGlobalBounds().left + sprite.getGlobalBounds().width; }
float Bola::top() { return sprite.getGlobalBounds().top; }
float Bola::bottom() { return sprite.getGlobalBounds().top + sprite.getGlobalBounds().height; }

//DEBUG: Ojo que este no funciona
/*
Bola::Bola(unsigned int lvl_width, unsigned int lvl_height, std::vector<float> vector_velocidades)
{
	//inicializamos el vector que guarda las velocidades de las bolas
	//no se puede utiilizar el metodo c++11 vector<int> vi = {1,2,3,4}

	ballVelocity = 0.1f;//vector_velocidades[0];

	for (auto v_vel : vector_velocidades)
		ballVelocityVector.push_back(v_vel);
	
	MAX_WIDTH = lvl_width;
	MAX_HEIGHT = lvl_height;
	if (!texture.loadFromFile("img/png/ballBlue.png"))
	{
		std::cout << "error al cargar la textura" << std::endl;
	}
	sprite.setTexture(texture);
	bolaAncho = sprite.getTextureRect().width;
	bolaAlto = sprite.getTextureRect().height;
	sprite.setPosition(sf::Vector2f(MAX_WIDTH / 2 - bolaAncho / 2, MAX_HEIGHT / 2));
	
	direcBola = sf::Vector2f(0.0f, 0.0f);
	velocidadBola = sf::Vector2f(ballVelocity, ballVelocity);
	anguloBola = sprite.getRotation();

	boundingBox = sprite.getGlobalBounds();

	rectBox.setSize(sf::Vector2f(boundingBox.width, boundingBox.height));
	rectBox.setOutlineThickness(-2);
	rectBox.setOutlineColor(sf::Color::Red);
	rectBox.setFillColor(sf::Color::Transparent);

	direcLine = sf::VertexArray(sf::Lines, 2);

	direcLine[0].position = sf::Vector2f(boundingBox.left + boundingBox.width / 2, boundingBox.top + boundingBox.height / 2);
	direcLine[0].color = sf::Color::Red;
	direcLine[1].position = sf::Vector2f(20, 70);
	direcLine[1].color = sf::Color::Red;

}
*/

