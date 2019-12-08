//
// Food.hpp - Maintains the Food array
//
#ifndef _FOOD_
#define _FOOD_

#include <vector>
#include <iostream>
#include <random>
#ifdef WINDOWS
    #include "ui_layer/sdl/include/windows/SDL.h"
#else
    #include "ui_layer/sdl/include/linux/SDL.h"
#endif



namespace domain_layer::food
{
    //Food types
    enum { _N, _A, _E, _C };
    //
    //
    // Food base class.
    class Food
    {
      public:
          Food()
          {
            food_score = 1;
          }
          virtual ~Food() noexcept {}
          virtual int getColor() = 0;
          SDL_Point getFood();
          void setFood(int x, int y);
          int valid_food;
          SDL_Point food_location;
          int food_score;
    };

    //
    // create function prototype.
    //
    typedef Food* (*createFoodFn)();

    //
    // Food N class derived from Food base class.
    //
    class Food_N: public Food
    {
        public:
            Food_N(); // Constructor
            ~Food_N() = default;
            int getColor()                          override;

            static Food* Create()
            {
                return new Food_N();
            }
    };

    //
    // Food N class derived from Food base class.
    //
    class Food_A: public Food
    {
        public:
            Food_A(); // Constructor
            ~Food_A() = default;
            int getColor()                          override;

            static Food* Create()
            {
                return new Food_A();
            }
    };

    //
    // Food C class derived from Food base class.
    //
    class Food_C: public Food
    {
        public:
            Food_C(); // Constructor
            ~Food_C() = default;
            int getColor()                          override;

            static Food* Create()
            {
                return new Food_C();
            }
    };

    //
    // Food N class derived from Food base class.
    //
    class Food_E: public Food
    {
        public:
            Food_E(); // Constructor
            ~Food_E() = default;
            int getColor()                          override;

            static Food* Create()
            {
                return new Food_E();
            }
    };
}
#endif //
