/**
 * @file bsp-config.h
 * @author Pascal Guenther (pascal.develop@pguenther.net)
 * @brief Global BSP and pin definitions
 * @version 1.0
 * @date 2020-05-22
 * 
 * @copyright Copyright (c) 2020 Pascal Guenther
 * 
 */
#pragma once
#include <cinttypes>

#if defined(ESP01)
    constexpr std::uint8_t ucGarageActuatorPin{14u};
#elif defined(NODEMCUV2)
    constexpr std::uint8_t ucGarageActuatorPin{16u};
#else
    #error Please define board
#endif
