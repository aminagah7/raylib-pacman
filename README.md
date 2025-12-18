# Raylib Pacman 🕹️

A classic Pacman-style game built in **C** using the **raylib** library, developed as part of the basic Programming Course – fall 1403 at Amirkabir University of Technology. This project features multiple ghost types, power-ups (Apple, Mushroom, Pepper, Cherry), a custom map system, and a persistent high-score leaderboard.

## ✨ Features
* **Classic Gameplay:** Navigate the maze, collect points, and avoid ghosts.
* **Power-ups:** * 🍎 **Apple**: Increases health.
    * 🍄 **Mushroom**: Temporary invincibility.
    * 🌶️ **Pepper**: "Soul Eater" mode (eat the ghosts!).
* **Dynamic Difficulty:** Choose between Easy, Normal, and Hard modes.
* **Records System:** Saves player names, scores, and dates to a local file.
* **Multiple Maps:** Supports different maze layouts.

## 🛠️ Prerequisites
To build this game, you need:
* A C compiler (GCC/MinGW recommended).
* [raylib](https://www.raylib.com/) (Version 4.5 or higher).
* CMake (Version 3.10 or higher).

## 👨‍🏫 Supervision
This project was developed for the basic Programming Course – fall 1403
Amirkabir University of Technology

Supervised by:

* Dr. Hossein Zeynali

## 📸 Preview
![Login Screenshot](.\resources\Pac-Man1.png)
![Level Screenshot](.\resources\Pac-Man2.png)
## Map
![Map1 Screenshot](.\resources\Pac-Man3.png)
![Map2 Screenshot](.\resources\Pac-Man4.png)
## Game Over
![Game Over Screenshot](.\resources\Pac-Man5.png)



## 🚀 Getting Started

### 1. Clone the repository
```bash
git clone [https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git](https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git)
cd YOUR_REPO_NAME
2. Build using CMake (Recommended)
Bash

mkdir build
cd build
cmake ..
cmake --build .
3. Running the game
Ensure the resources/ folder is in the same directory as your executable, then run:

Bash

./your_project_name  # Or your_project_name.exe on Windows
📂 Project Structure
main.c: Entry point and game loop.

pacman.c / .h: Player logic and movement.

enemy.c / .h: Ghost AI and behaviors.

map.c / .h: Level design and collision detection.

menu.c / .h: UI, high scores, and menu navigation.

resources/: Contains all textures (.png), sounds (.wav), and fonts.

🎮 Controls
Arrows: Move Pacman.

R-Shift: Select/Action in Menus.

Esc: Exit Game.

📜 License
This project is open source. Feel free to use and modify!