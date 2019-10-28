//
// Board.hpp - Maintains the board array
//
#ifndef _BOARD_
#define _BOARD_

#include <time.h>
#include <vector>

#include "domain_layer/piece/Piece.hpp"
#include "domain_layer/piece/PieceFactory.hpp"

//
// Maintains and manages the board and pieces.
//
namespace domain_layer::board
{
    #define BOARD_LINE_WIDTH        6   // Width of each of the two lines that delimit the board
    #define BLOCK_SIZE              20  // Width and Height of each block of a piece
    #define BOARD_POSITION          512 // Center position of the board from the left of the screen
    #define BOARD_WIDTH             10  // Board width in blocks
    #define BOARD_HEIGHT            20  // Board height in blocks
    #define MIN_VERTICAL_MARGIN     20  // Minimum vertical margin for the board limit
    #define MIN_HORIZONTAL_MARGIN   20  // Minimum horizontal margin for the board limit
    #define PIECE_BLOCKS            5   // Number of horizontal and vertical blocks of a matrix piece
    #define ONE_LINE_SCORE          300 // Score added for each line deleted.

    class Board
    {
        public:
            Board(int pScreenHeight);

            int getXPosInPixels         (int pPos);       // given block position return position in pixel
            int getYPosInPixels         (int pPos);       // given block position return position in pixel
            unsigned int getScore       ();               // return score
            void clearScore             ();               // resets the score
            bool isFreeBlock            (int pX, int pY); //a block in the board

            bool isPossibleMovement     (int pX, int pY); // checks collisions
            void storePiece             (int pX, int pY); // fills an unfilled block in board
            void deletePossibleLines    ();               // delete line is filled
            bool isGameOver             ();               // checks if game over
            void updateCurrentPiece     (domain_layer::piece::Piece * newPiece); // updates current piece
            void clearBoard             ();               // resets the board
            int storedPieceType         (int x, int y);   //used to differenciate while coloring
            void updatePiece();
            std::vector<std::vector<int>> get_board_data();
            domain_layer::piece::Piece *nextPiece;
            domain_layer::piece::Piece *piece;
            int posX, posY;
            int nextPosX, nextPosY;

        private:

            enum { POS_FREE, POS_FILLED };          // POS_FREE = free position of the board;
                                                    // POS_FILLED = filled position of the board
            int mBoard [BOARD_WIDTH][BOARD_HEIGHT]; // Board that contains the Piece
            int mScreenHeight;                      // height of the screen
            unsigned int mScore;                    // score

            void initBoard();
            void deleteLine (int pY);

            domain_layer::piece::PieceFactory *mPieceFactoryPtr; // Piece factory pointer
    };
}

#endif // _BOARD_
