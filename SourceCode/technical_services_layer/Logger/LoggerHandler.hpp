//
// LoggerHandler.hpp -- Interface for logging
//
#ifndef __LOGGER_HANDLER__
#define __LOGGER_HANDLER__

#include <string>
#include <iostream>

namespace technical_services_layer::Logging
{
    //
    // Logging interface.
    //
    class LoggerHandler
    {
        public:
            LoggerHandler(std::ostream & loggingStream = std::clog);

            virtual ~LoggerHandler() noexcept = 0;
            virtual LoggerHandler & operator<< (const std::string & message) = 0;

        protected:
            std::ostream & _loggingStream;
    };

    inline LoggerHandler::~LoggerHandler() noexcept
    {}

    inline LoggerHandler::LoggerHandler(std::ostream & loggingStream)
        : _loggingStream(loggingStream)
    {}
}

#endif // __LOGGER_HANDLER__