#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include "SDL_ttf.h"
#include "SDL.h"
#include <string>

class WelcomeScreen {
  public:
    WelcomeScreen(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t line_width, const std::size_t line_height);
   ~WelcomeScreen();

  void Render(std::string text);
  void UpdateWindowTitle(int score, int fps);

  // disable copy and assignment
  WelcomeScreen(const WelcomeScreen&) = delete;
  WelcomeScreen& operator=(const WelcomeScreen&) = delete;
  // disable move assignment
  WelcomeScreen& operator=(WelcomeScreen&& other) = delete;
  // overload move constructor
  WelcomeScreen(WelcomeScreen&& other) noexcept;
 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t line_width;
  const std::size_t line_height;
};

#endif