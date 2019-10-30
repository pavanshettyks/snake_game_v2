//
// SimpleStorage.cpp -- Handles the reading and writing to the file.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "technical_services_layer/Persistence/SimpleStorage.hpp"

namespace technical_services_layer::Persistence
{
    //
    // Constructor
    //
    SimpleStorage::SimpleStorage()
    : _loggerPtr(new technical_services_layer::Logging::SimpleLogger)
    {
        _logger << "Persistance storage has successfully initialized.";
    }

    //
    // Destructor
    //
    SimpleStorage::~SimpleStorage()
    {
        _logger << "Persistance storage has shutdown.";
    }

    //
    // Stores the users credentials into the file.
    //
    bool SimpleStorage::registerPlayer(UserCredentials creds)
    {
        // open credentials file.
        std::ofstream credFile(CREDENTIAL_FILENAME, std::ios::out | std::ios::app);
        if (!credFile.is_open())
        {
            std::cout << "Failed to open credentials file." << std::endl;
            return false;
        }

        // Create per player file to store the scores.
        std::string playerFilename(FILE_PATH);
        playerFilename.append(creds.username);
        playerFilename.append(".txt");

        std::ofstream playerFile(playerFilename.c_str(), std::ios::out);
        if (!playerFile.is_open())
        {
            std::cout << "Failed to create player file." << std::endl;
            credFile.close();
            return false;
        }

        // Write to credential file.
        credFile << creds.username.c_str() << " " << creds.password.c_str() << " "
            << creds.maxScore << " " << creds.gamesLeft << " " << std::endl;

        playerFile.close();
        credFile.close();

        return true;
    }


    //
    // Returns true if username is taken else false
    //
     bool SimpleStorage::validateUsername(const std::string & username)
    {
        std::string line;
        std::string name, passwd;
        unsigned int score, gamesLeft;

        // Open credential file.
        std::ifstream credFile(CREDENTIAL_FILENAME, std::ios::in);
        if (!credFile.is_open())
        {
            std::cout << "Failed to open credentials file." << std::endl;
        }

        // Find the data matching the username provided.
        while (getline(credFile, line))
        {
            std::istringstream buf(line);
            buf >> name >> passwd >> score >> gamesLeft;
            if (name == username)
            {
                return true;
            }
        }

        // if username not found.
        return false;
    }


    //
    // Returns the user credentials for the username provided.
    //
    UserCredentials SimpleStorage::getCredentialsByUsername(const std::string & username)
    {
        std::string line;
        std::string name, passwd;
        unsigned int score, gamesLeft;

        // If admin just return the hardcoded value.
        if (username == "admin")
        {
            UserCredentials ret = {"admin", "q123", 0, 0};
            return ret;
        }

        // Open credential file.
        std::ifstream credFile(CREDENTIAL_FILENAME, std::ios::in);
        if (!credFile.is_open())
        {
            std::cout << "Failed to open credentials file." << std::endl;
        }

        // Find the data matching the username provided.
        while (getline(credFile, line))
        {
            std::istringstream buf(line);
            buf >> name >> passwd >> score >> gamesLeft;
            if (name == username)
            {
                UserCredentials ret = {name, passwd, score, gamesLeft};
		 //std::cout << name << passwd << score << gamesLeft;
                return ret;
            }
        }

        // if username not found.
        return {username, "", 0, 0};
    }


    //
    // Returns the vector of max scores of all the players.
    //
    std::vector<Score> SimpleStorage::getAllPlayerMaxScore()
    {
        std::vector<Score> maxScores;
        std::string line;
        std::string name, passwd;
        unsigned int score, gamesLeft;

        // open credential file.
        std::ifstream credFile(CREDENTIAL_FILENAME, std::ios::in);
        if (!credFile.is_open())
        {
            std::cout << "Failed to open credentials file." << std::endl;
        }

        // Read and return the max score of each player.
        while (getline(credFile, line))
        {
            std::istringstream buf(line);
            buf >> name >> passwd >> score >> gamesLeft;
            maxScores.insert(maxScores.end(), {name, score});
        }

        return maxScores;
    }


