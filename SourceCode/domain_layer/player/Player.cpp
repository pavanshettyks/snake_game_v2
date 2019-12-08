//
//  Player.cpp - Handles player object and data.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

#include "domain_layer/player/Player.hpp"

namespace domain_layer::player
{
    //
    // Constructor
    //
    Player::Player(std::string username, unsigned int max_score, unsigned int games_left, technical_services_layer::Persistence::PersistenceHandler* pPersisitance)
    {
        this->username = username;
        this->max_score = max_score;
        this->games_left = games_left;
        this->_persistanceData = pPersisitance;
    }

    //
    // Destructor
    //
    Player::~Player()
    {
        _persistanceData->changePlayerGamesLeft(this->username, this->games_left);
    }

    //
    // Returns the player name.
    //
    std::string Player::get_name()
    {
        return username;
    }

    //
    // Returns player's max score.
    //
    unsigned int Player::get_max_score()
    {
        return max_score;
    }

    //
    // Changes the player max score if it more than current max score also updates in storage.
    // Also adds the data to the player scores in the storage.
    //
    void Player::set_max_score(unsigned int score)
    {
        if (score > max_score)
        {
            max_score = score;
            _persistanceData->setPlayerMaxScore(this->username, score);
        }

        _persistanceData->addPlayerScore(this->username, score);
    }

    //
    // Returns the last 10 scores of the player.
    //
    std::vector<unsigned int> Player::get_previous_scores()
    {
        return _persistanceData->getPlayerPrevScore(this->username);
    }

    //
    // Returns number of games player can play.
    //
    unsigned int Player::get_games_left()
    {
        return this->games_left;
    }

    //
    // Decrements the number of games a player can play.
    //
    void Player::reduce_games_left()
    {
        this->games_left--;
          _persistanceData->changePlayerGamesLeft(this->username, this->games_left);
    }

    //
    // Increments the games a player can play and updates it in storage.
    //
    void Player::add_games_after_payment()
    {
        this->games_left += 50;
        _persistanceData->changePlayerGamesLeft(this->username, this->games_left);
    }
}
