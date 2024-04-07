
# Miško3 Tetris Game
This is a repository for a simple Tetris game implemented in C programming language on Miško3 - a custom arm embeded system with stm32g474 microcontroller.

## Table of Contents

- [Miško3 Tetris Game](#miško3-tetris-game)
  - [Table of Contents](#table-of-contents)
  - [Miško3 Board](#miško3-board)
  - [Setup](#setup)
    - [vscode](#vscode)
      - [Linux (Ubuntu)](#linux-ubuntu)
    - [CubeIDE](#cubeide)
  - [Overview](#overview)
    - [Tetris piece aka. Tetromino](#tetris-piece-aka-tetromino)
    - [Field array](#field-array)
    - [Collisions](#collisions)
    - [Main loop](#main-loop)
  - [Future plans](#future-plans)


## Miško3 Board

The board was developed by students and professors at the Faculty of Electrical Engineering in Ljubljana, Slovenia. 
And as far as i know produced by [iSYSTEM labs](https://www.isystemlabs.si/).
You can find documentation and more information about the board on the [github repo](https://github.com/mjankovec/MiSKo3.git) 

## Setup

If you happen to be in possesion of the board and want to run the game on it, you can follow the steps bellow.

### vscode 

clone the repository:
```bash 
git clone https://github.com/irislapa/misko3-tetris.git
```
#### Linux (Ubuntu)
```bash
sudo apt-get install make
sudo apt-get install cmake # for building stlink
```
Download the [arm toolchain](https://developer.arm.com/downloads/-/gnu-rm) archive for your system.
The workspace path is set up for it to be installed in /usr/share, you can install it elsewhere but,
you will have to change the path in the makefile, 
```bash
sudo tar -xvjf /Downloads/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 -C /usr/share
```
After that you will be required to create soft-links to the binaries so that project can compile:
```bash
cd /usr/bin
sudo ln -s /usr/share/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-gcc arm-none-eabi-gcc 
# repeat for all the binaries in the bin directory
```

To flash the board you will need to install the stlink tool, you can do so by cloning or downloading the [repo](https://github.com/stlink-org/stlink):

You want to extract/instal the contents of repo to /usr/local/share/stlink.
```bash
sudo mv /Downloads/stlink-1.8.0 /usr/local/share/stlink
```

Then run the following commands:
```bash
cd /usr/local/share/stlink
cmake .
make
```
Now that the stlink is buit, you want create the following soft-links:
```bash
sudo ln -s /usr/local/share/stlink-1.8.0/bin/st-flash st-flash # for flashing the board
sudo ln -s /usr/local/share/stlink-1.8.0/bin/st-util st-util # in case you want to debug the board
```
If you plan on debugging you might need to install some additional libraries and vscode extensions, 
first try executing the binary file and see if it throws any errors, which should provide a solution.
In the terminal type in the previously created softlink and run it.
```bash
gcc-arm-none-eabi-gdb
```
The vscode you would want are:
- For syntax highliting and intellisense and such: [c/cpp tools](https://code.visualstudio.com/docs/languages/cpp)
- For debugging: [cortex-debug](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug)
- For using the virual com port: [serial monitor](https://marketplace.visualstudio.com/items?itemName=ms-vscode.vscode-serial-monitor)

To use the generate code and gui setup feature from cubeIDE, you can install the [CubeMX](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug) vscode extension.

You are now all set for running and debugging the project.
I have added tasks for convenience, press ctrl+shift+p, select "Tasks: Run Task" and choose the task you want to run.
Or you can also just type:
```bash
make # only build
make stflash # build and flash
```
If the build and/or flash is succesful, a green message will be printed in the terminal.

### CubeIDE
I didn't use windows for this project, so i can't provide a guide to a working vscode setup on Windows, but you can still resort to using CubeIDE.
You will have to first install CubeMX and convert the toolchain/IDE configuration from makefile to STM32CubeIDE.
You can do so by opening the project in CubeMX and under Project Manager -> Project -> Toolchain/IDE select STM32CubeIDE.
![](/images/image.png)
Now you can flash and debug the project using the CubeIDE.




## Overview

Tetris is a classic tile-matching puzzle video game where player manipulates falling pieces called tetrominoes. 
The goal is to complete horizontal lines without gaps.

I used the demo project from [repo](https://github.com/LAPSyLAB/Misko3_Docs_and_Projects.git), to build on, since it already has the necessary dirver implementations.

The game logic is based on the classic Tetris rules:

- Tetrominoes fall from the top of the playfield
- Player then moves and rotate tetrominoes to fit them into gaps
- Completing horizontal lines without gaps clears the line and awards points
- The game ends when the stack of tetrominoes reaches the top of the playfield


### Tetris piece aka. Tetromino
A tetromino can easily be represented as a 4x4 matrix, where each element is a boolean value, indicating if the cell is occupied or not.
The 
```c
typedef struct {
  int rotation;
  char shape;
  uint16_t grid[TETROMINO_SIZE]; // linearized representation
  int x; // location of upper most-left corner of matrix on the
  lcd
  int y;
} Tetromino;

Tetromino.shape = { 0, 1, 0, 0,
                    1, 1, 1, 0,
                    0, 0, 0, 0,
                    0, 0, 0, 0};
```
The 4x4 matrix allows for simple calculation of rotation for a tetromino:

```c
int rotateTetromino(int x, int y, int r) {
  switch (r % 4) {
    case 0: return (y * 4) + x; //0
    case 1: return 12 + y - (x * 4); //90
    case 2: return 15 - (y * 4) - x; //180
    case 3: return 3 - y + (x * 4); //270
  }
  return 0;
}
```

![](images/Untitled%20Diagram.drawio.png)

### Field array


### Collisions


### Main loop


## Future plans

- For the future i plan to implement the project with freeRTOS, and configure user interface with system interrupts, since the current implementation is laggy and not well optimized. 
- Make the graphics prettier and more appealing.
