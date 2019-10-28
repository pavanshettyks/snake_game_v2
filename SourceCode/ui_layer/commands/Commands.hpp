//
// Commands.h - Class that handles inputs (keyboard inputs)
//
#ifndef _COMMANDS_
#define _COMMANDS_

#ifdef WINDOWS
    #include "ui_layer/sdl/include/windows/SDL.h"
#else
    #include "ui_layer/sdl/include/linux/SDL.h"
#endif

#include <stdlib.h>

namespace ui_layer::commands
{
    class Commands
    {
        public:
            int pollkey(SDL_Event *e);
            int isKeyDown(int pKey);
    };
}

#endif // _COMMANDS_
