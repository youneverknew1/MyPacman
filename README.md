# Pacman , a man who eats poop.

A lightweight, high-performance Pacman game built from scratch in C using the **SDL2** library. This project features a dynamic map loading system, custom ghost AI, and real-time score tracking.

(<img width="546" height="638" alt="Screenshot 2026-04-11 013629" src="https://github.com/user-attachments/assets/84375a05-6ac6-46c1-9203-1ff813560601" />) 

## Features

* **Dynamic Map Loader:** The game reads `map.txt` to generate levels. You can change the grid size (rows/cols) directly in the text file without recompiling.
* **Intelligent Ghost AI:** * **Blinky (Red):** Uses Euclidean distance math to chase Pacman directly.
    * **Clyde (Orange):** An "Ambusher" AI that predicts Pacman's movement to cut him off.
* **Pellet(Poop) Regeneration:** Ghosts act as "planters," dropping new pellets(actually POOP) as they move through empty spaces, creating an endless survival challenge.
* **Custom UI:** A retro-style score counter rendered using custom pixel logic.

## Built With

* **Language:** C 
* **Graphics/Input:** [SDL2](https://www.libsdl.org/)
* **Compiler:** MinGW

## Installation & Setup

1.  **Clone the Repo:**
    ```bash
    git clone [https://github.com/youneverknew1/MyPacman.git](https://github.com/youneverknew1/MyPacman.git)
    cd MyPacman
    ```
2.  **Compile:**
    ```bash
    gcc -Iinclude -Llib -Wall -std=c99 src/*.c -o pacman -lmingw32 -lSDL2main -lSDL2
    ```
3.  **Run:**
    ```bash
    ./pacman
    ```

## How to Play

* **Arrows:** Move Pacman through the maze.
* **Objective:** Eat all the poops while avoiding the two ghosts.
* **Survival:** Beware! The ghosts will drop new pellets behind them, making the maze never-ending.

## Project Structure

* `src/`: Contains all `.c` logic (AI, Entity management, Map loading).
* `include/`: Header files and constants.
* `assets/`: Map data and game resources.

---
Developed with ❤️ by [Shahriar shadid,CSE-21,MBSTU]
