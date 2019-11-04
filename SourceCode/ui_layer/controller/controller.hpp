#ifndef CONTROLLER_H
#define CONTROLLER_H

//#include "ui_layer/view/snake.h"
#include "domain_layer/snake/snake.h"

namespace ui_layer::controller
{

	class Controller {
 	public:
  	void HandleInput(bool &running, Snake &snake) const;

 	private:
  	void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
	};
}
#endif