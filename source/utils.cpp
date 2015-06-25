#pragma once

#include "utils.h"

bool testCollision(Bola &mBola, Nave &mNave)
{
	bool hay_colision = false;
	//El primer && del if comprueba si la parte derecha de la bola esta dentro de la nave
	//El segundo && comprueba si la parte izquierda de la bola esta dentro de la nave
	if ((mBola.right() >= mNave.left() && mBola.right() <= mNave.right()) ||
		(mBola.left() >= mNave.left() && mBola.left() <= mNave.right()))
	{
		//Si se cumplen las condiciones anteriores entonces hay colision
		

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
				float angSalidaTemp = mBola.normalizaAngulo(impactoBola*diferencial - anguloDeEntrada);

				anguloDeSalida = mBola.normalizaAngulo(-anguloDeEntrada);

				if (anguloDeEntrada >= 0 && anguloDeEntrada <= 90)
					if (impactoBola < 0)
						if (angSalidaTemp > 200)
							anguloDeSalida = angSalidaTemp;
						else if (angSalidaTemp < 340)
							anguloDeSalida = angSalidaTemp;

				if (anguloDeEntrada > 90 && anguloDeEntrada <= 180)
					if (impactoBola > 0 && angSalidaTemp < 340)
						anguloDeSalida = angSalidaTemp;


				//DEBUG: Mostramos por consola
				//std::cout << "entrada: " << mBola.anguloBola << std::endl;
				//std::cout << "encho nave: " << mNave.naveAncho << " ";
				//std::cout << "impactoBola: " << impactoBola << std::endl;
				//std::cout << "salida: " << anguloDeSalida << std::endl;
				//std::cout << "salida norm: " << mBola.normalizaAngulo(anguloDeSalida) << std::endl;
			}

			//mBola.anguloBola = anguloDeSalida;//360 - mBola.anguloBola;
			mBola.anguloBola = mBola.normalizaAngulo(anguloDeSalida);
			hay_colision = true;


		}
		//TODO: Ajustar la zona de rebote, sobre todo cuando golpea lateralmente la NAVE
		//ahora mismo tiene un comportamiento herratico	
	}
	return hay_colision;
};

bool bolaBrickCollision(Bola &mBola, Brick &mbrick)
{
	bool hay_colision = false;
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
				hay_colision = true;
				mbrick.ladrillos_restantes--;
				//std::cout << "Colision vertical" << std::endl;
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
				hay_colision = true;
				mbrick.ladrillos_restantes--;
				//std::cout << "Colision lateral" << std::endl;
				//ladrillo.sprite.setColor(sf::Color::Black);
				ladrillo.sprite.setPosition(sf::Vector2f(-500.0f, -500.0f));
				//TODO: Esto solo cambioa hacia abajo o arriba la bola
				//hay que hacer la colision lateral
				mBola.anguloBola = mBola.normalizaAngulo(180 - mBola.anguloBola);
			}
		}
		else if ((mBola.bottom() >= ladrillo.top() && mBola.bottom() <= ladrillo.bottom()) ||
				 (mBola.top() <= ladrillo.bottom() && mBola.top() >= ladrillo.top()))
		{
			if ((mBola.right() >= ladrillo.left() && mBola.right() <= ladrillo.right()) ||
				(mBola.left() >= ladrillo.left() && mBola.left() <= ladrillo.right()))
			{
				hay_colision = true;
				mbrick.ladrillos_restantes--;
				//std::cout << "Colision diagonal" << std::endl;
				//ladrillo.sprite.setColor(sf::Color::Black);
				ladrillo.sprite.setPosition(sf::Vector2f(-500.0f, -500.0f));
				//TODO: Esto solo cambioa hacia abajo o arriba la bola
				//hay que hacer la colision lateral
				mBola.anguloBola = mBola.normalizaAngulo(180 + mBola.anguloBola);
			}
		}

	} //fin del for que recorre los ladrillos del objecto Brick
	return hay_colision;
};// fin de la funcion que comprueba la colision de la bola con los ladrillos