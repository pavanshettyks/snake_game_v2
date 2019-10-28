//
// ViewHandler.hpp -- Interface for the main to call into.
//
#ifndef __VIEW_HANDLER__
#define __VIEW_HANDLER__

namespace ui_layer::view
{
    //
    // Interface to ui layer.
    //
    class ViewHandler
    {
        public:
            // Constructors and assignment operations
            ViewHandler() = default;    // default ctor

            // Abstract class destructor
            virtual ~ViewHandler() noexcept = 0;  // must be virtual and pure

            // Operations
            virtual void launch() = 0;
    };

    inline ViewHandler::~ViewHandler() noexcept
    {

    }
}

#endif // __VIEW_HANDLDER__
