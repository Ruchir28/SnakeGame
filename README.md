# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>


## Features added 
1. Player name input window
2. Speical Food with 5 points, which is visible for 5 seconds
3. Logger using threads , which logs text in logger/log.txt file 
4. high score component which manager top 5 scores of the game and logs them to scores/high_score.txt file
5. Added Pause Functionality with space button

### Loop, Functions, I/O
1. ```Game::welcomeScreen``` method takes input from users, and renders a welcome screen prompt.
2. ``` HighScoreManager ``` class manages user highscores, reads highscore scores/high_score.txt file, 
   and maintains a list of all time 5 highest scores

### Object Oriented Programming
1. ```HighScoreManager, MessageQueue, WelcomeScreen``` classes are added which utilise OOP and genric templates
2. ```WelcomeScreen``` utilises member intiation lists 

### Memory Management 
1. ```WelcomeScreen``` utilises destructors 
2. ```Game::welcomeScreen``` and ```MessageQueue``` utilises move semantics 
3. ```WelcomeScreen``` follows rule of 5.

### Concurrency
1. ```AsyncLogger``` uses multithreading and insert logs in logger/log.txt file.
2. ```MessageQueue``` condition variables is utilised by messagequeue.
 

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* SDL2_TTF 
  * sdl2_ttf can be installed used 
    * Mac: [brew install sdl2_ttf]
    * Linux: [sudo apt-get install libsdl2-ttf-dev] 

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
