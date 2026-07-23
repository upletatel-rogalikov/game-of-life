# Game of Life

A simple recreation of Conway's Game of Life

## Building

### Prerequisites

>* C++23 compiler
>* CMake 4.3 or newer
>* Ninja build system

* ### Windows
	* #### Visual Studio
		>1. Clone repository into your `source/repos` folder
		>2. Open repository inside Visual Studio. CMake will automatically generate necessary build files
		>3. Choose `game_of_life.exe` target 
		>4. Build the application (`F5`)

* ### Linux
	>1. Clone repository into your preferred location
	>2. Run `cmake -G Ninja -B build`
	>3. Inside `build/` run `ninja`

* ### MacOS

## Running
* ### Windows
	Open `game_of_life.exe`

* ### Linux
	Run `./game_of_life`

* ### MacOS