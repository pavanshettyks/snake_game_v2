//
// GameHandler.hpp -- Interface between view and game.a
//
#ifndef __GAME_HANDLER__
#define __GAME_HANDLER__

#include <string>
#include <vector>

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

            // Functions to get data from domain_layer.
            virtual unsigned int get_curr_score()                   = 0;
            virtual struct BoardInfo get_play_zone_info()               = 0;
	    virtual struct SnakeInfo get_snake_info()               = 0;
	    virtual struct FoodInfo get_food_info()               = 0;
            virtual std::vector<std::vector<int>> get_play_zone_data()  = 0;
            virtual void process_timeout_movement()                 = 0;
         
    };

    inline GameHandler::~GameHandler() noexcept
    {
    }
}

#endif // __GAME_HANDLER__
