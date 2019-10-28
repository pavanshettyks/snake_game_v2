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
        unsigned int board_line_width;
        unsigned int block_size;
        unsigned int board_position;
        unsigned int board_width;
        unsigned int board_height;
        unsigned int min_vertical_margin;
        unsigned int min_horizontal_margin;
        unsigned int piece_block;
    };

    //
    // Infomarmation regarding each piece need to display them.
    //
    struct PieceInfo
    {
        int piece_color;
        std::vector<std::vector<int>> *piece_layout;
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

            // Initialize game module
            virtual void init_game()                                = 0;

            // Functions to get data from domain_layer.
            virtual unsigned int get_curr_score()                   = 0;
            virtual struct BoardInfo get_board_info()               = 0;
            virtual std::vector<std::vector<int>> get_board_data()  = 0;
            virtual struct PieceInfo get_piece_data()               = 0;
            virtual struct PieceInfo get_next_piece_data()          = 0;

            // Functions to tell domain layer of user input
            virtual void move_piece_right()                         = 0;
            virtual void move_piece_left()                          = 0;
            virtual void move_piece_down()                          = 0;
            virtual void rotate_piece()                             = 0;
            virtual void process_space_key()                        = 0;
            virtual void process_timeout_movement()                 = 0;
            virtual bool is_game_over()                             = 0;
    };

    inline GameHandler::~GameHandler() noexcept
    {
    }
}

#endif // __GAME_HANDLER__
