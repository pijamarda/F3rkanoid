F3rkanoid
=========

Arkanoid clone written in C++ using the SFML library.

Demo:
https://youtu.be/B987opu2biw

Demo with DEBUG mode on:
https://youtu.be/xNazb71JcUc

---

## Requirements

- [Docker Desktop](https://www.docker.com/products/docker-desktop/) installed and running

That's it. No compiler, no SFML, no extra tooling needed on the host machine.

---

## Build for Windows

Open a terminal (PowerShell or CMD) in the **project root** and run:

```
.\build-windows.cmd
```

The first run downloads and compiles SFML 2.6.1 from source inside Docker — this takes ~5 minutes. Every subsequent run reuses the Docker layer cache and finishes in seconds.

Output is placed in `dist\windows\`:

```
dist\windows\
├── f3rkanoid.exe
├── openal32.dll    ← required for audio, must stay next to the .exe
└── data\           ← fonts, images and sounds
```

---

## Run the game

Double-click `dist\windows\f3rkanoid.exe`, **or** from a terminal:

```
cd dist\windows
.\f3rkanoid.exe
```

> The executable must be run from inside `dist\windows\` so it can find the `data\` folder.

---

## Controls

| Key | Action |
|-----|--------|
| P | Pause / resume |
| M | Toggle music on/off |
| S | Toggle sound effects on/off |
| Q | Reset ball position |
| Z / A | Decrease / increase ball speed |

Mouse controls the paddle.

---

## Window size

The game renders at a 2× scale by default (1200×960). To change it, edit the constant at the top of `source/main.cpp`:

```cpp
const float SCALE = 2.0f;  // try 1.0, 1.5, 3.0 …
```

Then rebuild with `.\build-windows.cmd`.

---

## How it works

- Ball physics based on angle (degrees → sin/cos), frame-independent via delta time
- Mouse-controlled paddle
- 5×5 brick grid with random colour assignment per level
- Collision detection between ball↔paddle and ball↔bricks

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
