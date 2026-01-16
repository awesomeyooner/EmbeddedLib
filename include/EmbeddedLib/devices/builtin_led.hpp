#ifndef BUILTIN_LED_HPP
#define BUILTIN_LED_HPP

#include <Arduino.h>
#include "EmbeddedLib/devices/led.hpp"

#ifdef ESP32_DEVKIT_V1
    #define LED_PIN 2
#endif

#ifdef SAMD21_SEEED_XIAO
    #define LED_PIN 13
#endif

#ifdef STM32_NUCLEO64_F446RE
    #define LED_PIN PA5
#endif

#ifndef LED_PIN
    #define LED_PIN
#endif

class BuiltinLED{

    public:

        static LED led;

        static void initialize(int pin = -1);

        static void on();

        static void off();

        static void toggle(bool turn_on);

        static void toggle();

        static bool is_on();
    
}; // class BuiltinLED


#endif // BUILTIN_LED_HPP