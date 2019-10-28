//
// PlayerHandler.hpp -- Interface for view to call the player functions.
//
#ifndef __PLAYER_HANDLER__
#define __PLAYER_HANDLER__

#include <vector>

#include "technical_services_layer/Persistence/PersistenceHandler.hpp"

namespace domain_layer::player
{
    //
    // Interface between View and player class.
    //
    class PlayerHandler
    {
        public:
            PlayerHandler() = default;
            virtual ~PlayerHandler() noexcept = 0;

            virtual std::vector<unsigned int> get_previous_scores()     = 0;
            virtual unsigned int              get_games_left()          = 0;
            virtual void                      add_games_after_payment() = 0;
            virtual void                      reduce_games_left()       = 0;
    };

    inline PlayerHandler::~PlayerHandler() noexcept
    { }
}

#endif // __PLAYER_HANDLER__
