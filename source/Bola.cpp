#include "Bola.h"
#include <iostream>
#include <cmath>

Bola::Bola(unsigned int lvl_width, unsigned int lvl_height, double velocidad_inicial, float angulo_inicial)
{

	//Angulo inicial de la bola
	ANGULO_INICIAL = angulo_inicial;
	anguloBola = angulo_inicial;

	
	ballVelocity = velocidad_inicial;
	
	MAX_WIDTH = lvl_width;
	MAX_HEIGHT = lvl_height;
	if (!texture.loadFromFile("data/img/png/ballBlue.png"))
	{
		// error... prueba para el git sobre el error
	}
	sprite.setTexture(texture);
	bolaAncho = sprite.getTextureRect().width;
	bolaAlto = sprite.getTextureRect().height;
	sprite.setPosition(sf::Vector2f(MAX_WIDTH / 2 - bolaAncho / 2, MAX_HEIGHT / 2));
	
	boundingBox = sprite.getGlobalBounds();

	rectBox.setSize(sf::Vector2f(boundingBox.width, boundingBox.height));
	rectBox.setOutlineThickness(-2);
	rectBox.setOutlineColor(sf::Color::Red);
	rectBox.setFillColor(sf::Color::Transparent);

	direcLine = sf::VertexArray(sf::Lines, 2);

	direcLine[0].position = sf::Vector2f(boundingBox.left + boundingBox.width / 2, 
										 boundingBox.top + boundingBox.height / 2);
	direcLine[0].color = sf::Color::Red;
	direcLine[1].position = sf::Vector2f(20, 70);
	direcLine[1].color = sf::Color::Red;

	//Sonidos
	
	if (!bufferPaddle.loadFromFile("data/sound/paddle.wav"))
		std::cout << "error al cargar la fuente" << std::endl;
	
	soundPaddle.setBuffer(bufferPaddle);
	soundPaddle.setVolume(70);
	
	if (!bufferBrick.loadFromFile("data/sound/brick.wav"))
		std::cout << "error al cargar la fuente" << std::endl;

	soundBrick.setBuffer(bufferBrick);
	soundBrick.setVolume(70);
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

void Bola::actualizarPos(double dt)
{
	sf::Vector2f position = sprite.getPosition();	
	anguloBola = normalizaAngulo(anguloBola);
	if (position.x <= 0 + 20)
	{
		//Es decir, solo cambiamos el angulo de la bola si la bola va hacia la izquierda
		if (anguloBola > 90 && anguloBola <= 270)
			anguloBola = -(anguloBola - 180);
		anguloBola = normalizaAngulo(anguloBola);
		
	}
	else if (position.x >= MAX_WIDTH)
	{
		//Es decir, solo cambiamos el angulo de la bola si la bola va hacia la derecha
		if (anguloBola > 270 || anguloBola < 90)
			anguloBola = 180 - anguloBola;
		anguloBola = normalizaAngulo(anguloBola);
		
	}
	else if (position.y <= 0 + 20)
	{
		//Es decir, solo cambiamos el angulo de la bola si la bola va hacia arriba
		if (anguloBola > 180)
			anguloBola = -anguloBola;
		anguloBola = normalizaAngulo(anguloBola);
		
	}
	//Esto indica que la bola se ha caido por abajo y la volvemos a colocar en el centro
	else if (position.y >= MAX_HEIGHT)
	{
		anguloBola = ANGULO_INICIAL;
		sprite.setPosition(sf::Vector2f(MAX_WIDTH / 2 - bolaAncho / 2, MAX_HEIGHT / 2));
		//Es decir, solo cambiamos el angulo de la bola si la bola va hacia abajo
		/*
		if (anguloBola < 180)
			anguloBola = - anguloBola;
			*/
		anguloBola = normalizaAngulo(anguloBola);		
	}
	

	//Aqui debemos introducir el calculo del seno y coseno
	//convertimos nuestro angulo de grados a radianes que es como trabaja c++
	double anguloBolaRadianes = anguloBola * 3.141592653589793 / 180.0;
	//Ahora calculamos cuanto se ha desplazado en el eje de las X utilizando el Coseno
	velocidadBola.x = ballVelocity * std::cos(anguloBolaRadianes) * dt;
	//Ahora calculamos cuanto se ha desplazado en el eje de las Y utilizando el Seno
	velocidadBola.y = ballVelocity * std::sin(anguloBolaRadianes) * dt;

	if ( this->left() + velocidadBola.x >= 0 || 
		this->right() + velocidadBola.x <= MAX_WIDTH ||
		this->top() + velocidadBola.y >= 0 ||
		this->bottom() +velocidadBola.y <= MAX_HEIGHT)
	{
		sprite.move(velocidadBola);
	}

	//direcLine.clear();
	direcLine[0].position = sf::Vector2f(boundingBox.left + boundingBox.width / 2, 
										 boundingBox.top + boundingBox.height / 2);
	direcLine[0].color = sf::Color::Red;
	direcLine[1].position = sf::Vector2f(boundingBox.left + boundingBox.width / 2 + 
										 std::cos(anguloBolaRadianes) * 50, 
										 boundingBox.top + boundingBox.height / 2 + 
										 std::sin(anguloBolaRadianes) * 50);
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

float Bola::normalizaAngulo(float angulo)
{
	float angTemp = angulo;
	if (angulo > 360)
		angTemp = std::fmod(angulo,360);
	if (angTemp < 0)
		angTemp = angTemp + 360;

	return angTemp;
}

void Bola::resetPosition()
{
	sprite.setPosition(sf::Vector2f(MAX_WIDTH / 2 - bolaAncho / 2, MAX_HEIGHT / 2));	
	anguloBola = ANGULO_INICIAL;
}

void Bola::playSoundPaddle()
{
	
	soundPaddle.play();
}

void Bola::playSoundBrick()
{

	soundBrick.play();
}