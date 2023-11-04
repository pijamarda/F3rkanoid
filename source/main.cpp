#include <iostream>

#include "utils.h"


int main()
{

	//Con el modo debug activado, vemos lo siguiente:
	// Los bordes de colision de los elementos, nave, bola
	// el net_graph indicando FPS, angulo de la bola normalizado y offset de desplazamiento
	const bool DEBUG_ACTIVADO = false;

	//Tamaño de la ventana
	const unsigned int MAX_WIDTH = 600;
	const unsigned int MAX_HEIGHT = 480;

	//Tamaño de la pared
	const unsigned int PARED_WIDTH = 20;
	const unsigned int PARED_HEIGHT = 20;

	//Tamaño real del nivel donde se desarrollara todo el juego
	const unsigned int LVL_WIDTH = MAX_WIDTH - PARED_WIDTH*2;
	const unsigned int LVL_HEIGHT = MAX_HEIGHT - PARED_HEIGHT;

	//Velocidades iniciales de la nave y la bola
	const float VELOCIDAD_NAVE_INICIAL = 200;
	const double VELOCIDAD_BOLA_INICIAL = 400;

	//Angulo inicial hacia donde sale la bola
	const float ANGULO_INICIAL = 45;


	sf::Font font;
	sf::Text text_net_graph;
	sf::Text text_pause;
	std::string t_net_graph;
	sf::Vector2i localMouseCoords;
	sf::Clock clock;
	float dt;
	bool pausa = true;
	bool musica = true;
	bool sonido = true;

	sf::RenderWindow window(sf::VideoMode(MAX_WIDTH, MAX_HEIGHT), "F3RKANOID");
	Nave nave = Nave(LVL_WIDTH, LVL_HEIGHT, VELOCIDAD_NAVE_INICIAL);	
	Bola bola = Bola(LVL_WIDTH, LVL_HEIGHT, VELOCIDAD_BOLA_INICIAL, ANGULO_INICIAL);
	Brick ladrillos = Brick(1, LVL_WIDTH, LVL_HEIGHT, PARED_WIDTH);

	if (!font.loadFromFile("data/fonts/sansation.ttf"))
	{
		std::cout << "error al cargar la fuente" << std::endl;
	}
	
	text_net_graph.setFont(font);
	text_net_graph.setString("NET GRAPH");
	text_net_graph.setCharacterSize(18); // in pixels, not points!
	text_net_graph.setFillColor(sf::Color::White);
	text_net_graph.setStyle(sf::Text::Bold);

	text_pause.setFont(font);	
	text_pause.setPosition(100, 250);
	text_pause.setCharacterSize(18); // in pixels, not points!
	text_pause.setFillColor (sf::Color::White);
	text_pause.setStyle(sf::Text::Bold);
	std::string texto_temp_pausa = "PAUSA \n";
	texto_temp_pausa += "Pulsa P para empezar o para mostrar este menu \n\n";
	texto_temp_pausa += "Pulsa M para apagar/encender musica \n";
	texto_temp_pausa += "Pulsa S para apagar/encender sonido";
	text_pause.setString(texto_temp_pausa);
	
	//window.setFramerateLimit(60);

	sf::RectangleShape bordeIzquierdo(sf::Vector2f(PARED_WIDTH, MAX_HEIGHT));
	bordeIzquierdo.setFillColor(sf::Color::Blue);

	sf::RectangleShape bordeDerecho(sf::Vector2f(PARED_WIDTH, MAX_HEIGHT));
	bordeDerecho.setPosition(sf::Vector2f(MAX_WIDTH - PARED_WIDTH, 0));
	bordeDerecho.setFillColor(sf::Color::Blue);

	sf::RectangleShape bordeTop(sf::Vector2f(MAX_WIDTH, PARED_HEIGHT));
	//bordeDerecho.setPosition(sf::Vector2f(MAX_WIDTH - PARED_WIDTH, 0));
	bordeTop.setFillColor(sf::Color::Red);

	//musica
	sf::Music music;
	if (!music.openFromFile("data/sound/music1.ogg"))
	{ 
		std::cout << "error al cargar la musica" << std::endl;		
	}
	music.setVolume(30);
	music.play();
	//music.pause();
		
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Q)
				{
					bola.resetPosition();
				}
				else if (event.key.code == (sf::Keyboard::Left))
				{
					// left key is pressed: move our character
					if (nave.dNave == direccion::parado)
						nave.dNave = direccion::izquierda;
					else if (nave.dNave == direccion::derecha)
						nave.dNave = direccion::parado;
				}
				else if (event.key.code == (sf::Keyboard::Right))
				{
					if (nave.dNave == direccion::parado)
						nave.dNave = direccion::derecha;
					else if (nave.dNave == direccion::izquierda)
						nave.dNave = direccion::parado;
				}
				else if (event.key.code == (sf::Keyboard::Z))
				{
					bola.ballVelocity -= 15;
				}
				else if (event.key.code == (sf::Keyboard::A))
				{
					bola.ballVelocity += 15;
				}
				else if (event.key.code == (sf::Keyboard::P))
				{
					pausa = !pausa;
				}
				else if (event.key.code == (sf::Keyboard::M))
				{
					if (musica)
						music.play();
					else
						music.pause();
					musica = !musica;
				}
				else if (event.key.code == (sf::Keyboard::S))
				{
					sonido = !sonido;
				}

			}
			
			localMouseCoords = sf::Mouse::getPosition(window);
		}

		//actualizamos direccion nave
		
		dt = clock.restart().asSeconds();
		t_net_graph = "";
		t_net_graph += "fps: " + std::to_string((int)(1.f/dt)) + "\n";		
		t_net_graph += "angulo: " + std::to_string((int)bola.anguloBola) + "\n";
		t_net_graph += std::to_string((int)bola.x()) + " , " + std::to_string((int)bola.y()) + "\n";
		
		text_net_graph.setString(t_net_graph);

		//A ver que tal funciona, si le damos a la "P" se deberia pausar la actualizacion de las posiciones
		// de la nave y la bola

		if (!pausa)
		{
			nave.actualizarPos(dt, localMouseCoords);
			bola.actualizarPos(dt);
			if (testCollision(bola, nave))
			{
				if (sonido)
					bola.playSoundPaddle();
			}
			if (bolaBrickCollision(bola, ladrillos))
			{
				if (sonido)
					bola.playSoundBrick();
				//std::cout << ladrillos.ladrillos_restantes << std::endl;
				
			}
			if (ladrillos.ladrillos_restantes <= 0)
				pausa = true;
		}
		else //Mostramos el Menu
		{
			
		}
		//
		window.clear();
		window.draw(bordeIzquierdo);
		window.draw(bordeDerecho);
		window.draw(bordeTop);
		nave.draw(window, DEBUG_ACTIVADO);
		ladrillos.draw(window);
		bola.draw(window, DEBUG_ACTIVADO);		
		if (DEBUG_ACTIVADO)
			window.draw(text_net_graph);
		if (pausa)
			window.draw(text_pause);
		window.display();
	}

	return 0;
}