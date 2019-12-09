//helps to create playzone object. returns score to view

#include "Game.hpp"
#include <iostream>
#ifdef WINDOWS
    #include "ui_layer/sdl/include/windows/SDL.h"
    #include "ui_layer/sdl/include/windows/SDL2_gfxPrimitives.h"
    #include "ui_layer/sdl/include/windows/SDL_ttf.h"
#else
    #include "ui_layer/sdl/include/linux/SDL.h"
    #include "ui_layer/sdl/include/linux/SDL2_gfxPrimitives.h"
    #include "ui_layer/sdl/include/linux/SDL_ttf.h"
#endif

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)) {
        iteration = 0;
        mFoodFactoryPtr = domain_layer::food::FoodFactory::Get();
        foodsObjs[0]  = mFoodFactoryPtr->CreateRandomFood();
        foodsObjs[1]  = mFoodFactoryPtr->CreateRandomFood();
        foodsObjs[2]  = mFoodFactoryPtr->CreateRandomFood();
        foodsObjs[3]  = mFoodFactoryPtr->CreateRandomFood();

        PlaceFood();

}

void Game::Run(ui_layer::controller::Controller* const &controller, PlayZone &playzone,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller->HandleInput(running, snake);
    Update();
    playzone.Render(snake,  foodsObjs);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      playzone.UpdateWindowTitle(score, frame_count);
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

void Game::PlaceFood() {
  int x, y;
  /*
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      break;
    }
  } */
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      foodsObjs[0]->setFood(x,y);
      break;
    }
  }
  if(iteration <= 20){

          while (true) {
            x = random_w(engine);
            y = random_h(engine);
            // Check that the location is not occupied by a snake item before placing
            // food.
            if (!snake.SnakeCell(x, y)) {
              foodsObjs[1]->setFood(x,y);
              break;
            }
          }
          while (true) {
            x = random_w(engine);
            y = random_h(engine);
            // Check that the location is not occupied by a snake item before placing
            // food.
            if (!snake.SnakeCell(x, y)) {
              foodsObjs[2]->setFood(x,y);
              break;
            }
          }

          while (true) {
            x = random_w(engine);
            y = random_h(engine);
            // Check that the location is not occupied by a snake item before placing
            // food.
            if (!snake.SnakeCell(x, y)) {
              foodsObjs[3]->setFood(x,y);
              break;
            }
          }
    if( iteration+1 == 10){
      foodsObjs[1]->valid_food = 0;
      foodsObjs[2]->valid_food = 0;
      foodsObjs[3]->valid_food = 0;
    }
  }



  return;
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  if(foodsObjs[1]->valid_food == 1){

    for( int i =0;i< 4; i++){
      if (foodsObjs[i]->getFood().x == new_x && foodsObjs[i]->getFood().y == new_y) {
        score = score + foodsObjs[i]->food_score;
        PlaceFood();
        iteration++;
        // Grow snake and increase speed.
        snake.GrowBody();
        snake.speed += 0.009;
      }
    }
  }
  else{
    if (foodsObjs[0]->getFood().x == new_x && foodsObjs[0]->getFood().y == new_y) {
      score = score + foodsObjs[0]->food_score;
      PlaceFood();
      iteration++;
      // Grow snake and increase speed.
      snake.GrowBody();
      snake.speed += 0.009;
    }
  }
/*
  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    iteration++;
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.008;
  }
  */
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

void Game::handle_input_right(){
   ctrl->HandleInput_right();
}
void Game::handle_input_left(){
ctrl->HandleInput_left();
}
void Game::handle_input_up(){
  ctrl->HandleInput_up();
}
void Game::handle_input_down(){
  ctrl->HandleInput_down();
}
