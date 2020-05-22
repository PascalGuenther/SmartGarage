/**
 * @file Garage.h
 * @author Pascal Guenther (pascal.develop@pguenther.net)
 * @brief Garage Door controller
 * @version 0.1
 * @date 2020-05-22
 * 
 * @copyright Copyright (c) 2020 Pascal Guenther
 * 
 */
#pragma once
#include <cinttypes>
#include <Arduino.h>

#if !defined(GARAGE_API)
    #define GARAGE_API
#endif // !defined(GARAGE_API)

namespace SmartGarage {

    class GARAGE_API GarageDoor
    {
    public:
        GarageDoor(uint8_t ucActuatorPin, bool bActiveLow = false)
            : m_ucActuatorPin(ucActuatorPin), m_bActiveLow(bActiveLow)
        {
            pinMode(m_ucActuatorPin, OUTPUT);
            digitalWrite(m_ucActuatorPin, m_bActiveLow ? HIGH : LOW);
        }
        void Move()
        {
            unsigned long ulStart = millis();
            digitalWrite(m_ucActuatorPin, m_bActiveLow ? LOW : HIGH);
            while(millis() < (ulStart + 750u)) {}
            digitalWrite(m_ucActuatorPin, m_bActiveLow ? HIGH : LOW);
        }
    private:
        uint8_t m_ucActuatorPin;
        uint8_t m_bActiveLow;
    };

}
