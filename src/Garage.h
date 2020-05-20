#pragma once
#include <cinttypes>
#include <Arduino.h>

#if !defined(GARAGE_API)
    #define GARAGE_API
#endif // !defined(GARAGE_API)

namespace SmartGarage {

    class GARAGE_API Garage
    {
    public:
        Garage(uint8_t ucActuatorPin)
            : m_ucActuatorPin(ucActuatorPin)
        {
            pinMode(m_ucActuatorPin, OUTPUT);
            digitalWrite(m_ucActuatorPin, LOW);
        }
        void Move()
        {
            digitalWrite(m_ucActuatorPin, HIGH);
            delay(500);
            digitalWrite(m_ucActuatorPin, LOW);
        }
    private:
        uint8_t m_ucActuatorPin;
    };

}
