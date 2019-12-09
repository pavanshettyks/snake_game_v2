#ifndef CONTROLLER_H
#define CONTROLLER_H

//#include "ui_layer/view/snake.h"
#include "domain_layer/snake/Snake.hpp"

namespace ui_layer::controller
{

	class Controller {
 	public:
		//new
  	void HandleInput(bool &running, Snake &snake) const;
		void HandleInput_right() const;
		void HandleInput_left() const;
		void HandleInput_up() const;
		void HandleInput_down() const;

 	private:
  	void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;

	};
}
#endif
