//
//  Food.cpp - creates a Food
//

#include "domain_layer/food/Food.hpp"

namespace domain_layer::food
{

    SDL_Point Food::getFood(){
      return food_location;
    }

    void Food::setFood(int x, int y){
       food_location.x = x;
       food_location.y =y;
    }
    //
    // Food_N functions.
    //
    Food_N::Food_N()
    {
      valid_food = 1;
      food_score = 1;
    }

    int Food_N::getColor()
    {
        return 0x27; //red
    }

    //
    // Food_A functions.
    //
    Food_A::Food_A()
    {
      food_score = 3;
      valid_food = 1;
    }

    int Food_A::getColor()
    {
        return 0x7A; //orange
    }

    //
    // Food_E functions.
    //

    Food_E::Food_E()
    {
      food_score = 4;
      valid_food =1;
    }

    int Food_E::getColor()
    {
        return 0xAA;  //orange - yellow
    }
    //
    // Food_C functions.
    //
    Food_C::Food_C()
    {
      food_score = 15;
      valid_food =1;
    }

    int Food_C::getColor()
    {
        return 0xCC; //yellow
    }

}
