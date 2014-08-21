#include <iostream>

#include "Brick.h"
#include "Nave.h"
#include "Bola.h"


void testCollision(Bola &mBola, Nave &mNave)
{

	if (mBola.right() >= mNave.left() && mBola.right() <= mNave.right())
	{
		if (mBola.left() >= mNave.left() && mBola.left() <= mNave.right())
		{
			if (mBola.bottom() >= mNave.top() && mBola.bottom() <= mNave.bottom())
			{
				//std::cout << "hay colision total" << std::endl;
				//mBola.rebote = true;
				mBola.anguloBola = 360 - mBola.anguloBola;
				//DEBUG: Vamos a probar que al golpear la bola contra la nave
				//la inclinacion respecto al suelo disminuye
				//mBola.velocidadBola.x = mBola.ballVelocityVector[1];
			}
		}
	}
};

int main()
{

	const bool DEBUG_ACTIVADO = true;

	const unsigned int MAX_WIDTH = 600;
	const unsigned int MAX_HEIGHT = 480;

	const unsigned int PARED_WIDTH = 20;
	const unsigned int PARED_HEIGHT = 20;

	const unsigned int LVL_WIDTH = MAX_WIDTH - PARED_WIDTH;
	const unsigned int LVL_HEIGHT = MAX_HEIGHT - PARED_HEIGHT;

	const float VELOCIDAD_NAVE_INICIAL = 100;
	const double VELOCIDAD_BOLA_INICIAL = 100;

	//definimos las distintas velocidades que puede adquirir la bola
	const float VEL1 = VELOCIDAD_NAVE_INICIAL,
				VEL2 = 0.5f;

	sf::Font font;
	if (!font.loadFromFile("fonts/sansation.ttf"));
	{
		std::cout << "error al cargar la fuente" << std::endl;
	}
	sf::Text text_fps;
	text_fps.setFont(font);
	text_fps.setString("2000");
	text_fps.setCharacterSize(24); // in pixels, not points!
	text_fps.setColor(sf::Color::White);
	text_fps.setStyle(sf::Text::Bold);

	sf::Text text_bola;
	text_bola.setFont(font);
	text_bola.setString("2000");
	text_bola.setCharacterSize(24); // in pixels, not points!
	text_bola.setColor(sf::Color::White);
	text_bola.setStyle(sf::Text::Bold);
	text_bola.setPosition(sf::Vector2f(40, 40));
	

	std::vector<float> vector_velocidades;
	vector_velocidades.push_back(VEL1);
	vector_velocidades.push_back(VEL2);

	sf::RenderWindow window(sf::VideoMode(MAX_WIDTH, MAX_HEIGHT), "F3RKANOID");
	window.setFramerateLimit(60);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	sf::Vector2i localMouseCoords;

	Nave nave = Nave(LVL_WIDTH, LVL_HEIGHT, VELOCIDAD_NAVE_INICIAL);
	//DEBUG: Cuando uso el constructor de los vectores no me inicializa bien los graficos
	//revisar
	//Bola bola = Bola(LVL_WIDTH, LVL_HEIGHT, vector_velocidades);
	Bola bola = Bola(LVL_WIDTH, LVL_HEIGHT, VELOCIDAD_BOLA_INICIAL);
	Brick ladrillos = Brick(1, LVL_WIDTH, LVL_HEIGHT);

	sf::Clock clock;
	//clock.restart().asSeconds();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				// left key is pressed: move our character
				if (nave.dNave == direccion::parado)
					nave.dNave = direccion::izquierda;
				else if (nave.dNave == direccion::derecha)
					nave.dNave = direccion::parado;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (nave.dNave == direccion::parado)
					nave.dNave = direccion::derecha;
				else if (nave.dNave == direccion::izquierda)
					nave.dNave = direccion::parado;
			}
			localMouseCoords = sf::Mouse::getPosition(window);
		}

		//actualizamos direccion nave
		
		float dt = clock.restart().asSeconds();
		text_fps.setString(std::to_string(1.f/dt));
		text_bola.setString("Hola");
		text_bola.setString(std::to_string(bola.ballVelocity) + " s " 
							+ std::to_string(bola.velocidadBola.x)
							+ " " + std::to_string(bola.velocidadBola.y));
		nave.actualizarPos(dt);
		//DEBUG: Vamos a intentar utilizar la version que actualiza la posicion de la bola
		//basada en el angulo
		//bola.actualizarPos(dt,localMouseCoords);
		bola.actualizarPosAngulo(dt);
		testCollision(bola, nave);
		//
		window.clear();
		//window.draw(shape);
		nave.draw(window, DEBUG_ACTIVADO);
		//ladrillos.draw(window);
		bola.draw(window, DEBUG_ACTIVADO);
		window.draw(text_fps);
		window.draw(text_bola);
		window.display();
	}

	return 0;
}