F3rkanoid
=========

Arkanoid clone written in C++ using the SFML library.

Demo:
https://youtu.be/B987opu2biw

Demo with DEBUG mode on:
https://youtu.be/xNazb71JcUc

---

## Download

Ready-to-play builds are on the [Releases page](https://github.com/pijamarda/F3rkanoid/releases/latest). Pick the file for your system:

| System | File | How to run |
|--------|------|------------|
| Windows | `f3rkanoid-X.Y.Z-windows-x64.zip` | Extract it and double-click `f3rkanoid.exe` |
| Linux (x86-64) | `f3rkanoid-X.Y.Z-linux-x64.tar.gz` | `tar xzf f3rkanoid-*.tar.gz` then run `./f3rkanoid-*/f3rkanoid.sh` |

> On WSL, sound needs `sudo apt install libpulse0`.

The rest of this README is about building the game yourself.

---

## Requirements

- Docker installed and running: [Docker Desktop](https://www.docker.com/products/docker-desktop/) on Windows, or Docker Engine on Linux

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

On Linux you can build the Windows version too, with `./build-windows.sh`.

---

## Build for Linux

From a terminal in the **project root**:

```
./build-linux.sh
```

Same idea as the Windows build: SFML 2.6.1 is compiled inside Docker on the first run (~5 min), then cached.

Output is placed in `dist/linux/`:

```
dist/linux/
├── f3rkanoid       ← the game binary
├── f3rkanoid.sh    ← launcher (runs the game from the right folder)
├── lib/            ← bundled audio/font libraries (OpenAL, FreeType, Vorbis, FLAC…)
└── data/           ← fonts, images and sounds
```

Run it with `./dist/linux/f3rkanoid.sh`. The folder can be copied to any x86-64 distro as recent as Ubuntu 22.04 or newer; it only needs the usual desktop libraries (X11, OpenGL, PulseAudio/PipeWire).

> On WSL, sound needs `sudo apt install libpulse0` (WSLg provides the audio server, but not the client library).

---

## Run the game

**Linux:** `./dist/linux/f3rkanoid.sh`

**Windows:** double-click `dist\windows\f3rkanoid.exe`, **or** from a terminal:

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

Then rebuild with `.\build-windows.cmd` (Windows) or `./build-linux.sh` (Linux).

---

## How it works

- Ball physics based on angle (degrees → sin/cos), frame-independent via delta time
- Mouse-controlled paddle
- 5×5 brick grid with random colour assignment per level
- Collision detection between ball↔paddle and ball↔bricks

---

## Making a release

Releases are created with one command from an up-to-date `master` with no uncommitted changes:

```
./release.sh
```

It reads the current version from the `VERSION` file and asks which kind of release this is:

| Type | Example | Use it for |
|------|---------|------------|
| patch | 1.0.0 → 1.0.1 | bug fixes, small changes |
| minor | 1.0.0 → 1.1.0 | new features |
| major | 1.0.0 → 2.0.0 | big or incompatible changes |

The script updates `VERSION`, commits it, creates the git tag (e.g. `v1.1.0`) and pushes both. The tag push starts the [Release workflow](.github/workflows/release.yml), which builds the Windows and Linux versions and publishes them on the Releases page after about 10–15 minutes.

Use `./release.sh --dry-run` to see what would happen without changing anything.

The version also appears in the game's window title (e.g. "F3RKANOID 1.1.0").

---

## Credits

Ball and paddle sprites by [Kenney](https://www.kenney.nl) (see `data/img/readme.txt`).

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
