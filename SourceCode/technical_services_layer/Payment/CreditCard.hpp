//
// CreditCard.hpp -- Class that handles the payment.
//

#ifndef __CREDITCARD__
#define __CREDITCARD__

#include "technical_services_layer/Logger/LoggerHandler.hpp"
#include "technical_services_layer/Logger/SimpleLogger.hpp"

//
// Contains creditcard and creditcardFactory class.
// Contains mastercard and visacard as well as thier respective factories.
//
namespace technical_services_layer::payment
{
    struct CreditCardInfo
    {
	std::string cardType;
        std::string name;
        std::string cardNum;
        unsigned int expiryMonth;
        unsigned int expiryYear;
        unsigned int CVV;
    };

    class CreditCard
    {
        public:
            CreditCard() = default;
            CreditCard(CreditCardInfo & ccInfo)
            : creditcardDetail(ccInfo),
              _loggerPtr(new technical_services_layer::Logging::SimpleLogger)
            {
            }

            virtual bool doPayment() = 0;
            virtual ~CreditCard() = 0;

        protected:
            CreditCardInfo creditcardDetail;

            technical_services_layer::Logging::LoggerHandler* _loggerPtr;
            technical_services_layer::Logging::LoggerHandler & _logger = *_loggerPtr;
    };

    inline CreditCard::~CreditCard()
    {

    }


    class VisaCard : public CreditCard
    {
        public:
            VisaCard(CreditCardInfo & ccInfo)
            : CreditCard(ccInfo)
            {
            }

            ~VisaCard() override = default;
            bool doPayment();
    };

    class MasterCard : public CreditCard
    {
        public:
            MasterCard(CreditCardInfo & ccInfo)
            : CreditCard(ccInfo)
            {
            }

            ~MasterCard() override = default;
            bool doPayment();
    };



    class CreditCardFactory
    {
        public:

	    static CreditCardFactory* createFactory();

            virtual CreditCard* createCreditCard(CreditCardInfo & ccInfo) = 0;
    };

    class VisaCardFactory : public CreditCardFactory
    {
        public:
            CreditCard* createCreditCard(CreditCardInfo & ccInfo) override
            {
                return new VisaCard(ccInfo);
            }
    };

    class MasterCardFactory : public CreditCardFactory
    {
        public:
            CreditCard* createCreditCard(CreditCardInfo & ccInfo) override
            {
                return new MasterCard(ccInfo);
            }
    };
}

#endif // __CREDITCARD__
