//
//  View.hpp - Class for handling drawing, it uses SDL2 for the rendering.
//
#ifndef _VIEW_
#define _VIEW_

#include "domain_layer/food/Food.hpp"
#include "domain_layer/food/FoodFactory.hpp"


#include <iostream>
#include "domain_layer/game/Game.hpp"
#include "domain_layer/play_zone/PlayZone.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include "termcolor.hpp"
#ifdef WINDOWS
    #include "ui_layer/sdl/include/windows/SDL.h"
    #include "ui_layer/sdl/include/windows/SDL2_gfxPrimitives.h"
    #include "ui_layer/sdl/include/windows/SDL_ttf.h"
#else
    #include "ui_layer/sdl/include/linux/SDL.h"
    #include "ui_layer/sdl/include/linux/SDL2_gfxPrimitives.h"
    #include "ui_layer/sdl/include/linux/SDL_ttf.h"
#endif

#include "ui_layer/view/ViewHandler.hpp"
//#include "ui_layer/commands/Commands.hpp"
#include "ui_layer/controller/Controller.hpp"
//#include "domain_layer/game/GameHandler.hpp"
#include "domain_layer/player/PlayerHandler.hpp"
#include "technical_services_layer/Payment/CreditCard.hpp"
#include "technical_services_layer/Logger/LoggerHandler.hpp"
#include "technical_services_layer/Persistence/PersistenceHandler.hpp"

namespace ui_layer::view
{
    //
    // Colors
    //
    enum color { ZERO, BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, COLOR_MAX };

    //
    // Implements the function of ViewHandler interface.
    // Also implements function to display ui related data.
    //
    class View : public ui_layer::view::ViewHandler
    {
        public:
            View();

            // Operations
            void launch() override;

            // Destructor
            ~View() override;

        private:


            // Drawing related functions.
             void init_SDL();
            int messageBox();
            void cleanup_SDL();
            void showScore(unsigned int );

            void clearScreen();
           // void drawBlock(int pX1, int pY1, int pX2, int pY2, enum color pC);

               // Menu related functions.
            bool initialize_system();
            bool display_main_menu();
            bool display_user_menu();
            void register_player();
            bool login_user();

            // Functions to display player related data.
            void play_game();
            bool check_player_status();
            void buy_premium();
            void view_previous_score();
            void view_leaderboard();
            void view_gameHelp();



            int mScreenHeight = 0;

            // These smart pointers hold pointers to lower architectural layer's interfaces
            ui_layer::controller::Controller*                           _control;
            domain_layer::player::PlayerHandler*                       _playerData;
            //domain_layer::game::GameHandler*                           _gameData;
            technical_services_layer::Persistence::PersistenceHandler* _persistentData;
            technical_services_layer::payment::CreditCardFactory*      _ccFactory;
            technical_services_layer::Logging::LoggerHandler*          _loggerPtr;

            technical_services_layer::Logging::LoggerHandler & _logger = *_loggerPtr;
     };
}

#endif // _VIEW_
