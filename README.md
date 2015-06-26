F3rkanoid
=========

Clon de Arkanoid hecho con SFML

Para compilarlo en Linux es necesario tener descargada la libreria SFML version 2.1
Lo bueno es que no es necesario instalar nada:

Link de descarga  
http://sfml-dev.org/download/sfml/2.1/  
Descomprimimos el contenido de la carpeta, por ejemplo en:  
/home/pijamarda/SFML/  
Compilamos con g++ utilizando el flag para utilizar c++11  
g++ -c -std=c++0x *.cpp -I /home/pijamarda/SFML2.1/include  
Linkamos con las librerias  
g++ *.o -o sfml-app -L /home/pijamarda/SFML2.1/lib -lsfml-graphics -lsfml-window -lsfml-system  
Y ejecutamos indicando manualmente donde estan los binarios de la libreria  
export LD_LIBRARY_PATH=/home/pijamarda/SFML2.1/lib && ./sfml-app  

