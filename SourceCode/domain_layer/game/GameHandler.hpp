//
// GameHandler.hpp -- Interface between view and game.a
//
#ifndef __GAME_HANDLER__
#define __GAME_HANDLER__

#include <string>
#include <vector>
#include "ui_layer/controller/Controller.hpp"
#include "domain_layer/play_zone/PlayZone.hpp"

namespace domain_layer::game
{
    //
    // Static information about the board to display board and pieces.
    //
    struct BoardInfo
    {
        unsigned int play_zone_line_width;
        unsigned int block_size;
        unsigned int play_zone_position;
        unsigned int play_zone_width;
        unsigned int play_zone_height;
        unsigned int min_vertical_margin;
        unsigned int min_horizontal_margin;
        unsigned int piece_block;
    };

    //
    // Infomarmation regarding snake to display them.
    //
    struct SnakeInfo
    {
        int snake_color;
        std::vector<std::vector<int>> *layout;
        int draw_posX;
        int draw_posY;
    };

    struct FoodInfo
    {
        int food_color;
        int draw_posX;
        int draw_posY;
    };

    //
    // Interface used by the View class to call the game class for the data.
    //
    class GameHandler
    {
        public:
            GameHandler() {};
            virtual ~GameHandler() noexcept = 0;
            virtual int GetScore() const =0;
            virtual int GetSize() const =0;
            virtual void Run(ui_layer::controller::Controller* const &controller, PlayZone &playzone,
                     std::size_t target_frame_duration) = 0;
            // Functions to get data from domain_layer.
            virtual void handle_input_right()                   = 0;
            virtual void handle_input_left()                   = 0;
            virtual void handle_input_up()                   = 0;
            virtual void handle_input_down()                   = 0; 
          //  virtual std::vector<std::vector<int>> get_play_zone_data()  = 0;

            };

    inline GameHandler::~GameHandler() noexcept
    {
    }
}

#endif // __GAME_HANDLER__
