//
// PieceFactory.cpp -- Manages the creation of the piece objects.
//

#include <time.h>

#include "domain_layer/piece/PieceFactory.hpp"

namespace domain_layer::piece
{
    //
    // Constructor
    // Registers all the pieces that this factory could produce.
    //
    PieceFactory::PieceFactory()
    {
        srand(static_cast<unsigned int>(time(NULL)));

        Register(&Piece_I::Create);
        Register(&Piece_L::Create);
        Register(&Piece_Lm::Create);
        Register(&Piece_N::Create);
        Register(&Piece_Nm::Create);
        Register(&Piece_S::Create);
        Register(&Piece_T::Create);
    }

    //
    // Stores the create function of the piece in the vector.
    //
    void PieceFactory::Register(createPieceFn pfn)
    {
        mFactoryVector.push_back(pfn);
    }

    //
    // Static function to create the random piece when requested.
    //
    Piece* PieceFactory::CreateRandomPiece()
    {
        int numPieces = static_cast<int>(mFactoryVector.size());
        int index = getRand(0, numPieces-1);
        int pieceRotation = getRand(1,3);

        return (mFactoryVector[index])(pieceRotation);
    }
}
