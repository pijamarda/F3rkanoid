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
		//baja de la bola entra en contacto con la parte superior de la nave y rebotamos
		if (mBola.bottom() >= mNave.top())
		{			
			
			mBola.anguloBola = 360 - mBola.anguloBola;	
			
		}	
		//TODO: Ajustar la zona de rebote, sobre todo cuando golpea lateralmente la NAVE
		//ahora mismo tiene un comportamiento herratico	
	}
};

int main()
{

	//Con el modo debug activado, vemos lo siguiente:
	// Los bordes de colision de los elementos, nave, bola
	// el net_graph indicando FPS, angulo de la bola normalizado y offset de desplazamiento
	const bool DEBUG_ACTIVADO = true;

	//Tamaño de la ventana
	const unsigned int MAX_WIDTH = 600;
	const unsigned int MAX_HEIGHT = 480;

	//Tamaño de la pared
	const unsigned int PARED_WIDTH = 20;
	const unsigned int PARED_HEIGHT = 20;

	//Tamaño real del nivel donde se desarrollara todo el juego
	const unsigned int LVL_WIDTH = MAX_WIDTH - PARED_WIDTH;
	const unsigned int LVL_HEIGHT = MAX_HEIGHT - PARED_HEIGHT;

	//Velocidades iniciales de la nave y la bola
	const float VELOCIDAD_NAVE_INICIAL = 200;
	const double VELOCIDAD_BOLA_INICIAL = 600;

	//Angulo inicial hacia donde sale la bola
	const int ANGULO_INICIAL = 45;


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
	text_net_graph.setString("NET GRAPH");
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
		t_net_graph = "";
		t_net_graph += "fps: " + std::to_string(1.f/dt) + "\n";		
		t_net_graph += "angulo: " + std::to_string(bola.anguloBola % 360) + "\n";
		t_net_graph += std::to_string(bola.velocidadBola.x) + " , " + std::to_string(bola.velocidadBola.y) + "\n";
		
		text_net_graph.setString(t_net_graph);
		nave.actualizarPos(dt, localMouseCoords);
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