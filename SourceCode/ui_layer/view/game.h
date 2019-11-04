#ifndef GAME_H
#define GAME_H

#include <random>
#ifdef WINDOWS
    #include "ui_layer/sdl/include/windows/SDL.h"
   // #include "ui_layer/sdl/include/windows/SDL2_gfxPrimitives.h"
   // #include "ui_layer/sdl/include/windows/SDL_ttf.h"
#else
    #include "ui_layer/sdl/include/linux/SDL.h"
   // #include "ui_layer/sdl/include/linux/SDL2_gfxPrimitives.h"
   // #include "ui_layer/sdl/include/linux/SDL_ttf.h"
#endif
#include "ui_layer/controller/controller.hpp"
//#include "renderer.h"
#include "snake.h"
#include "domain_layer/play_zone/PlayZone.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(ui_layer::controller::Controller* const &controller, PlayZone &playzone,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
};

#endif