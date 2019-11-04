//
// Storage.hpp -- Manages data storage and retrival from the file.
//
#ifndef __STORAGE__
#define __STORAGE__

#include "technical_services_layer/Persistence/PersistenceHandler.hpp"
#include "technical_services_layer/Logger/SimpleLogger.hpp"

#ifdef WINDOWS
    #define FILE_PATH "../../../SourceCode/technical_services_layer/"
    //
    // Enable this if want to debug the code using debugger.
    // Change to the absolute path in your system
    //
    //#define FILE_PATH "D:\\repo\\tetris\\C++ Development Root\\SourceCode\\technical_services_layer\\"
#else
    #define FILE_PATH "./technical_services_layer/"
#endif

#define CREDENTIAL_FILENAME     FILE_PATH"Player_Credentials"

namespace technical_services_layer::Persistence
{
    //
    // Implements the functions of the PersistanceHandler Interface.
    //
    class Storage : public technical_services_layer::Persistence::PersistenceHandler
    {
        public:
            using PersistenceHandler::PersistenceHandler;
            Storage();
            ~Storage();

            bool                registerPlayer(UserCredentials)                         override;
	    bool                validateUsername(const std::string & username)		override;
	    UserCredentials     adminLogin(const std::string & username)                override;
            UserCredentials     getPlayerCredentials(const std::string & username)      override;
            std::vector<Score>  getMaxScores()	                                        override;
            void                setPlayerMaxScore(const std::string & , unsigned int)   override;
            void                addPlayerScore(const std::string &, unsigned int)       override;
            void                changePlayerGamesLeft(const std::string & username, unsigned int games_left)    override;
            std::vector<unsigned int> getPlayerPrevScore(const std::string username)    override;

        private:
            technical_services_layer::Logging::LoggerHandler*                   _loggerPtr;
            
            // convenience reference object enabling standard insertion syntax
            // This line must be physically after the definition of _loggerPtr
            technical_services_layer::Logging::LoggerHandler                    & _logger = *_loggerPtr;
    };
}

#endif  // __STORAGE__
