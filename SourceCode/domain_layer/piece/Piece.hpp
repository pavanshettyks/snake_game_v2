//
// Piece.hpp - Maintains the piece array
//
#ifndef _PIECE_
#define _PIECE_

#include <vector>
#include <iostream>

#define SIZE 5

namespace domain_layer::piece
{
    //
    // Piece types
    //
    enum { _ZERO, _I, _L, _Lm, _N, _Nm, _S, _T };

    //
    // Piece base class.
    //
    class Piece
    {
        public:
            Piece()
            {
                for(int i = 0; i < 5; i++)
                    for(int j = 0; j < 5; j++)
                        mPiece[i][j] = 0;
            }

            virtual ~Piece() noexcept {}

            virtual int getXInitialPosition() = 0;
            virtual int getYInitialPosition() = 0;
            virtual void rotatePiece(int pieceRotation = 1) = 0; // Rotates Piece array
            virtual int getColor() = 0;

            int mPiece [5][5];     // Piece array
    };

    //
    // create function prototype.
    //
    typedef Piece* (*createPieceFn)(int);

    //
    // Piece I class derived from Piece base class.
    //
    class Piece_I: public Piece
    {
        public:
            Piece_I(int rotation); // Constructor
            ~Piece_I() = default;

            int getXInitialPosition()               override;
            int getYInitialPosition()               override;
            void rotatePiece(int pieceRotation = 1) override;
            int getColor()                          override;

            static Piece* Create(int rotation)
            {
                return new Piece_I(rotation);
            }
    };

    //
    // Piece L class derived from Piece base class.
    //
    class Piece_L : public Piece
    {
    public:
        Piece_L(int rotation); // Constructor
        ~Piece_L() = default;

        int getXInitialPosition()               override;
        int getYInitialPosition()               override;
        void rotatePiece(int pieceRotation = 1) override;
        int getColor()                          override;

        static Piece* Create(int rotation)
        {
            return new Piece_L(rotation);
        }
    };

    //
    // Piece Lm class derived from Piece base class.
    //
    class Piece_Lm : public Piece
    {
    public:
        Piece_Lm(int rotation); // Constructor
        ~Piece_Lm() = default;

        int getXInitialPosition()               override;
        int getYInitialPosition()               override;
        void rotatePiece(int pieceRotation = 1) override;
        int getColor()                          override;

        static Piece* Create(int rotation)
        {
            return new Piece_Lm(rotation);
        }
    };

    //
    // Piece N class derived from Piece base class.
    //
    class Piece_N : public Piece
    {
    public:
        Piece_N(int rotation); // Constructor
        ~Piece_N() = default;

        int getXInitialPosition()               override;
        int getYInitialPosition()               override;
        void rotatePiece(int pieceRotation = 1) override;
        int getColor()                          override;

        static Piece* Create(int rotation)
        {
            return new Piece_N(rotation);
        }
    };

    //
    // Piece Nm class derived from Piece base class.
    //
    class Piece_Nm : public Piece
    {
    public:
        Piece_Nm(int rotation); // Constructor
        ~Piece_Nm() = default;

        int getXInitialPosition()               override;
        int getYInitialPosition()               override;
        void rotatePiece(int pieceRotation = 1) override;
        int getColor()                          override;

        static Piece* Create(int rotation)
        {
            return new Piece_Nm(rotation);
        }
    };

    //
    // Piece S class derived from Piece base class.
    //
    class Piece_S : public Piece
    {
    public:
        Piece_S(int rotation); // Constructor
        ~Piece_S() = default;

        int getXInitialPosition()               override;
        int getYInitialPosition()               override;
        void rotatePiece(int pieceRotation = 1) override;
        int getColor()                          override;

        static Piece* Create(int rotation)
        {
            return new Piece_S(rotation);
        }
    };

    //
    // Piece T class derived from Piece base class.
    //
    class Piece_T : public Piece
    {
    public:
        Piece_T(int rotation); // Constructor
        ~Piece_T() = default;

        int getXInitialPosition()               override;
        int getYInitialPosition()               override;
        void rotatePiece(int pieceRotation = 1) override;
        int getColor()                          override;

        static Piece* Create(int rotation)
        {
            return new Piece_T(rotation);
        }
    };
}

#endif // _piece_
