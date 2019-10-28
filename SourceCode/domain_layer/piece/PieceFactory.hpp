//
// PieceFactory.hpp -- Factory to generate Piece objects.
//
#ifndef __PIECE_FACTORY__
#define __PIECE_FACTORY__

#include <map>

#include "domain_layer/piece/Piece.hpp"

namespace domain_layer::piece
{
    //
    // Factory to create Piece objects.
    //
    class PieceFactory
    {
        public:
            //
            // Creates single factory instance.
            //
            static PieceFactory *Get()
            {
                static PieceFactory instance;
                return &instance;
            }

            //
            // Destructor
            //
            ~PieceFactory()
            {
                mFactoryVector.clear();
            }

            //
            // Create random piece type piece object.
            //
            Piece* CreateRandomPiece();

        private:
            PieceFactory();
            std::vector<createPieceFn> mFactoryVector;
            void Register(createPieceFn);
            int getRand(int pA, int pB)
            {
                return rand() % (pB - pA + 1) + pA;
            }
    };
}

#endif // __PIECE_FACTORY__
