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

			float anguloDeEntrada = mBola.anguloBola;
			float anguloDeSalida = mBola.anguloBola;

			if (mBola.anguloBola > 0 && mBola.anguloBola <= 180)
			{
				//dividimos las 180 partes por el tamaño de la nave
				//en nuestro caso particular da alrededor de 0'73
				float diferencial = 180.0f / mNave.naveAncho;
				
				//ahora calculamos la diferencia del centro de la bola respecto al centro
				//de la nave, es decir restamos el centro de la bola menos la coordenada x del centro de
				//la nave eso nos da la zona de impacto.
				float impactoBola = centroBolaX - centroNaveX;

				//el angulo de salida sera la zona de impacto sobre la nave por el diferencial calculado antes
				//y le restamos el angulo de entrada
				//en el caso de que choque en el centro la zona de impacto por el diferencial sera cero
				//y en los extremos cambiara mucho el angulo de salida
				
				if (anguloDeEntrada >= 30 && anguloDeEntrada <= 150)
					anguloDeSalida = impactoBola*diferencial - anguloDeEntrada;
				else
					anguloDeSalida = -anguloDeEntrada;
				

				//DEBUG: Mostramos por consola
				std::cout << "entrada: " << mBola.anguloBola << std::endl;
				//std::cout << "encho nave: " << mNave.naveAncho << " ";
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

void bolaBrickCollision(Bola &mBola, Brick &mbrick)
{
	//El primer && del if comprueba si la parte derecha de la bola esta dentro de la nave
	//El segundo && comprueba si la parte izquierda de la bola esta dentro de la nave
	for (auto &ladrillo : mbrick.ladrillos)
	{
		//Si detectamos la colision por la izquierda o la derecha del ladrillo entonces
		if ((mBola.right() >= ladrillo.left() && mBola.right() <= ladrillo.right()) &&
			(mBola.left() >= ladrillo.left() && mBola.left() <= ladrillo.right()))
		{
			//si la bola viene desde arriba, entonces...
			if ((mBola.bottom() >= ladrillo.top() && mBola.bottom() <= ladrillo.bottom()) ||
				(mBola.top() <= ladrillo.bottom() && mBola.top() >= ladrillo.top()))
			{
				std::cout << "Colision vertical" << std::endl;
				//ladrillo.sprite.setColor(sf::Color::Black);
				ladrillo.sprite.setPosition(sf::Vector2f(-500.0f, -500.0f));
				mBola.anguloBola = mBola.normalizaAngulo(-mBola.anguloBola);
			}
		}
		//si detectamos la colision por arriba o por abajo
		else if ((mBola.bottom() >= ladrillo.top() && mBola.bottom() <= ladrillo.bottom()) &&
				 (mBola.top() <= ladrillo.bottom() && mBola.top() >= ladrillo.top()))
		{
			if ((mBola.right() >= ladrillo.left() && mBola.right() <= ladrillo.right()) ||
				(mBola.left() >= ladrillo.left() && mBola.left() <= ladrillo.right()))
			{
				std::cout << "Colision lateral" << std::endl;
				//ladrillo.sprite.setColor(sf::Color::Black);
				ladrillo.sprite.setPosition(sf::Vector2f(-500.0f, -500.0f));
				//TODO: Esto solo cambioa hacia abajo o arriba la bola
				//hay que hacer la colision lateral
				mBola.anguloBola = mBola.normalizaAngulo(180-mBola.anguloBola);
			}
		}
		else if ((mBola.bottom() >= ladrillo.top() && mBola.bottom() <= ladrillo.bottom()) ||
				 (mBola.top() <= ladrillo.bottom() && mBola.top() >= ladrillo.top()))
		{
			if ((mBola.right() >= ladrillo.left() && mBola.right() <= ladrillo.right()) ||
				(mBola.left() >= ladrillo.left() && mBola.left() <= ladrillo.right()))
			{
				std::cout << "Colision diagonal" << std::endl;
				//ladrillo.sprite.setColor(sf::Color::Black);
				ladrillo.sprite.setPosition(sf::Vector2f(-500.0f, -500.0f));
				//TODO: Esto solo cambioa hacia abajo o arriba la bola
				//hay que hacer la colision lateral
				mBola.anguloBola = mBola.normalizaAngulo(180 + mBola.anguloBola);
			}
		}
		
	} //fin del for que recorre los ladrillos del objecto Brick
};// fin de la funcion que comprueba la colision de la bola con los ladrillos

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
	const unsigned int LVL_WIDTH = MAX_WIDTH - PARED_WIDTH*2;
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
	bool pausa = false;

	sf::RenderWindow window(sf::VideoMode(MAX_WIDTH, MAX_HEIGHT), "F3RKANOID");
	Nave nave = Nave(LVL_WIDTH, LVL_HEIGHT, VELOCIDAD_NAVE_INICIAL);	
	Bola bola = Bola(LVL_WIDTH, LVL_HEIGHT, VELOCIDAD_BOLA_INICIAL, ANGULO_INICIAL);
	Brick ladrillos = Brick(1, LVL_WIDTH, LVL_HEIGHT, PARED_WIDTH);

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
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				pausa = !pausa;
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

		//A ver que tal funciona, si le damos a la "P" se deberia pausar la actualizacion de las posiciones
		// de la nave y la bola

		if (!pausa)
		{
			nave.actualizarPos(dt, localMouseCoords);
			bola.actualizarPos(dt);
			testCollision(bola, nave);
			bolaBrickCollision(bola, ladrillos);
		}
		//
		window.clear();
		
		nave.draw(window, DEBUG_ACTIVADO);
		ladrillos.draw(window);
		bola.draw(window, DEBUG_ACTIVADO);		
		window.draw(text_net_graph);
		window.display();
	}

	return 0;
}