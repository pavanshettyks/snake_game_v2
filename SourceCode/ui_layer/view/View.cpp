//
//  View.cpp - Class for handling drawing, it uses SDL2 for the rendering.
//
#include <algorithm>




#include "ui_layer/view/View.hpp"
#include "domain_layer/game/Game.hpp"
//#include "domain_layer/player/Player.hpp"
#include "technical_services_layer/Persistence/Storage.hpp"
#include "technical_services_layer/Logger/SimpleLogger.hpp"
#include "technical_services_layer/Payment/CreditCard.hpp"

#undef max
// Number of milliseconds that the piece remains before going 1 block down
#define WAIT_TIME 700

// OS dependent code, diffent file location based on the executable location.
#ifdef WINDOWS

    #define OS_DEP_CLEAR     "cls"
    #define BACKGROUND_IMAGE "../../../SourceCode/ui_layer/resources/orange.bmp"
    #define FONT_NAME        "../../../SourceCode/ui_layer/resources/arial.ttf"

    //
    // Enable these if want to debug the code using debugger.
    // Change to the absolute path in your system
    //


#else
    #define OS_DEP_CLEAR     "clear"
    #define BACKGROUND_IMAGE "./ui_layer/resources/orange.bmp"
    #define FONT_NAME        "./ui_layer/resources/arial.ttf"
#endif

// SDL related global variables.
static TTF_Font *font;
static SDL_Window  *win;
static SDL_Renderer *ren;
//static SDL_Surface  *imgSurface;
static SDL_Texture *background_tx;
static Uint8 mColors [ui_layer::view::COLOR_MAX][4] =  {  {0   , 0   , 0   , 0   },
                                                          {0x00, 0x00, 0x00, 0xff},
                                                          {0xff, 0x00, 0x00, 0xff},
                                                          {0x00, 0xff, 0x00, 0xff},
                                                          {0x00, 0x00, 0xff, 0xff},
                                                          {0x00, 0xff, 0xff, 0xff},
                                                          {0xff, 0x00, 0xff, 0xff},
                                                          {0xff, 0xff, 0x00, 0xff},
                                                          {0xff, 0xff, 0xff, 0xff} };

namespace ui_layer::view
{
    //
    // Constructor.
    // Create objects to creditcardFactory, logger and persistancehandler.
    //
    View::View()
    : _persistentData(new technical_services_layer::Persistence::Storage),
      _loggerPtr(new technical_services_layer::Logging::SimpleLogger)
    {
        //_cmdData = NULL;
       // _gameData = NULL;
        _playerData = NULL;
        mScreenHeight = 0;
        _ccFactory = technical_services_layer::payment::CreditCardFactory::createFactory();



        _logger << "View being used and has been successfully initialized";
    }

    //
    // Destructor.
    //
    View::~View()
    {
        _logger << "View shutdown successfully";
    }

    //
    // Start of the UI interface.
    //
    void View::launch()
    {
        bool status = false;

        status = initialize_system();
        if(status == false)
            return;

        while (1)
        {
            status = display_main_menu();
            if(status == false)
                break;

            status = display_user_menu();
            if (status == false)
                break;
        }
    }

