#include "Brick.h"

Brick::Brick(int nivel, unsigned int LVL_WIDTH, unsigned int LVL_HEIGHT)
{
	MAX_WIDTH = LVL_WIDTH;
	MAX_HEIGHT = LVL_HEIGHT;

	sf::Texture text1;
	text1.loadFromFile("img/png/element_blue_rectangle.png");
	tipoLadrillos.push_back(text1);

	sf::Texture text2;
	text2.loadFromFile("img/png/element_green_rectangle.png");
	tipoLadrillos.push_back(text2);

	sf::Texture text3;
	text3.loadFromFile("img/png/element_grey_rectangle.png");
	tipoLadrillos.push_back(text3);

	sf::Texture text4;
	text4.loadFromFile("img/png/element_purple_rectangle.png");
	tipoLadrillos.push_back(text4);

	sf::Texture text5;
	text5.loadFromFile("img/png/element_red_rectangle.png");
	tipoLadrillos.push_back(text5);

	sf::Texture text6;
	text6.loadFromFile("img/png/element_yellow_rectangle.png");
	tipoLadrillos.push_back(text6);

	/*
	El numero de nivel marcara la disposicion de los ladrillos
	ahora mismo solo generamos el nivel 1
	*/
	if (nivel == 1)
	{
		//esta es la semilla de los numeros aleatorios
		srand((unsigned)time(0));

		num_ladrillos = ANCHO * ALTO;
		// Este nivel compone los ladrillos de forma rectangular con dimensiones
		// ANCHO x ALTO
		for (unsigned int i = 0; i < ANCHO; i++)
		{
			for (unsigned int j = 0; j < ALTO; j++)
			{
				//Elegimos un numero entre 0 y NUM_COLORES

				int random = (rand() % NUM_COLORES);

				sf::Sprite spriteTemp;
				//Este numero aleatorio selecciona la textura del vector de tama�o
				//NUM_COLORES que hemos creado
				spriteTemp.setTexture(tipoLadrillos[random]);

				//std::cout << random << " ";

				int anchoTemp = spriteTemp.getGlobalBounds().width;
				int altoTemp = spriteTemp.getGlobalBounds().height;

				//std::cout << anchoTemp << " " << altoTemp << " ";

				//TODO: Debemos marcar la posicion inicial del bloque de ladrillos
				// ahora mismo lo estamos generando desde la esquina arriba izquierda (0,0)

				/*
				Asignamos a cada ladrillo del vector, un sprite aleatorio y una posicion
				de manera que queda 
				# # # # #
				# # # # #
				*/
				//TODO: Considerar asignar aqui mismo la poisicion en el propio sprite
				Ladrillo ladrilloTemp = { spriteTemp, sf::Vector2f(i*anchoTemp, j*altoTemp) };
				ladrillos.push_back(ladrilloTemp);
			}
			//std::cout << std::endl;
		}
	}

	/*
	for (auto num : ladrillos)
		std::cout << num.pos.x << "|" << num.pos.y << " ";
	std::cout << std::endl;
	*/

}

void Brick::draw(sf::RenderWindow &window)
{	
	//TODO: Ahora mismo el modo de posicionar cada sprite es un poco enrevesado
	// en vez de asignar la posicion del sprite en el momento de su creacion
	// asignamos su posicion en el metodo pintar, es posible que sea lento
	//TODO: Probar a cambiar la asignacion de posicion en el propio sprite del Struct ladrillo
	for (auto lad : ladrillos)
	{
		sf::Vector2f posTemp = sf::Vector2f(lad.pos.x, lad.pos.y);
		lad.sprite.setPosition(posTemp);
		window.draw(lad.sprite);
	}
}