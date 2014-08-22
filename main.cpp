#include <iostream>

#include "Brick.h"
#include "Nave.h"
#include "Bola.h"


void testCollision(Bola &mBola, Nave &mNave)
{
	//El primer && del if comprueba si la parte derecha de la bola esta dentro de la nave
	//El segundo && comprueba si la parte izquierda de la bola esta dentro de la nave
	if ( (mBola.right() >= mNave.left() && mBola.right() <= mNave.right()) || 
		 (mBola.left() >= mNave.left() && mBola.left() <= mNave.right()) )
	{
		//En cualquiera de los 2 casos anteriormente indicados comprobamos que la parte 
		//baja de la bola entra en contacto con la parte superior de la nave
		if (mBola.bottom() >= mNave.top())
		{			
			mBola.anguloBola = 360 - mBola.anguloBola;			
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

	const float VELOCIDAD_NAVE_INICIAL = 200;
	const double VELOCIDAD_BOLA_INICIAL = 300;
	const int ANGULO_INICIAL = 60;

	sf::Font font;
	sf::Text text_net_graph;
	std::string t_net_graph;
	sf::Vector2i localMouseCoords;
	sf::Clock clock;
	float dt;
	
	sf::RenderWindow window(sf::VideoMode(MAX_WIDTH, MAX_HEIGHT), "F3RKANOID");
	Nave nave = Nave(LVL_WIDTH, LVL_HEIGHT, VELOCIDAD_NAVE_INICIAL);	
	Bola bola = Bola(LVL_WIDTH, LVL_HEIGHT, VELOCIDAD_BOLA_INICIAL, ANGULO_INICIAL);
	Brick ladrillos = Brick(1, LVL_WIDTH, LVL_HEIGHT);

	if (!font.loadFromFile("fonts/sansation.ttf"))
	{
		std::cout << "error al cargar la fuente" << std::endl;
	}
	
	text_net_graph.setFont(font);
	text_net_graph.setString("2000");
	text_net_graph.setCharacterSize(18); // in pixels, not points!
	text_net_graph.setColor(sf::Color::White);
	text_net_graph.setStyle(sf::Text::Bold);	
	
	//window.setFramerateLimit(60);
		
	
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
		
		dt = clock.restart().asSeconds();
		
		t_net_graph += std::to_string(1.f/dt) + "\n";
		//text_fps.setString(std::to_string(1.f/dt));
		t_net_graph += std::to_string(bola.ballVelocity) + "\n";
		t_net_graph += std::to_string(bola.velocidadBola.x) + " , " + std::to_string(bola.velocidadBola.y) + "\n";
		/*text_bola.setString(std::to_string(bola.ballVelocity) + " s \n" 
							+ std::to_string(bola.velocidadBola.x)
							+ " , " + std::to_string(bola.velocidadBola.y));
		*/
		nave.actualizarPos(dt);
		bola.actualizarPos(dt);
		testCollision(bola, nave);
		//
		window.clear();
		
		nave.draw(window, DEBUG_ACTIVADO);
		//ladrillos.draw(window);
		bola.draw(window, DEBUG_ACTIVADO);		
		window.draw(text_net_graph);
		window.display();
	}

	return 0;
}