// 
// Board.cpp - Board of the game. A matrix of n x m holes.
// 

#include "domain_layer/board/Board.hpp"

namespace domain_layer::board
{
    Board::Board (int pScreenHeight)
    {
        //
        // Creating piece factory object so taht it can be used to create
        // piece objects.
        //
        mPieceFactoryPtr = domain_layer::piece::PieceFactory::Get();

        //
        // Create the inital piece and the next piece to come.
        //
        piece = mPieceFactoryPtr->CreateRandomPiece();
        nextPiece = mPieceFactoryPtr->CreateRandomPiece();

        //
        // Get the start position of the piece.
        //
        posX = (BOARD_WIDTH / 2) + piece->getXInitialPosition();
        posY = piece->getYInitialPosition();

        //
        // Next position is constant as it just displayed.
        //
        nextPosX = 10;
        nextPosY = 0;

        // Get the screen height
        mScreenHeight = pScreenHeight;

        mScore = 0;

        // Init the board blocks with free positions
        initBoard();
    }

    //
    // Init the board blocks with free positions
    //
    void Board::initBoard()
    {
        for (int i = 0; i < BOARD_WIDTH; i++)
        {
            for (int j = 0; j < BOARD_HEIGHT; j++)
            {
                mBoard[i][j] = 0;
            }
        }
    }

    //
    // Returns the horizontal position (in pixels) of the block given like parameter
    //
    // Parameters:
    //  pPos:  Horizontal position of the block in the board
    //
    int Board::getXPosInPixels (int pPos)
    {
        return ( (BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) ) + (pPos * BLOCK_SIZE) );
    }

    //
    // Returns the vertical position (in pixels) of the block given like parameter
    //
    // Parameters
    //  pPos:  Horizontal position of the block in the board
    //
    int Board::getYPosInPixels (int pPos)
    {
        return ( mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT) + (pPos * BLOCK_SIZE) );
    }

    //
    // Returns the current score of the game.
    //
    unsigned int Board::getScore()
    {
        return mScore;
    }

    //
    // Reset the score to zero.
    //
    void Board::clearScore()
    {
        mScore = 0;
    }

    //
    // Returns 1 (true) if the this block of the board is empty, 0 if it is filled
    //
    // Parameters:
    //  pX:        Horizontal position in blocks
    //  pY:        Vertical position in blocks
    //
    bool Board::isFreeBlock (int pX, int pY)
    {
        return (mBoard[pX][pY] == POS_FREE);
    }

    //
    // Check if the piece can be stored at this position without any collision
    // Returns true if the movement is possible, false if it not possible
    //
    // Parameters:
    //  pX:        Horizontal position in blocks
    //  pY:        Vertical position in blocks
    //
    bool Board::isPossibleMovement (int pX, int pY)
    {
        int boardX, boardY;

        // This is just to check the 5x5 blocks of a piece with the appropriate area in the board
        for( int i = 0; i < PIECE_BLOCKS; i++)
        {
            boardX = pX + i;
            for ( int j = 0; j < PIECE_BLOCKS; j++)
            {
                boardY = pY + j;
                // Check if the piece is outside the limits of the board
                if ( boardX < 0 || boardX > BOARD_WIDTH - 1 || boardY > BOARD_HEIGHT - 1 )
                {
                    if( piece->mPiece[i][j] != 0)
                        return 0;
                }
                // Check if the piece have collisioned with a block already stored in the map
                if ( boardY >= 0)
                {
                    if ( piece->mPiece[i][j] != 0 && !isFreeBlock(boardX, boardY))
                        return false;
                }
            }
        }

        return true;
    }

    //
    // Store a piece in the board by filling the blocks
    //
    // Parameters:
    //  pX:        Horizontal position in blocks
    //  pY:        Vertical position in blocks
    //
    void Board::storePiece (int pX, int pY)
    {
        int boardX, boardY;
    
        // Store each block of the piece into the board
        for (int i = 0; i < PIECE_BLOCKS; i++)
        {
            boardX = pX + i;
            for (int j = 0; j < PIECE_BLOCKS; j++)
            {
                boardY = pY + j;
                // Store only the blocks of the piece that are not holes
                if ( piece->mPiece[i][j] != 0)
                     mBoard[boardX][boardY] = piece->getColor();
            }
        }
    }

    //
    // Delete all the lines that should be removed
    //
    void Board::deletePossibleLines ()
    {
        for (int i = 0; i < BOARD_HEIGHT; i++)
        {
            int col = 0;
            while ( col < BOARD_WIDTH )
            {
                if ( mBoard[col][i] == POS_FREE) break;
                col++;
            }
            if (col == BOARD_WIDTH) deleteLine(i);
        }
    }

    //
    // Check if the game is over becase a piece have achived the upper position
    //
    // Returns true or false
    //
    bool Board::isGameOver ()
    {
        //If the first line has blocks, then, game over
        for (int i = 0; i < BOARD_WIDTH; i++)
        {
            if (mBoard[i][0] != POS_FREE) return true;
        }

        return false;
    }

    //
    // Delete a line of the board by moving all above lines down
    //
    // Parameters:
    //  pY:        Vertical position in blocks of the line to delete
    //
    void Board::deleteLine (int pY)
    {
        // Moves all the upper lines one row down
        for (int j = pY; j > 0; j--)
        {
            for (int i = 0; i < BOARD_WIDTH; i++)
            {
                mBoard[i][j] = mBoard[i][j-1];
            }
        }
    
        mScore += ONE_LINE_SCORE;
    }

    //
    // Sets the next piece to the current piece.
    //
    void Board::updateCurrentPiece(domain_layer::piece::Piece *newPiece)
    {
        this->piece = newPiece;
    }

    //
    // Resets the board back to empty.
    //
    void Board::clearBoard()
    {
        initBoard();
    }

    //
    // Returns the type of piece stored a the given location in the board.
    //
    int Board::storedPieceType(int x, int y)
    {
        return mBoard[x][y];
    }

    //
    // Sets next piece to current piece and gets new next piece from factory.
    //
    void Board::updatePiece()
    {
        if(piece)
            delete piece;
    
        updateCurrentPiece(nextPiece);
    
        posX = (BOARD_WIDTH / 2) + piece->getXInitialPosition();
        posY = piece->getYInitialPosition();
    
        nextPiece = mPieceFactoryPtr->CreateRandomPiece();
    }

    //
    // This function return current board configuration.
    //
    std::vector<std::vector<int>> Board::get_board_data()
    {
        std::vector<std::vector<int>> bData(BOARD_WIDTH);

        for(int i = 0; i < BOARD_WIDTH; i++)
        {
            bData[i] = std::vector<int>(BOARD_HEIGHT);
            for(int j = 0; j < BOARD_HEIGHT; j++)
                bData[i][j] = this->mBoard[i][j];
        }

        return bData;
    }
}
