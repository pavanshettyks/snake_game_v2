//
// Player.hpp - Maintains player object
//
#ifndef __PLAYER__
#define __PLAYER__

#include <vector>
#include "domain_layer/player/PlayerHandler.hpp"
#include "technical_services_layer/Persistence/PersistenceHandler.hpp"

namespace domain_layer::player
{
    //
    // Implements player handler interface functions.
    //
    class Player : public PlayerHandler{
        public:
            Player(std::string, unsigned int, unsigned int, technical_services_layer::Persistence::PersistenceHandler*);
            ~Player();
            std::string               get_name();
            unsigned int              get_max_score();
            void                      set_max_score(unsigned int);
            std::vector<unsigned int> get_previous_scores();
            unsigned int              get_games_left();
            void                      add_games_after_payment();
            void                      reduce_games_left();

        private:
            std::string  username;
            unsigned int max_score;
            unsigned int games_left;
            technical_services_layer::Persistence::PersistenceHandler* _persistanceData;
    };
}

#endif  //__PLAYER__
