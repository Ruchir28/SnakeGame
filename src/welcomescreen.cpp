#include "welcomescreen.h"
#include <iostream>
#include <string>
#include <thread>
#include <filesystem>

WelcomeScreen::WelcomeScreen(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t line_width, const std::size_t line_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      line_width(line_width),
      line_height(line_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  if (TTF_Init() == -1) {
    std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
  }


  // Create Window
  sdl_window = SDL_CreateWindow("Welcome To Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

WelcomeScreen::~WelcomeScreen() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

WelcomeScreen::WelcomeScreen(WelcomeScreen&& other) noexcept
    : sdl_window(other.sdl_window),
      sdl_renderer(other.sdl_renderer),
      screen_width(other.screen_width),
      screen_height(other.screen_height),
      line_width(other.line_width),
      line_height(other.line_height) {
  other.sdl_window = nullptr;
  other.sdl_renderer = nullptr;
}



void WelcomeScreen::Render(std::string text) {

    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Write Welcome to Snake Game
    TTF_Font* font = TTF_OpenFont("../font/Roboto-Regular.ttf", 20);
    if (font == NULL) {
        std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }
    SDL_Color textColor = {255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Welcome to Snake Game", textColor);
    if (textSurface == NULL) {
        std::cerr << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(sdl_renderer, textSurface);
    if (textTexture == NULL) {
        std::cerr << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
    }
    SDL_Rect textRect;
    textRect.x = 0;
    textRect.y = 0;
    textRect.w = line_height;
    textRect.h = textSurface->h;
    SDL_FreeSurface(textSurface);
    textSurface = NULL;
    SDL_RenderCopy(sdl_renderer, textTexture, NULL, &textRect);
    std::string display_text = "Enter your name:" + text;
    SDL_Surface* textSurface2 = TTF_RenderText_Solid(font, display_text.c_str(), textColor);
    if (textSurface2 == NULL) {
        std::cerr << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }
    SDL_Texture* textTexture2 = SDL_CreateTextureFromSurface(sdl_renderer, textSurface2);
    if (textTexture2 == NULL) {
        std::cerr << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
    }
    SDL_Rect textRect2;
    textRect2.x = 0;
    textRect2.y = textRect.h + 10;
    textRect2.w = textSurface2->w;
    textRect2.h = textSurface2->h;
    SDL_FreeSurface(textSurface2);
    textSurface2 = NULL;
    SDL_RenderCopy(sdl_renderer, textTexture2, NULL, &textRect2);
    SDL_RenderPresent(sdl_renderer);
    SDL_DestroyTexture(textTexture2);
    TTF_CloseFont(font);
}

void WelcomeScreen::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