    //
    // Displays the main menu.
    //
    bool View::display_main_menu()
    {
        unsigned int choice = 0;
        bool ret = false;

        while (1)
        {
            std::system(OS_DEP_CLEAR);
	    //std::cout << termcolor::red << "Hello, Colorful World!" << std::endl;
            std::cout << "\033[1;31m-----------------------------------------\033[0m" << std::endl;
            std::cout << "    Welcome to game station menu     " << std::endl;
            std::cout << "\033[32m-----------------------------------------\033[0m" << std::endl;
            std::cout << "1 - Create New Player Account" << std::endl;
            std::cout << "2 - Player login       " << std::endl;
            std::cout << "3 - Exit               " << std::endl;
            std::cout << "-----------------------------------------" << std::endl;
            std::cout << "Enter your choice: ";
//	    std::cout << "\033[1;31mbold red text\033[0m\n";
            std::cin >> choice;

            if (choice == 0 || choice > 3)
            {
                std::cout << "Invalid option selected \n" << std::endl;
                std::cout << "Press enter to retry \n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            switch (choice)
            {
                case 1:
                    register_player();
                    break;
                case 2:
                    ret = login_user();
                    if(ret == true)
                        return true;
                    break;
                case 3:
                    return false;
                    break;
            }
        }
    }

    //
    // Accepts username and password of new player and register them in storage.
    //
    void View::register_player()
    {
        std::string username, password;
        technical_services_layer::Persistence::UserCredentials cred;
	//technical_services_layer::Persistence::UserCredentials cred;
        bool ret = true;


        std::system(OS_DEP_CLEAR);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
///
        std::cout << "---------------------------" << std::endl;
        std::cout << "    Player Registration    " << std::endl;

        std::cout << "---------------------------" << std::endl;
        std::cout << "Please Enter username: ";
        std::getline(std::cin, username);
        std::cout << "Enter password: ";
        std::getline(std::cin, password);



        if (_persistentData->validateUsername(username))
        {
            std::cout <<termcolor::red << "Username is already taken." << termcolor::reset << std::endl;
	    std::cout <<termcolor::red  << "Player registration failed. Retry later." << termcolor::reset<<std::endl;
            goto end;
        }


        cred.username = username;
        cred.password = password;
        cred.maxScore = 0;
        cred.gamesLeft = 5;

        ret = _persistentData->registerPlayer(cred);
        if (ret == false)
        {
            std::cout  <<termcolor::red << "Player registration failed. Retry later." << termcolor::reset<<std::endl;
            goto end;
        }
	std::cout << termcolor::green << "Player registration successfull" <<termcolor::reset<< std::endl;
        //std::cout << "Player registration successfull." << std::endl;
	std::cout << "Thank you for choosing our game"<< std::endl;


    end:
	//Sleep(1000);
	std::cout << "Returning to main screen"<< std::endl;
        std::cout << "Press enter to continue"<< std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    //
    // Accepts the username and password and then checks if they match
    // the one kept in storage. If matches, creates player handle.
    //
    bool View::login_user()
    {
        std::string username, password;
        technical_services_layer::Persistence::UserCredentials cred;
        bool ret = true;

        std::system(OS_DEP_CLEAR);

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "------------------------------" << std::endl;
        std::cout << "         Player Login      " << std::endl;
        std::cout << "------------------------------" << std::endl;
        std::cout << "Enter your username: ";
        std::getline(std::cin, username);
        std::cout << "Enter your password: ";
        std::getline(std::cin, password);

        cred = _persistentData->getPlayerCredentials(username);
        //std::cout << "Invalid username or password." << cred.password <<std::endl;
        if (cred.password != password)
        {
            ret = false;
            std::cout <<termcolor::red<<"Invalid username or password." <<termcolor::reset<< std::endl;
            goto end;
        }

        std::cout <<termcolor::green<< "Player login successfull" <<termcolor::reset<< std::endl;

        //
        // Create player handle.
        //
        _playerData =  new domain_layer::player::Player(cred.username, cred.maxScore, cred.gamesLeft, _persistentData);

    end:

        std::cout << "Press enter to continue";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return ret;
    }

    //
    // Displays player menu.
    //
    bool View::display_user_menu()
    {
        unsigned int choice;
        bool ret = true;


        while (1)
        {
            std::system(OS_DEP_CLEAR);
            std::cout << "---------------------------" << std::endl;
            std::cout << "         Snake Game Menu       " << std::endl;
            std::cout << "---------------------------" << std::endl;
            std::cout << "1 - Play Snake Game              " << std::endl;
            std::cout << "2 - Buy premium version           " << std::endl;
            std::cout << "3 - View previous game results   " << std::endl;
            std::cout << "4 - View Leaderboard       " << std::endl;
	          std::cout << "5 - Game help      " << std::endl;
            std::cout << "6 - Logout                 " << std::endl;
            std::cout << "---------------------------" << std::endl;
            std::cout << "Please enter your choice: ";
            std::cin >> choice;

            switch (choice)
            {
                case 1:
                    // Checks if player have games left to play.
                    ret = check_player_status();
                    if (ret == false)
                    {
                        break;
                    }
                    // Reduce the number of games that player can play by 1.
                    _playerData->reduce_games_left();
                    // Starts the game.
                    play_game();


                    break;
                case 2:
                    // Buy premium version
                    buy_premium();
                    break;
                case 3:
                    // Displays last 10 scores of the player.
                    view_previous_score();
                    break;
                case 4:
                    // Displays the ranking of each player based on their max score.
                    view_leaderboard();
                    break;
		            case 5:
                    // Displays game controls and tricks
                    view_gameHelp();
                    break;
                case 6:
                    goto exit_loop;
                    break;
                default:
                    std::cout << "Invalid choice provided." << std::endl;
                    std::cout << "Press enter to retry";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
            }
        }

    exit_loop:
        return ret;
    }

    //
    // Asks for admin password so that system can be started.
    //
    bool View::initialize_system()
    {
        std::string password;
        technical_services_layer::Persistence::UserCredentials cred;

        std::cout <<termcolor::green<< "Username: admin" << std::endl;
        std::cout << "Enter password: ";
        std::getline(std::cin, password);
	      cred = _persistentData->adminLogin("admin");
       // cred = _persistentData->getCredentialsByUsername("admin");
        if (cred.password != password)
        {
            std::cout <<termcolor::red<< "Invalid admin password." <<std::endl;
	          std::cout << "Please try again." <<std::endl;
            return false;
        }


	std::cout << "System start initiated" <<termcolor::reset<< std::endl;
	std::cout << "System started" <<termcolor::reset<< std::endl;
        std::cout << "Press enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return true;
    }

    //
    // Game helps and tricks
    //
    void View::view_gameHelp(){
      std::system(OS_DEP_CLEAR);
      std::string temp;
      std::cout << std::endl;
      std::cout << "\033[32m-----------------------------------------\033[0m" << std::endl;
      std::cout << "    Welcome to game station help     " << std::endl;
      std::cout << "\033[32m-----------------------------------------\033[0m" << std::endl;
      std::cout << " Controls:    " << std::endl;
      std::cout << " ^ (upward arrow) to move the snake up " << std::endl;
      std::cout << " v (downward arrow) to move the snake down   " << std::endl;
      std::cout << " < (left arrow) to move the snake left   " << std::endl;
      std::cout << " > (right arrow) to move the snake right   " << std::endl;
      std::cout << " Rules:    " << std::endl;
      std::cout << " 1. If snake touches its own body game ends   " << std::endl;
      std::cout << " 2. If snake eats food its body grows   " << std::endl;
      std::cout << " 3. For every food the snake eats poits will be awarded  " << std::endl;
      std::cout << " 4. Snake's speed will increase after it eats food" << std::endl;
      std::cout << " Tricks:    " << std::endl;
      std::cout << " 1. Try eating more food   " << std::endl;
      std::cout << " 2. Try placing the snake on the boundary " << std::endl;
      std::cout << " 3. If the snake length increases try keeping snake body away from head " << std::endl;
      std::cout << "Press enter to goto main menue.....";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      getline(std::cin, temp);
    }

    //
    // Checks if player is allowed to player more games or not.
    //
    bool View::check_player_status()
    {
        bool ret = true;
        std::string temp;

        // check if player can play game.
        if(_playerData->get_games_left() <= 0)
        {
            ret = false;
            std::cout << termcolor::red <<"Your game limit is over." << termcolor::reset <<std::endl;
            std::cout<< termcolor::green << "Please buy premium version to play more games" << termcolor::reset << std::endl;
            std::cout << "Press enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(std::cin, temp);
        }

        return ret;
    }






    //
    // Start the game.
    //
    void View::play_game()
    {
        std::string temp;
	constexpr std::size_t kFramesPerSecond{60};
  	constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  	constexpr std::size_t kScreenWidth{640};
  	constexpr std::size_t kScreenHeight{640};
 	constexpr std::size_t kGridWidth{32};
  	constexpr std::size_t kGridHeight{32};
  	PlayZone playzone(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  	//Controller controller;
	_control = new ui_layer::controller::Controller;
  	Game game(kGridWidth, kGridHeight);
        game.Run(_control, playzone, kMsPerFrame);

        std::cout << "Game has terminated successfully!\n";
        _playerData->set_max_score(game.GetScore());
        std::cout <<termcolor::green << "Score: " << game.GetScore() << termcolor::reset<<"\n";
 	      std::cout << std::endl;
        std::cout << "Press enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(std::cin, temp);
  //std::cout << "Size: " << game.GetSize() << "\n";
	/*bool

    exit_loop:
        cleanup_SDL();
        return;*/
    }

    //
    // Asks for the payment information and then sends it down to process it.
    // If sucessful, adds more game to the player.
    //
    void View::buy_premium()
    {
        bool ret = false;
        std::string temp;
        std::system(OS_DEP_CLEAR);
        technical_services_layer::payment::CreditCardInfo ccInfo;
        std::cout <<termcolor::green<< "With premium version you will get to play 50 games." <<termcolor::reset<< std::endl;
        // Ask for credit card info.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << std::endl;
        std::cout << "   Payment Info   " << std::endl;
        std::cout << "------------------" << std::endl;
	      std::cout << "Card type (visa/mastercard): " << std::endl;
        getline(std::cin, ccInfo.cardType);
        std::cout << "Name on card: " << std::endl;
        getline(std::cin, ccInfo.name);
        std::cout << "Credit card number: " << std::endl;
        getline(std::cin, ccInfo.cardNum);
        std::cout << "Expiry month: " << std::endl;
        std::cin >> ccInfo.expiryMonth;
        std::cout << "Expiry year: " << std::endl;
        std::cin >> ccInfo.expiryYear;
        std::cout << "CVV: " << std::endl;
        std::cin >> ccInfo.CVV;
        std::cout << std::endl;
        std::cout << "Wait while we process the payment..." << std::endl;

        // Create credit card object with the creditcard info.
        technical_services_layer::payment::CreditCard* creditCard = _ccFactory->createCreditCard(ccInfo);

        // Request payment processing.
        ret = creditCard->make_payment();
        if (ret == false)
        {
            std::cout << "Credit card payment failed." << std::endl;
            goto End;
        }

        // If payment passed add more plays to player.
        _playerData->add_games_after_payment();

    End:
        std::cout << std::endl;
        std::cout << "Press enter to continue...";
        std::getline(std::cin, temp);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    //
    // Display last 15 scores of the player.
    //
    void View::view_previous_score()
    {
        std::vector<unsigned int> prev_score;
        unsigned int i = 1;
        std::string temp;

        // Get last 15 scores of the player.
        prev_score = _playerData->get_previous_scores();

        // Display scores.
        std::cout << std::endl;
        std::cout << "Previous 15 scores" << std::endl;
        std::cout << "------------------" << std::endl;
        for (std::vector<unsigned int>::iterator it = prev_score.begin() ;
             it != prev_score.end(); ++it)
        {
            std::cout << i << ") " << *it << std::endl;
            i++;
        }

        std::cout << std::endl;
        std::cout << "Press enter to continue...";
        std::getline(std::cin, temp);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    //
    // Comparator function for sorting.
    //
    bool sortbyscore(technical_services_layer::Persistence::Score &a,
        technical_services_layer::Persistence::Score &b)
    {
        return (a.maxScore > b.maxScore);
    }

    //
    // Displays the player name and score based on their max score.
    //
    void View::view_leaderboard()
    {
        std::vector<technical_services_layer::Persistence::Score> leaderboard;
        unsigned int i = 1;
        std::string temp;

        // Retrives all max score from the persistance layer.
        leaderboard = _persistentData->getMaxScores();

        // Sort the data based on the max score.
        std::sort(leaderboard.begin(), leaderboard.end(), sortbyscore);

        // Display the leaderboard.
        std::cout << std::endl;
        std::cout << "Leaderboard" << std::endl;
        std::cout << "----------------" << std::endl;
        for (std::vector<technical_services_layer::Persistence::Score>::iterator it = leaderboard.begin();
            it != leaderboard.end(); ++it)
        {
            std::cout << i << ") " << (*it).username << "   " <<  (*it).maxScore << std::endl;
            i++;
        }
        std::cout << std::endl;
        std::cout << "Press enter to continue...";
        std::getline(std::cin, temp);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }


    //
    // Displays the popup message box when the game is over.
    //
    int View::messageBox()
    {
        const SDL_MessageBoxButtonData buttons[] = {
              { 0, 0, "OK" },   // { .flags, .buttonid, .text }
        };

        const SDL_MessageBoxColorScheme colorScheme = {
              {   // .colors (.r, .g, .b)
                  // [SDL_MESSAGEBOX_COLOR_BACKGROUND]
                  {   0,   0,   0 },
                  // [SDL_MESSAGEBOX_COLOR_TEXT]
                  {   0, 255,   0 },
                  // [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER]
                  { 255, 255,   0 },
                  // [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND]
                  { 205, 205, 205 },
                  // [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]
                  { 255,   0, 255 }
              }
        };

        const SDL_MessageBoxData messageboxdata = {
                SDL_MESSAGEBOX_INFORMATION,     // .flags
                NULL,                           // .window
                "GAME OVER!",                   // .title
                "Press OK to go to main menu",  // .message
                SDL_arraysize(buttons),         // .numbuttons
                buttons,                        // .buttons
                &colorScheme                    // .colorScheme
        };

        int buttonid;
        if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
        {
            SDL_Log("error displaying message box");
            return 1;
        }
        if (buttonid == -1)
        {
            SDL_Log("no selection");
        }
        else
        {
            return buttonid;
        }

        return 0;
    }

    //


    //
    // Clear the screen to black
    //
    void View::clearScreen()
    {
        color pC = BLACK;
        SDL_SetRenderDrawColor(ren, mColors[pC][0], mColors[pC][1], mColors[pC][2], mColors[pC][3]);
        SDL_RenderClear(ren);
    }



    // Loads score.
    //
    void View::showScore(unsigned int score)
    {
        char str[20];
        SDL_Surface* textSurface = NULL;
        SDL_Color foregroundColor = { 255,255,255,0 };

        #ifdef WINDOWS
            sprintf_s(str, "Score: %d", score);
        #else
            sprintf(str, "Score: %d", score);
        #endif

        textSurface = TTF_RenderText_Solid(font, str, foregroundColor);
        SDL_Texture *Message = SDL_CreateTextureFromSurface(ren, textSurface);

        SDL_Rect Message_rect;
        Message_rect.x = 750;
        Message_rect.y = 100;
        Message_rect.w = 100;
        Message_rect.h = 30;

        SDL_RenderCopy(ren, Message, NULL, &Message_rect);

    }

    //
    // Cleanups the SDL library components.
    //
    void View::cleanup_SDL()
    {
        SDL_DestroyTexture(background_tx);
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
    }


}
