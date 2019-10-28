//
// main.cpp -- application starts from here.
//

#ifdef WINDOWS
    #include <stdlib.h>
#endif

#include <limits>
#include "ui_layer/view/ViewHandler.hpp"
#include "ui_layer/view/View.hpp"

#define UNUSED(x) (void)(x)

//
// main function which starts the game.
//
#ifdef __cplusplus
  extern "C"
#endif
int main (int argc, char** argv)
{
    UNUSED(argc);
    UNUSED(argv);

    // create the viewhandler object.
    ui_layer::view::ViewHandler *userInterface = new ui_layer::view::View;

    // launch the ui.
    userInterface->launch();

    return 0;
}
