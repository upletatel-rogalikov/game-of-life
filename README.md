# Game of Life

A simple recreation of Conway's Game of Life, created with [raylib](https://github.com/raysan5/raylib)

## Building

### Prerequisites

>* **C\+\+23 compiler** (required C\+\+ standard can be modified in `CMakeLists.txt`, but older standards have not been tested)
>* **CMake 4.3 or newer** (required CMake version can be modified in `CMakeLists.txt`, but older version have not been tested)
>* **Ninja** (or any other build system supported by CMake)

* ### Windows
	* #### Visual Studio
		>**1.** Clone repository into your `source/repos` folder
		>
		>**2.** Open repository inside Visual Studio. CMake will automatically generate necessary build files
		>
		>**3.** Choose `game_of_life.exe` target
		>
		>**4.** Build the application (`F5`)

* ### Linux
	>**1.** Clone repository into your preferred location
	>
	>**2.** Run `cmake -G Ninja -B build`
	>
	>**3.** Inside `build/` run `ninja`

* ### MacOS
	***Building has not been tested on MacOS, but should be possible***

## Running
* ### Windows
	Open `game_of_life.exe`

* ### Linux
	Run `./game_of_life`

* ### MacOS
	***The program has not been tested on MacOS***