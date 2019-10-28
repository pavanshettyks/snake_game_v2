//
// CreditCard.cpp -- Class that handles the payment.
//

#include <string>
#include <iostream>
#include <fstream>

#include "technical_services_layer/Payment/CreditCard.hpp"

#ifdef WINDOWS
    #define CONFIG_FILENAME "../../../SourceCode/technical_services_layer/config.txt"
    //
    // Enable these if want to debug the code using debugger.
    // Change to the absolute path in your system
    //
    //#define CONFIG_FILENAME "D:\\repo\\tetris\\C++ Development Root\\SourceCode\\technical_services_layer\\config.txt"
#else
    #define CONFIG_FILENAME "./technical_services_layer/config.txt"
#endif

namespace technical_services_layer::payment
{
    //
    // Create the appropriate factory based on the config read from file.
    //
    CreditCardFactory* CreditCardFactory::createFactory()
    {
        //
        // Read preference from config file.
        //
        std::string paymentType, line;

        std::ifstream PaymentConfigFile(CONFIG_FILENAME, std::ios::in);
        if (!PaymentConfigFile.is_open())
        {
            std::cout << "Failed to open config file." << std::endl;
            return NULL;
        }

        getline(PaymentConfigFile, line);

        PaymentConfigFile.close();

        if(line == "visa")
            return new VisaCardFactory();
        else if(line == "mastercard")
            return new MasterCardFactory();
        else
        {
            std::cout << "Unsupported credit card type found in config file" << std::endl;
        }

        return NULL;
    }

    //
    // Processes the payment of visa card.
    //
    bool VisaCard::make_payment()
    {
        _logger << "Visa payment sucessful.";
        return true;
    }

    //
    // Processes the payment of mastercard.
    //
    bool MasterCard::make_payment()
    {
        _logger << "MasterCard payment sucessful.";
        return true;
    }
}
