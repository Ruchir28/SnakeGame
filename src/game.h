#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "welcomescreen.h"
#include <string>

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  void welcomeScreen(WelcomeScreen &&welcomeScreen, std::size_t kMsPerFrame);
  int GetScore() const;
  int GetSize() const;
  std::string GetUserName() const;

 private:
  Snake snake;
  SDL_Point food;
  SDL_Point special_food;
  std::string userName;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::uniform_int_distribution<int> special_food_random;

  int score{0};

  void PlaceFood(SDL_Point &food);
  void Update();
};

#endif