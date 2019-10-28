//
//  Piece.cpp - creates a piece array given a type and rotation
//

#include "domain_layer/piece/Piece.hpp"

namespace domain_layer::piece
{
    //
    // Piece_I functions.
    //
    Piece_I::Piece_I(int pieceRotation)
    {
        int IPiece[5][5] = {
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0}
        };

        std::copy(&IPiece[0][0], &IPiece[0][0] + 25, &mPiece[0][0]);
        rotatePiece(pieceRotation);
    }

    int Piece_I::getColor()
    {
        return _I;
    }

    void Piece_I::rotatePiece(int pieceRotation)
    {
        int count = 0;
        while (count < pieceRotation)
        {
            for (int i = 0; i < SIZE - 1; i++)
            {
                for (int j = i; j < SIZE - i - 1; j++)
                {
                    int temp = mPiece[i][j];
                    mPiece[i][j] = mPiece[SIZE - j - 1][i];
                    mPiece[SIZE - j - 1][i] = mPiece[SIZE - i - 1][SIZE - j - 1];
                    mPiece[SIZE - i - 1][SIZE - j - 1] = mPiece[j][SIZE - i - 1];
                    mPiece[j][SIZE - i - 1] = temp;
                }
            }
            count++;
        }
    }

    int Piece_I::getXInitialPosition()
    {
        return -2;
    }

    int Piece_I::getYInitialPosition()
    {
        //check bottom half of the Piece array
        for (int i = 0; i < SIZE; i++)
        {
            if (mPiece[3][i] == 1)
            {
                return -3;
            }

            if (mPiece[4][i] == 1)
            {
                return -4;
            }
        }

        return -2;
    }


    //
    // Piece_L functions.
    //
    Piece_L::Piece_L(int pieceRotation)
    {
        int IPiece[5][5] = {
                {0, 0, 0, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 1, 1, 0},
                {0, 0, 0, 0, 0}
        };

        std::copy(&IPiece[0][0], &IPiece[0][0] + 25, &mPiece[0][0]);
        rotatePiece(pieceRotation);
    }

    int Piece_L::getColor()
    {
        return _L;
    }

    void Piece_L::rotatePiece(int pieceRotation)
    {
        int count = 0;
        while (count < pieceRotation)
        {
            for (int i = 0; i < SIZE - 1; i++)
            {
                for (int j = i; j < SIZE - i - 1; j++)
                {
                    int temp = mPiece[i][j];
                    mPiece[i][j] = mPiece[SIZE - j - 1][i];
                    mPiece[SIZE - j - 1][i] = mPiece[SIZE - i - 1][SIZE - j - 1];
                    mPiece[SIZE - i - 1][SIZE - j - 1] = mPiece[j][SIZE - i - 1];
                    mPiece[j][SIZE - i - 1] = temp;
                }
            }
            count++;
        }
    }

    int Piece_L::getXInitialPosition()
    {
        return -2;
    }

    int Piece_L::getYInitialPosition()
    {
        //check bottom half of the Piece array
        for (int i = 0; i < SIZE; i++)
        {
            if (mPiece[3][i] == 1)
            {
                return -3;
            }

            if (mPiece[4][i] == 1)
            {
                return -4;
            }
        }

        return -2;
    }


    //
    // Piece_Lm functions.
    //
    Piece_Lm::Piece_Lm(int pieceRotation)
    {
        int IPiece[5][5] = {
                {0, 0, 0, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 1, 1, 0, 0},
                {0, 0, 0, 0, 0}
        };

        std::copy(&IPiece[0][0], &IPiece[0][0] + 25, &mPiece[0][0]);
        rotatePiece(pieceRotation);
    }

    int Piece_Lm::getColor()
    {
        return _Lm;
    }

    void Piece_Lm::rotatePiece(int pieceRotation)
    {
        int count = 0;
        while (count < pieceRotation)
        {
            for (int i = 0; i < SIZE - 1; i++)
            {
                for (int j = i; j < SIZE - i - 1; j++)
                {
                    int temp = mPiece[i][j];
                    mPiece[i][j] = mPiece[SIZE - j - 1][i];
                    mPiece[SIZE - j - 1][i] = mPiece[SIZE - i - 1][SIZE - j - 1];
                    mPiece[SIZE - i - 1][SIZE - j - 1] = mPiece[j][SIZE - i - 1];
                    mPiece[j][SIZE - i - 1] = temp;
                }
            }
            count++;
        }
    }

    int Piece_Lm::getXInitialPosition()
    {
        return -2;
    }

    int Piece_Lm::getYInitialPosition()
    {
        //check bottom half of the Piece array
        for (int i = 0; i < SIZE; i++)
        {
            if (mPiece[3][i] == 1)
            {
                return -3;
            }

            if (mPiece[4][i] == 1)
            {
                return -4;
            }
        }

        return -2;
    }


    //
    // Piece_N functions.
    //
    Piece_N::Piece_N(int pieceRotation)
    {
        int IPiece[5][5] = {
                {0, 0, 0, 0, 0},
                {0, 0, 0, 1, 0},
                {0, 0, 1, 1, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0}
        };

        std::copy(&IPiece[0][0], &IPiece[0][0] + 25, &mPiece[0][0]);
        rotatePiece(pieceRotation);
    }

    int Piece_N::getColor()
    {
        return _N;
    }

    void Piece_N::rotatePiece(int pieceRotation)
    {
        int count = 0;
        while (count < pieceRotation)
        {
            for (int i = 0; i < SIZE - 1; i++)
            {
                for (int j = i; j < SIZE - i - 1; j++)
                {
                    int temp = mPiece[i][j];
                    mPiece[i][j] = mPiece[SIZE - j - 1][i];
                    mPiece[SIZE - j - 1][i] = mPiece[SIZE - i - 1][SIZE - j - 1];
                    mPiece[SIZE - i - 1][SIZE - j - 1] = mPiece[j][SIZE - i - 1];
                    mPiece[j][SIZE - i - 1] = temp;
                }
            }
            count++;
        }
    }

    int Piece_N::getXInitialPosition()
    {
        return -2;
    }

    int Piece_N::getYInitialPosition()
    {
        //check bottom half of the Piece array
        for (int i = 0; i < SIZE; i++)
        {
            if (mPiece[3][i] == 1)
            {
                return -3;
            }

            if (mPiece[4][i] == 1)
            {
                return -4;
            }
        }

        return -2;
    }


    //
    // Piece_Nm functions.
    //
    Piece_Nm::Piece_Nm(int pieceRotation)
    {
        int IPiece[5][5] = {
                {0, 0, 0, 0, 0},
                {0, 1, 0, 0, 0},
                {0 ,1, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0}
        };

        std::copy(&IPiece[0][0], &IPiece[0][0] + 25, &mPiece[0][0]);
        rotatePiece(pieceRotation);
    }

    int Piece_Nm::getColor()
    {
        return _Nm;
    }

    void Piece_Nm::rotatePiece(int pieceRotation)
    {
        int count = 0;
        while (count < pieceRotation)
        {
            for (int i = 0; i < SIZE - 1; i++)
            {
                for (int j = i; j < SIZE - i - 1; j++)
                {
                    int temp = mPiece[i][j];
                    mPiece[i][j] = mPiece[SIZE - j - 1][i];
                    mPiece[SIZE - j - 1][i] = mPiece[SIZE - i - 1][SIZE - j - 1];
                    mPiece[SIZE - i - 1][SIZE - j - 1] = mPiece[j][SIZE - i - 1];
                    mPiece[j][SIZE - i - 1] = temp;
                }
            }
            count++;
        }
    }

    int Piece_Nm::getXInitialPosition()
    {
        return -2;
    }

    int Piece_Nm::getYInitialPosition()
    {
        //check bottom half of the Piece array
        for (int i = 0; i < SIZE; i++)
        {
            if (mPiece[3][i] == 1)
            {
                return -3;
            }

            if (mPiece[4][i] == 1)
            {
                return -4;
            }
        }

        return -2;
    }


    //
    // Piece_S functions.
    //
    Piece_S::Piece_S(int pieceRotation)
    {
        int IPiece[5][5] = {
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 1, 1, 0},
                {0, 0, 1, 1, 0},
                {0, 0, 0, 0, 0}
        };

        std::copy(&IPiece[0][0], &IPiece[0][0] + 25, &mPiece[0][0]);
        rotatePiece(pieceRotation);
    }

    int Piece_S::getColor()
    {
        return _S;
    }

    void Piece_S::rotatePiece(int pieceRotation)
    {
        int count = 0;
        while (count < pieceRotation)
        {
            for (int i = 0; i < SIZE - 1; i++)
            {
                for (int j = i; j < SIZE - i - 1; j++)
                {
                    int temp = mPiece[i][j];
                    mPiece[i][j] = mPiece[SIZE - j - 1][i];
                    mPiece[SIZE - j - 1][i] = mPiece[SIZE - i - 1][SIZE - j - 1];
                    mPiece[SIZE - i - 1][SIZE - j - 1] = mPiece[j][SIZE - i - 1];
                    mPiece[j][SIZE - i - 1] = temp;
                }
            }
            count++;
        }
    }

    int Piece_S::getXInitialPosition()
    {
        return -2;
    }

    int Piece_S::getYInitialPosition()
    {
        //check bottom half of the Piece array
        for (int i = 0; i < SIZE; i++)
        {
            if (mPiece[3][i] == 1)
            {
                return -3;
            }

            if (mPiece[4][i] == 1)
            {
                return -4;
            }
        }

        return -2;
    }


    //
    // Piece_T functions.
    //
    Piece_T::Piece_T(int pieceRotation)
    {
        int IPiece[5][5] = {
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 1, 1, 1, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0}
        };

        std::copy(&IPiece[0][0], &IPiece[0][0] + 25, &mPiece[0][0]);
        rotatePiece(pieceRotation);
    }

    int Piece_T::getColor()
    {
        return _T;
    }

    void Piece_T::rotatePiece(int pieceRotation)
    {
        int count = 0;
        while(count < pieceRotation )
        {
            for (int i = 0; i < SIZE - 1; i++)
            {
                for (int j = i; j < SIZE - i - 1; j++)
                {
                    int temp                           = mPiece[i][j];
                    mPiece[i][j]                       = mPiece[SIZE - j - 1][i];
                    mPiece[SIZE - j - 1][i]            = mPiece[SIZE - i - 1][SIZE - j - 1];
                    mPiece[SIZE - i - 1][SIZE - j - 1] = mPiece[j][SIZE - i - 1];
                    mPiece[j][SIZE - i - 1]            = temp;
                }
            }
            count++;
        }
    }
    
    int Piece_T::getXInitialPosition ()
    {
        return -2;
    }
    
    int Piece_T::getYInitialPosition ()
    {
        //check bottom half of the Piece array
        for ( int i = 0; i < SIZE; i++ )
        {
            if (mPiece[3][i] == 1)
            {
                return -3;
            }
    
            if (mPiece[4][i] == 1)
            {
                return -4;
            }
        }
    
        return -2;
    }
}
