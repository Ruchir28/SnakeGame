#include "game.h"
#include <iostream>
#include "SDL.h"


Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      special_food_random(0, 100),
      special_food{-1, -1} {
  PlaceFood(food);
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  Uint32 special_food_start = 0;
  bool running = true;
  bool special_food_rendered = false;

  while (running) {
    frame_start = SDL_GetTicks();
    if(special_food.x != -1 && special_food.y != -1) {
      if(!special_food_rendered) special_food_start = SDL_GetTicks();
      special_food_rendered = true;
    } else {
      special_food_rendered = false;
    }
    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, special_food);

    frame_end = SDL_GetTicks();

    if(special_food_rendered &&  (frame_end - special_food_start) >= 5000) {
      special_food.x = -1;
      special_food.y = -1;
      special_food_rendered = false;
    }

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::welcomeScreen(WelcomeScreen &&welcomeScreen, std::size_t kMsPerFrame) {
  Uint32 frame_start;
  Uint32 frame_end; 
  Uint32 frame_duration;
  bool quit = false;
  SDL_Event e;
  // Text input from user
  std::string userInput = "";
  SDL_StartTextInput();
  while (!quit) {
    frame_start = SDL_GetTicks();
    // Handle events on queue
    if (SDL_PollEvent(&e) != 0) {
      // User requests quit
      if (e.type == SDL_QUIT) {
        quit = true;
      }
      if(e.type == SDL_TEXTINPUT) {
        /* Add new text onto the end of our text */
        userInput += e.text.text;
      }
      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_RETURN:
            quit = true;
            break;
          case SDLK_BACKSPACE:
            if (userInput.length() > 0) {
              userInput.pop_back();
            }
            break;
          default:
            break;
        }
      }
    }

    // Render the welcome screen
    welcomeScreen.Render(userInput);

    frame_end = SDL_GetTicks();
    frame_duration = frame_end - frame_start;
    if (frame_duration < kMsPerFrame) {
      SDL_Delay(kMsPerFrame - frame_duration);
    }
  }
  SDL_StopTextInput();
  userName = userInput;
}

std::string Game::GetUserName() const {
  return userName;
}

void Game::PlaceFood(SDL_Point &food) {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;
  if (snake.pause) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  if(special_food.x == new_x && special_food.y == new_y) {
    score += 5;
    special_food.x = -1;
    special_food.y = -1;
  }

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood(food);
    if(special_food.x == -1 && special_food.y == -1) {
      if(special_food_random(engine) < 20) {
        PlaceFood(special_food);
      }
    }
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }