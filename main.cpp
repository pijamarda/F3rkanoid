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

			
			/*
			*	Vamos a intentar que el angulo de salida de rebote dependa de en que parte de la nave 
			*	colisiona.
			*	
			*/
			//Primero calculamos la coordenada del centro de la bola
			float centroBolaX = (mBola.right() + mBola.left()) / 2;
			//Calculamos la coordenada actual del centro de la nave
			float centroNaveX = (mNave.right() + mNave.left()) / 2;
			//Ahora vamos a hacer la comparacion de donde rebota la bola respecto a la nave
			// Dividimos la nave en varias zonas de choque, en principio 5
			int numeroZonas = 5;
			float tamZonaChoque = (mNave.right() - mNave.left()) / numeroZonas;
			//Estas zonas nos daran un rango de x para comparar
			//por ahora solo voy a sacar por consola la zona de la nave donde choca
			/*
			if (centroBolaX < mNave.left() + tamZonaChoque)
				std::cout << "Zona 1" << std::endl;
			else if (centroBolaX < mNave.left() + tamZonaChoque*2)
				std::cout << "Zona 2" << std::endl;
			else if (centroBolaX < mNave.left() + tamZonaChoque*3)
				std::cout << "Zona 3" << std::endl;
			else if (centroBolaX < mNave.left() + tamZonaChoque*4)
				std::cout << "Zona 4" << std::endl;
			else if (centroBolaX < mNave.left() + tamZonaChoque*5)
				std::cout << "Zona 5" << std::endl;
			*/

			//Formula el calculo del angulo de salida del rebote segun donde impacte
			/*
			*	PRIMERA APROXIMACION SI LA BOLA VIENE CON UN ANGULO > 0 Y <90 (de izquierda a derecha)
			*	La idea es la siguiente, si rebota en el extremo izquierdo de la pala la bola debe
			*	volver por donde ha venido, esto es angulo de entrada + 180
			*	Si rebota en medio la bola sale con un angulo igual pero rebotando ANG + 180 + 90
			*	Si rebota en el extremo derecho sale rebotando ANG + 180 + 180
			*
			*	De manera que dividimos la anchura de la nave en 180 zonas de impacto, que son los angulos
			*	de salida que va a tomar la bola
			*/

			float anguloDeSalida = mBola.anguloBola;

			if (mBola.anguloBola > 0 && mBola.anguloBola <= 180)
			{
				float diferencial = 180.0f / mNave.naveAncho;
				//en nuestro caso particular da alrededor de 0'73
				float centroNaveX = (mNave.right() + mNave.left()) / 2;
				//ahora calculamos la diferencia de la bola en e nave respecto al centro
				//de la bola, es decir restamos el centro de la bola menos la coordenada x de la nave
				//eso nos da la zona de impacto entre 0 y la anchura
				float impactoBola = centroBolaX - centroNaveX;

				//el angulo de salida sera la zona de impacto sobre la nave por el diferencial calculado antes
				//y despues sumamos 180 porque corresponde a un rebote con direccion de izquierda a derecha

				if (anguloDeSalida >= 0 && anguloDeSalida <= 90)
					if (anguloDeSalida >= 30 || impactoBola < 0)
						anguloDeSalida = -anguloDeSalida + impactoBola*diferencial;
					else
						anguloDeSalida = -anguloDeSalida;
				if (anguloDeSalida > 90 && anguloDeSalida <= 180)
					if (anguloDeSalida <= 150 || impactoBola > 0)
						anguloDeSalida = -anguloDeSalida + impactoBola*diferencial;
					else
						anguloDeSalida = -anguloDeSalida;

				//DEBUG: Mostramos por consola
				std::cout << "entrada: " << mBola.anguloBola << std::endl;
				std::cout << "encho nave: " << mNave.naveAncho << " ";
				std::cout << "impactoBola: " << impactoBola << std::endl;
				std::cout << "salida: " << anguloDeSalida << std::endl;
				//std::cout << "salida norm: " << mBola.normalizaAngulo(anguloDeSalida) << std::endl;
			}			

			//mBola.anguloBola = anguloDeSalida;//360 - mBola.anguloBola;
			mBola.anguloBola = mBola.normalizaAngulo(anguloDeSalida);
				
			
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
	const double VELOCIDAD_BOLA_INICIAL = 400;

	//Angulo inicial hacia donde sale la bola
	const float ANGULO_INICIAL = 45;


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
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				bola.resetPosition();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				// left key is pressed: move our character
				if (nave.dNave == direccion::parado)
					nave.dNave = direccion::izquierda;
				else if (nave.dNave == direccion::derecha)
					nave.dNave = direccion::parado;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (nave.dNave == direccion::parado)
					nave.dNave = direccion::derecha;
				else if (nave.dNave == direccion::izquierda)
					nave.dNave = direccion::parado;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				bola.ballVelocity -= 15;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				bola.ballVelocity += 15;
			}
			localMouseCoords = sf::Mouse::getPosition(window);
		}

		//actualizamos direccion nave
		
		dt = clock.restart().asSeconds();
		t_net_graph = "";
		t_net_graph += "fps: " + std::to_string(1.f/dt) + "\n";		
		t_net_graph += "angulo: " + std::to_string(bola.anguloBola) + "\n";
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