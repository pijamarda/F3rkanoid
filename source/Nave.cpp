#include "Nave.h"


Nave::Nave(unsigned int lvl_width, unsigned int lvl_height, float velocidad_nave_ini)
{
	velocidadNave = velocidad_nave_ini;
	//Guardamos en las variables MAX, los limites del nivel
	MAX_WIDTH = lvl_width;
	MAX_HEIGHT = lvl_height;
	if (!texture.loadFromFile("img/png/paddleBlu.png"))
	{
		std::cout << "Ha habido un error en la carga de la textura de la Nave" << std::endl;
	}

	dNave = direccion::parado;

	sprite.setTexture(texture);
	naveAncho = sprite.getTextureRect().width;
	naveAlto = sprite.getTextureRect().height;

	//La posicion inicial de la nave es en la mitad del ancho de la pantalla
	//y en la parte de abajo del nivel
	sprite.setPosition(sf::Vector2f(MAX_WIDTH / 2 - naveAncho / 2, MAX_HEIGHT - naveAlto));

	/*
	DEBUG: Pintamos los limites del sprite de la nave con un rectangulo visible
	*/
	boundingBox = sprite.getGlobalBounds();
	rectBox.setSize(sf::Vector2f(boundingBox.width, boundingBox.height));
	rectBox.setOutlineThickness(-2);
	rectBox.setOutlineColor(sf::Color::Blue);
	rectBox.setFillColor(sf::Color::Transparent);
}

void Nave::draw(sf::RenderWindow &window, bool debug)
{
	window.draw(sprite);
	if (debug)
		window.draw(rectBox);
}

void Nave::actualizarPos(double dt, sf::Vector2i mouseCoords)
{
	sf::Vector2f position = sprite.getPosition();

	if (dNave == direccion::derecha && position.x < MAX_WIDTH - naveAncho)
	{
		sprite.move(velocidadNave*dt, 0);
	}
	else if (dNave == direccion::izquierda && position.x > 0)
	{
		sprite.move(-velocidadNave*dt, 0);
	}
	else dNave = direccion::parado;

	//Vamos a utilizar las coordenadas del raton para mover la nave
	// se ha hecho deprisa y corriendo quizas haya algun fallo extra
	float coordenadaX = mouseCoords.x;
	if (coordenadaX > MAX_WIDTH - naveAncho)
		coordenadaX = MAX_WIDTH - naveAncho;
	sprite.setPosition(sf::Vector2f(coordenadaX,this->y()));

	boundingBox = sprite.getGlobalBounds();
	rectBox.setPosition(sf::Vector2f(boundingBox.left, boundingBox.top));
}


float Nave::x() { return sprite.getPosition().x; }
float Nave::y() { return sprite.getPosition().y; }
float Nave::left() { return sprite.getGlobalBounds().left; }
float Nave::right() { return sprite.getGlobalBounds().left + sprite.getGlobalBounds().width; }
float Nave::top() { return sprite.getGlobalBounds().top; }
float Nave::bottom() { return sprite.getGlobalBounds().top + sprite.getGlobalBounds().height; }
