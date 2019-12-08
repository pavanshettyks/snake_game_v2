//
// FoodFactory.hpp -- Factory to generate Food objects.
//
#ifndef __FOOD_FACTORY__
#define __FOOD_FACTORY__

#include <map>

#include "domain_layer/food/Food.hpp"

namespace domain_layer::food
{
    //
    // Factory to create Food objects.
    //
    class FoodFactory
    {
        public:
            //
            // Creates single factory instance.
            //
            static FoodFactory *Get()
            {
                static FoodFactory instance;
                return &instance;
            }
            // Create random food type food object.
            //
            Food* CreateRandomFood();
            ~FoodFactory(){ }
        private:
            FoodFactory();
            int count;
            std::vector<createFoodFn> mFactoryVector;
            void Register(createFoodFn);

    };
}

#endif // __FOOD_FACTORY__
