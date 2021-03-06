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
#include "domain_layer/game/GameHandler.hpp"
#include "ui_layer/controller/Controller.hpp"
//#include "renderer.h"
#include "domain_layer/snake/Snake.hpp"
#include "domain_layer/play_zone/PlayZone.hpp"
#include "domain_layer/player/Player.hpp"
#include "domain_layer/food/Food.hpp"
#include "domain_layer/food/FoodFactory.hpp"

class Game : public domain_layer::game::GameHandler {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(ui_layer::controller::Controller* const &controller, PlayZone &playzone,
           std::size_t target_frame_duration) override;
  int GetScore() const override;
  int GetSize() const override;
   void handle_input_right() override;
   void handle_input_left() override;
   void handle_input_up() override;
   void handle_input_down()override;
  domain_layer::food::Food *foods;
  domain_layer::food::Food *foods1;
  domain_layer::food::Food *foods2;
  domain_layer::food::Food *foods3;

  domain_layer::food::Food *foodsObjs[4];
 private:
  Snake snake;
//  SDL_Point food;
  ui_layer::controller::Controller *ctrl;
  domain_layer::food::FoodFactory *mFoodFactoryPtr;
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  int score{0};
  int iteration;
  void PlaceFood();
  void Update();
};

#endif
