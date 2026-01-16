#include "EmbeddedLib/devices/builtin_led.hpp"


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


LED BuiltinLED::led;

void BuiltinLED::initialize(int pin)
{
    // If the pin isn't set, then use the default. If it is, then use that
    pin == -1 ? led.initialize(LED_PIN) : led.initialize(pin);

} // end of "initialize"


void BuiltinLED::on()
{
    led.on();

} // end of "on"


void BuiltinLED::off()
{
    led.off();

} // end of "off"


void BuiltinLED::toggle(bool turn_on)
{
    led.toggle(turn_on);

} // end of "toggle"


void BuiltinLED::toggle()
{
    led.toggle();

} // end of "toggle"


bool BuiltinLED::is_on()
{
    return led.is_on();

} // end of "is_on"