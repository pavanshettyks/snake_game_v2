//helps to create the zone in which snake  and food will be present

#include "PlayZone.hpp"
#include <iostream>
#include <string>
#include <random>

PlayZone::PlayZone(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);
  mFoodFactoryPtr = domain_layer::food::FoodFactory::Get();
  foods = mFoodFactoryPtr->CreateRandomFood();
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

PlayZone::~PlayZone() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void PlayZone::Render(Snake const snake,  domain_layer::food::Food  *(foodsObjs[4])) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;
  //std::cout<<"inside the render method"<<foodsObjs[0]->food_score<<std::endl;
  //int x = foodsObjs[0]->food_score;
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);


  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, foodsObjs[0]->getColor(), 0x00, 0xFF); //yellow 0xCC
  block.x = foodsObjs[0]->getFood().x * block.w;
  block.y = foodsObjs[0]->getFood().y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render 3 new foods
  if(foodsObjs[1]->valid_food == 1){

   for(int i =1; i<4; i++){
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, foodsObjs[i]->getColor(), 0x00, 0xFF); //yellow 0xCC
    block.x = foodsObjs[i]->getFood().x * block.w;
    block.y = foodsObjs[i]->getFood().y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
 }
  /*  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x10, 0x91, 0xFF); // pink
    block.x = foodsObjs[1]->getFood().x * block.w;
    block.y = foodsObjs[1]->getFood().y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);

    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x27, 0x00, 0xFF);  //red
    block.x = foodsObjs[2]->getFood().x * block.w;
    block.y = foodsObjs[2]->getFood().y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
*/
  }



  // Render food orange color
/*  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x7A, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
*/
  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;

  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void PlayZone::PlaceFood(Snake snake, SDL_Point food) {
  int x, y;
std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
std::random_device dev;
  std::mt19937 engine;
  while (true) {

     x = random_w(engine);
    y = random_h(engine);

    // Check that the location is not occupied by a snake item before placing it in placeZone
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      x= food.x;
      return;
   }
  }
}


void PlayZone::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
