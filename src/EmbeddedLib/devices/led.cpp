#include "EmbeddedLib/devices/led.hpp"

LED::LED(int pin)
{
    m_pin = pin;
    m_is_on = false;

} // end of LED


void LED::initialize()
{
    // Set the pinmode to output
    pinMode(m_pin, OUTPUT);

    // Turn off as a safety check
    off();

} // end of "initialize"


void LED::initialize(int pin)
{
    m_pin = pin;
    initialize();

} // end of "initialize"


bool LED::is_on()
{
    return m_is_on;

} // end of "is_on"


void LED::on()
{
    m_is_on = true;
    digitalWrite(m_pin, HIGH);

} // end of "on"


void LED::off()
{
    m_is_on = false;
    digitalWrite(m_pin, LOW);

} // end of "off"


void LED::toggle(bool turn_on)
{
    // If user wants to turn it on, turn on. Turn off otherwise
    turn_on ? on() : off();

} // end of "toggle"


