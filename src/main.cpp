#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "welcomescreen.h"
#include <thread>
#include "highscoremanager.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  constexpr std::size_t kLineHeight{200};
  constexpr std::size_t kLineWidth{500};
  HighScoreManager highScoreManager;
  WelcomeScreen welcomeScreen(kScreenWidth, kScreenHeight, kLineWidth, kLineHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.welcomeScreen(std::move(welcomeScreen), kMsPerFrame);
  std::cout << "Here";
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "User:" << game.GetUserName() <<" Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  highScoreManager.addScore(game.GetUserName(),game.GetScore());
  return 0;
}