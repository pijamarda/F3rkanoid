F3rkanoid
=========

Arkanoid clone written in C++ using the SFML library.

Demo:
https://youtu.be/B987opu2biw

Demo with DEBUG mode on:
https://youtu.be/xNazb71JcUc

---

## Building for Windows

Requires [Docker Desktop](https://www.docker.com/products/docker-desktop/) running.

```
.\build-windows.cmd
```

The first run compiles SFML 2.6.1 from source inside Docker (~5 min). Subsequent runs use the Docker layer cache and are fast.

Output is placed in `dist\windows\`:

```
dist\windows\
├── f3rkanoid.exe
├── openal32.dll
└── data\
```

Double-click `f3rkanoid.exe` to run — no extra installs needed on the target machine.

### Controls

| Key | Action |
|-----|--------|
| P | Pause / resume |
| M | Toggle music |
| S | Toggle sound effects |
| Q | Reset ball |
| Z / A | Decrease / increase ball speed |

---

## How it works

- Ball physics based on angle (degrees → sin/cos), frame-independent via delta time
- Mouse-controlled paddle
- 5×5 brick grid with random colour assignment per level
- Collision detection between ball↔paddle and ball↔bricks

---

---

## DEPRECATED — old build instructions

> The instructions below are kept for historical reference.
> The project no longer requires a manual SFML installation or g++ on the host.

**Requisites:**
g++ - GNU C++ compiler >= version 4.7

Para compilarlo en Linux es necesario tener descargada la libreria SFML (recomendada version 2.3)

Link de descarga  
http://sfml-dev.org/download/sfml/  
Descomprimimos el contenido de la carpeta, por ejemplo en:  
/home/zeneke/data/sdk/SFML-2.3/  
Compilamos con g++ utilizando el flag para utilizar c++11  
g++ -c -std=c++0x source/*.cpp   
Linkamos con las librerias  
g++ *.o -o sfml-app -L /home/zeneke/data/sdk/SFML-2.3/lib -lsfml-graphics -lsfml-window -lsfml-system  
Y ejecutamos indicando manualmente donde estan los binarios de la libreria  
export LD_LIBRARY_PATH=/home/zeneke/data/sdk/SFML-2.3/lib && ./sfml-app  
