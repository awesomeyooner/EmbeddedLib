#include "EmbeddedLib/devices/led.hpp"


LED::LED(GPIO_TypeDef* gpio_family, uint16_t pin)
{
    m_gpio_family = gpio_family;
    m_pin = pin;
    m_is_on = false;

} // end of "LED"


bool LED::is_on()
{
    return m_is_on;

} // end of "is_on"


void LED::on()
{
    m_is_on = true;
    HAL_GPIO_WritePin(m_gpio_family, m_pin, GPIO_PIN_SET);

} // end of "on"


void LED::off()
{
    m_is_on = false;
    HAL_GPIO_WritePin(m_gpio_family, m_pin, GPIO_PIN_RESET);

} // end of "off"


void LED::toggle(bool turn_on)
{
    // If user wants to turn it on, turn on. Turn off otherwise
    turn_on ? on() : off();

} // end of "toggle"


void LED::toggle()
{
    // If it's on, turn off. If it's not on, turn on
    m_is_on ? off() : on(); 

} // end of "toggle"
