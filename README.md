F3rkanoid
=========

Clon de Arkanoid hecho con SFML

See the demo here:
https://youtu.be/B987opu2biw

Requisitos:  
g++ - GNU C++ compiler >= version 4.7

Para compilarlo en Linux es necesario tener descargada la libreria SFML (recomendada version 2.3)

Link de descarga  
http://sfml-dev.org/download/sfml/
Descomprimimos el contenido de la carpeta, por ejemplo en:  
/home/zeneke/data/sdk/SFML-2.3/  
Compilamos con g++ utilizando el flag para utilizar c++11  
g++ -c -std=c++0x source/*.cpp -I /home/zeneke/data/sdk/SFML-2.3/include  
Linkamos con las librerias  
g++ *.o -o sfml-app -L /home/zeneke/data/sdk/SFML-2.3/lib -lsfml-graphics -lsfml-window -lsfml-system  
Y ejecutamos indicando manualmente donde estan los binarios de la libreria  
export LD_LIBRARY_PATH=/home/zeneke/data/sdk/SFML-2.3/lib && ./sfml-app  

