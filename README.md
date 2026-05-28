# Lode Runner Clone

For the final project of the C++ Object-Oriented Programming course, we were tasked with building a classic Lode Runner clone. This repository showcases the implementation built using the SFML 3 framework. It ensures seamless integration between the graphical frontend and the core game logic through strict object-oriented principles.

## 🌟 Key Features
* **Classic Gameplay:** Navigate levels, climb ladders, slide on ropes, collect coins, dig through floors, and avoid enemies to progress.
* **Distinct Enemy AI:** Features both BFS-based pathfinding enemies (Smart) and randomized movement enemies (Stupid).
* **Dynamic UI & Screen Management:** Fully functional main menu, settings, help screen, and game overlays.
* **Customizable Themes:** Seamlessly switch between classic "Lode Runner" and custom "Mario" visual/audio themes in the settings.
* **Efficient Resource Management:** Optimized loading and caching of textures, fonts, and sound buffers.

## 🏗️ Implementation Details
This project was designed with a heavy focus on clean architecture and object-oriented design:
* **Graphics & User Interface:** Built entirely with SFML 3. The visual architecture handles dynamic sprite rendering, responsive UI components, and real-time user input events.
* **Game Loop & Screen States:** Driven by a centralized `Game` class that manages a state machine of various `Screen` objects (e.g., `GameScreen`, `MenuScreen`, `SettingsScreen`).
* **Resource Management:** A Singleton `ResourceManager` handles disk I/O, caching assets to ensure high performance. A supplementary `StyleManager` allows seamless toggling between different asset packs.
* **Collision & Interactions:** Utilizes a double-dispatch (Visitor) pattern to handle complex interactions between moving entities (`Player`, `Enemy`) and static environment objects (`Wall`, `Ladder`, `DiggableFloor`).
* **Level Generation:** Maps are loaded dynamically from `.txt` files, parsing ASCII layouts into fully interactive game objects.

## 🛠️ Build Instructions
This project uses **CMake** for its build system.

### Prerequisites
* C++17 or higher compiler
* CMake (3.26+)
* SFML 3

### Building
Clone the repository and build using CMake:
```bash
git clone https://github.com/yourusername/your-repo-name.git
cd your-repo-name

mkdir build
cd build

# Generate build files and compile
cmake ..
cmake --build .
```

### Running
Once built, you can run the executable directly from the build directory:
```bash
./OOP_Project_1
```
*(Note: The CMake configuration will automatically copy the `resources/` directory into your build folder so all assets load correctly).*

## 🎮 Controls
* **Arrow Keys:** Move Left / Right / Climb Up / Climb Down
* **Z / X:** Dig Left / Dig Right
* **Esc:** Return to Menu
