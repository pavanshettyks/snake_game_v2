//
// FoodFactory.cpp -- Manages the creation of the food objects.
//

#include <time.h>

#include "domain_layer/food/FoodFactory.hpp"

namespace domain_layer::food
{
    //
    // Constructor
    // Registers all the foods that this factory could produce.
    //
    FoodFactory::FoodFactory()
    {
        srand(static_cast<unsigned int>(time(NULL)));

        count = 0;


        Register(&Food_A::Create);
        Register(&Food_N::Create);
        Register(&Food_E::Create);
        Register(&Food_C::Create);




    }

    //
    // Stores the create function of the food in the vector.
    //
    void FoodFactory::Register(createFoodFn pfn)
    {
        mFactoryVector.push_back(pfn);
    }

    //
    // Static function to create the random Food when requested.
    //
    Food* FoodFactory::CreateRandomFood()
    {
        //std::cout<<"dhgdsbhdhbs"<<std::endl;
        int numFoods = static_cast<int>(mFactoryVector.size());
        //int index = getRand(0, numFoods-1);
        if (count == numFoods){
          count = 0;
        }
        //int pieceRotation = getRand(1,3);
        return mFactoryVector[count++]();
    }
}
