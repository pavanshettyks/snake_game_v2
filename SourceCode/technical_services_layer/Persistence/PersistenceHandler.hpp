//
// PersistenceHandler.hpp -- Interface used to access storage.
//
#ifndef __PERSISTENCE_HANDLER__
#define __PERSISTENCE_HANDLER__

#include <string>
#include <vector>

namespace technical_services_layer::Persistence
{
    struct UserCredentials
    {
        std::string  username;
        std::string  password;
        unsigned int maxScore;
        unsigned int gamesLeft;
    };

    struct Score
    {
        std::string username;
        unsigned int maxScore;
    };

    //
    // Interface used to access the storage by the higher layers.
    //
    struct PersistenceHandler
    {
        PersistenceHandler() = default;
        virtual ~PersistenceHandler() noexcept = 0;

        virtual bool                registerPlayer( UserCredentials)                        = 0;
        virtual UserCredentials     getCredentialsByUsername(const std::string & username)  = 0;
        virtual std::vector<Score>  getAllPlayerMaxScore()                                  = 0;
        virtual void                setPlayerMaxScore(const std::string &, unsigned int)    = 0;
        virtual void                addPlayerScore(const std::string & , unsigned int)      = 0;
        virtual void                changePlayerGamesLeft(const std::string & username, unsigned int games_left)    = 0;
        virtual std::vector<unsigned int> getPlayerPrevScore(const std::string username)    = 0;
    };

    inline PersistenceHandler::~PersistenceHandler() noexcept
    {}
}

#endif  // __PERSISTANCE_HANDLER__