    //
    // Changes the max score of the player in the file.
    //
    void SimpleStorage::setPlayerMaxScore(const std::string & username, unsigned int maxScore)
    {
        int ret;
        std::string line;
        std::string name, passwd;
        unsigned int score, gamesLeft;
        std::string tempFilename;

        // Create a temp file.
        tempFilename.append(CREDENTIAL_FILENAME);
        tempFilename.append(".temp");
        std::ofstream tempFile(tempFilename.c_str());

        // Open credential file.
        std::ifstream credFile(CREDENTIAL_FILENAME);
        if (!credFile.is_open())
        {
            std::cout << "Failed to open credentials file." << std::endl;
        }

        // Copy the data from credential file to temp file for all the user
        // except for the username provided, for him copy the data with modified
        // max score.
        while (getline(credFile, line))
        {
            std::istringstream buf(line);
            buf >> name >> passwd >> score >> gamesLeft;
            if (name == username)
            {
                score = maxScore;
                tempFile << name << " " << passwd << " " << score << " " << " " << gamesLeft << std::endl;
            }
            else
            {
                tempFile << name << " " << passwd << " " << score << " " << " " << gamesLeft << std::endl;
            }
        }

        credFile.close();
        tempFile.close();

        // Delete the credential file and rename the temp file to credential file.
        std::remove(CREDENTIAL_FILENAME);
        ret = std::rename(tempFilename.c_str(), CREDENTIAL_FILENAME);
        if (ret != 0)
        {
            _logger << "Critical Error: credentials file is deleted.";
        }
    }


    //
    // Appends the player score to the player file.
    //
    void SimpleStorage::addPlayerScore(const std::string & username, unsigned int score)
    {
        std::string playerFilename(FILE_PATH);
        playerFilename.append(username);
        playerFilename.append(".txt");

        std::ofstream playerFile(playerFilename.c_str(), std::ios::app);
        if (!playerFile.is_open())
        {
            std::cout << "Failed to open player file." << std::endl;
        }

        playerFile << score <<std::endl;
    }

    //
    // Changes the games left for the player in the credential file.
    //
    void SimpleStorage::changePlayerGamesLeft(const std::string & username, unsigned int games_left)
    {
        int ret;
        std::string line;
        std::string name, passwd;
        unsigned int score, gamesLeft;
        std::string tempFilename;

        // Create a temp file.
        tempFilename.append(CREDENTIAL_FILENAME);
        tempFilename.append(".temp");
        std::ofstream tempFile(tempFilename.c_str());

        // Open credential file.
        std::ifstream credFile(CREDENTIAL_FILENAME);
        if (!credFile.is_open())
        {
            std::cout << "Failed to open credentials file." << std::endl;
        }

        // Copy the data from credential file to temp file for all the user
        // except for the username provided, for him copy the data with modified
        // games left.
        while (getline(credFile, line))
        {
            std::istringstream buf(line);
            buf >> name >> passwd >> score >> gamesLeft;
            if (name == username)
            {
                gamesLeft = games_left;
                tempFile << name << " " << passwd << " " << score << " " << gamesLeft << std::endl;
            }
            else
            {
                tempFile << name << " " << passwd << " " << score << " " << gamesLeft << std::endl;
            }
        }

        credFile.close();
        tempFile.close();

        // Delete the credential file and rename the temp file to credential file.
        std::remove(CREDENTIAL_FILENAME);
        ret = std::rename(tempFilename.c_str(), CREDENTIAL_FILENAME);
        if (ret != 0)
        {
            _logger << "Critical Error: credentials file is deleted.";
        }
    }

    //
    // Returns the vector containing last 10 scores of the player from the player file.
    //
    std::vector<unsigned int> SimpleStorage::getPlayerPrevScore(const std::string username)
    {
        std::string line;
        unsigned int score;
        std::vector<unsigned int> scores = {};
        std::vector<unsigned int> lastScores = {};

        std::string playerFilename(FILE_PATH);
        playerFilename.append(username);
        playerFilename.append(".txt");

        // Open player file
        std::ifstream playerFile(playerFilename.c_str(), std::ios::in);
        if (!playerFile.is_open())
        {
            std::cout << "Failed to open player file." << std::endl;
            return scores;
        }

        // Read all the data from the file.
        while (getline(playerFile, line))
        {
            std::istringstream buf(line);
            buf >> score;
            scores.push_back(score);
        }

        // Copy only last 10 scores.
        for (std::vector<unsigned int>::iterator it = (scores.end() - std::min(static_cast<int>(scores.size()), 10));
             it != scores.end(); ++it)
        {
            lastScores.push_back(*it);
        }

        return lastScores;
    }
}
