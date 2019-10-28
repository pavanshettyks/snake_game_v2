//
// Game.cpp - Logic of the game
//

#include "domain_layer/game/Game.hpp"

namespace domain_layer::game
{
    //
    // Constructor
    //
    Game::Game(domain_layer::player::Player *PlayerPtr, int screenHeight)
    {
        _playerData = PlayerPtr;
        _boardData = NULL;
        mScreenHeight = screenHeight;
    }

    //
    // Destructor
    //
    Game::~Game()
    {

    }

    //
    // Creates the board object.
    //
    void Game::init_game()
    {
        // initialize board
        _boardData = new domain_layer::board::Board(mScreenHeight);
    }

    //
    // Returns the current score to be displayed.
    //
    unsigned int Game::get_curr_score()
    {
        return _boardData->getScore();
    }

    //
    // Returns the board information need to display.
    //
    struct BoardInfo Game::get_board_info()
    {
        struct BoardInfo bInfo;

        bInfo.board_line_width      = BOARD_LINE_WIDTH;
        bInfo.block_size            = BLOCK_SIZE;
        bInfo.board_position        = BOARD_POSITION;
        bInfo.board_width           = BOARD_WIDTH;
        bInfo.board_height          = BOARD_HEIGHT;
        bInfo.min_vertical_margin   = MIN_VERTICAL_MARGIN;
        bInfo.min_horizontal_margin = MIN_HORIZONTAL_MARGIN;
        bInfo.piece_block           = PIECE_BLOCKS;

        return bInfo;
    }

    //
    // Returns the current board configuration to be displayed.
    //
    std::vector<std::vector<int>> Game::get_board_data()
    {
        return _boardData->get_board_data();
    }

    //
    // Returns the playing piece configuration to be displayed.
    //
    struct PieceInfo Game::get_piece_data()
    {
        struct PieceInfo pInfo;
        pInfo.piece_layout = new std::vector<std::vector<int>>(PIECE_BLOCKS);

        for(int i = 0; i < PIECE_BLOCKS; i++)
        {
            (*(pInfo.piece_layout))[i] = std::vector<int>(PIECE_BLOCKS);
            for(int j = 0; j < PIECE_BLOCKS; j++)
              (*(pInfo.piece_layout))[i][j] = _boardData->piece->mPiece[i][j];
        }

        pInfo.piece_color = _boardData->piece->getColor();
        pInfo.draw_posX = _boardData->getXPosInPixels(_boardData->posX);
        pInfo.draw_posY = _boardData->getYPosInPixels(_boardData->posY);

        return pInfo;
    }

    //
    // Returns next piece's configuration to be displayed.
    //
    struct PieceInfo Game::get_next_piece_data()
    {
        struct PieceInfo pInfo;
        pInfo.piece_layout = new std::vector<std::vector<int>>(PIECE_BLOCKS);

        for (int i = 0; i < PIECE_BLOCKS; i++)
        {
            (*(pInfo.piece_layout))[i] = std::vector<int>(PIECE_BLOCKS);
            for (int j = 0; j < PIECE_BLOCKS; j++)
                (*(pInfo.piece_layout))[i][j] = _boardData->nextPiece->mPiece[i][j];
        }

        pInfo.piece_color = _boardData->nextPiece->getColor();
        pInfo.draw_posX = _boardData->getXPosInPixels(_boardData->nextPosX);
        pInfo.draw_posY = _boardData->getYPosInPixels(_boardData->nextPosY);

        return pInfo;
    }

    //
    // Handles the logic when player press right arrow key.
    //
    void Game::move_piece_right()
    {
        if (_boardData->isPossibleMovement(_boardData->posX + 1, _boardData->posY))
        {
            _boardData->posX++;
        }
    }

    //
    // Handles the logic when player press left arrow key.
    //
    void Game::move_piece_left()
    {
        if (_boardData->isPossibleMovement(_boardData->posX - 1, _boardData->posY))
        {
            _boardData->posX--;
        }
    }

    //
    // Handles the logic when player press down arrow key.
    //
    void Game::move_piece_down()
    {
        if (_boardData->isPossibleMovement(_boardData->posX, _boardData->posY + 1))
        {
            _boardData->posY++;
        }
    }

    //
    // Handles the logic when player press up arrow key.
    //
    void Game::rotate_piece()
    {
        _boardData->piece->rotatePiece();
        if (!_boardData->isPossibleMovement(_boardData->posX, _boardData->posY))
        {
            _boardData->piece->rotatePiece(3);
        }
    }

    //
    // Handles the logic when player press space key.
    //
    void Game::process_space_key()
    {
        // check collision from up to the possible bottom
        while (_boardData->isPossibleMovement(_boardData->posX, _boardData->posY))
        {
            _boardData->posY++;
        }

        _boardData->storePiece(_boardData->posX, _boardData->posY - 1);
        _boardData->deletePossibleLines();

        _boardData->updatePiece();
    }

    //
    // Checks if the game is over or not, if over then updates the player max score.
    //
    bool Game::is_game_over()
    {
        bool ret;
        ret = _boardData->isGameOver();
        if (ret == true)
        {
            _playerData->set_max_score(_boardData->getScore());
        }

        return ret;
    }

    //
    // Handles the logic if the user does not press any key within the time.
    // Automatic piece moving down logic.
    //
    void Game::process_timeout_movement()
    {
        if(_boardData->isPossibleMovement(_boardData->posX, _boardData->posY+1))
        {
            _boardData->posY++;
        }
        else
        {
            _boardData->storePiece(_boardData->posX, _boardData->posY);
            _boardData->deletePossibleLines();
            _boardData->updatePiece();
        }  
    }
}
