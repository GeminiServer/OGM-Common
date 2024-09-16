#pragma once
#include "Arduino.h"
#include "OpenKNX/Helper.h"
#include "OpenKNX/defines.h"

namespace OpenKNX
{

    namespace Led
    {
        namespace Effects
        {
            class Base
            {
              protected:
                volatile uint32_t _lastMillis = 0;

              public:
                virtual uint8_t value() = 0;
                virtual ~Base() {};
            };
        } // namespace Effects
    } // namespace Led
} // namespace OpenKNX