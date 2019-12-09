#include "Controller.hpp"
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
#include "domain_layer/snake/Snake.hpp"

namespace ui_layer::controller
{

	void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
 	 if (snake.direction != opposite || snake.size == 1) snake.direction = input;
 		 return;
	}

	void Controller::HandleInput(bool &running, Snake &snake) const {
  	SDL_Event e;
  	while (SDL_PollEvent(&e)) {
    	if (e.type == SDL_QUIT) {
      	running = false;
    	} else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
      }
    }
  }
}


/// remove this once generic code is working
//

void Controller::HandleInput_right() const{
  //ChangeDirection(snake, Snake::Direction::kRight,
    //              Snake::Direction::kLeft);
      //            snake.direction = Snake::Direction::kLeft;
}
void Controller::HandleInput_left() const{
  //ChangeDirection(snake, Snake::Direction::kLeft,
    //              Snake::Direction::kRight);

}
void Controller::HandleInput_up() const{
  //ChangeDirection(snake, Snake::Direction::kUp,
    //              Snake::Direction::kDown);

}
void Controller::HandleInput_down() const{
  //ChangeDirection(snake, Snake::Direction::kDown,
    //              Snake::Direction::kUp);
}


}
