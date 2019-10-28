//
// SimpleLogger.hpp -- Manages the logging of messages.
//
#ifndef __SIMPLE_LOGGER__
#define __SIMPLE_LOGGER__

#include <iostream>
#include <chrono>
#include <iomanip>

#include "technical_services_layer/Logger/LoggerHandler.hpp"

namespace technical_services_layer::Logging
{
    //
    // Implements the functions of LoggerHandler interface.
    //
    class SimpleLogger : public technical_services_layer::Logging::LoggerHandler
    {
        public:
            SimpleLogger(std::ostream & loggingStream = std::clog);
            ~SimpleLogger() noexcept override;

            SimpleLogger & operator<< (const std::string & message) override;
    };

    inline SimpleLogger::SimpleLogger(std::ostream & loggingStream)
        : LoggerHandler(loggingStream)
    {
        *this << "Simple Logger initialization successfully";
    }

    inline SimpleLogger::~SimpleLogger() noexcept
    {
        *this << "Simple Logger shutdown successfully";
    }

    inline SimpleLogger & SimpleLogger::operator<< (const std::string & message)
    {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        #ifdef WINDOWS
            std::tm curr_time = { 0 };
            localtime_s(&curr_time, &now);
            _loggingStream << std::put_time(&curr_time, "%Y-%m-%d %X") << " | ";
        #else
            std::tm *curr_time = NULL;
            curr_time = localtime(&now);
            _loggingStream << std::put_time(curr_time, "%Y-%m-%d %X") << " | ";
        #endif

        _loggingStream << message << '\n';

        return *this;
    }
}

#endif // __SIMPLE_LOGGER__
