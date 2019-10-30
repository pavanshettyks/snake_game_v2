//
//  Game.h - maintains all game objects
//
#ifndef _GAME_
#define _GAME_

#include "domain_layer/player/Player.hpp"
//#include "domain_layer/board/Board.hpp"
#include "domain_layer/game/GameHandler.hpp"

#define WAIT_TIME 700  // Number of milliseconds that the piece remains before going 1 block down

//
// Implements the functions exposed by the GameHandler interface.
//
namespace domain_layer::game
{
    class Game : public domain_layer::game::GameHandler
    {
        public:
            Game(domain_layer::player::Player *PlayerPtr);

            ~Game();

       /*     // Initialize game module
            void init_game()                                override;

            // Functions to get data from domain_layer.
            unsigned int get_curr_score()                   override;
            struct BoardInfo get_board_info()               override;
            std::vector<std::vector<int>> get_board_data()  override;
            struct PieceInfo get_piece_data()               override;
            struct PieceInfo get_next_piece_data()          override;

            // Functions to tell domain layer of user input.
            void move_piece_right()                         override;
            void move_piece_left()                          override;
            void move_piece_down()                          override;
            void rotate_piece()                             override;
            void process_space_key()                        override;
            void process_timeout_movement()                 override;
            bool is_game_over()                             override; */

        private:
            int mScreenHeight;
            domain_layer::player::Player* _playerData;
           // domain_layer::board::Board*   _boardData;
    };

}

#endif // _GAME_
