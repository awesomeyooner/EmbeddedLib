#include "EmbeddedLib/devices/gpio_device.hpp"


using namespace std;


GPIODevice::GPIODevice(GPIO_TypeDef* gpio_family, uint16_t pin)
{
    m_gpio_family = gpio_family;
    m_pin = pin;

} // end of "GPIODevice(GPIO_TypeDef*, uint16_t)"


void GPIODevice::attach_callback(function<void()> callback)
{
    m_callback = callback;

} // end of "attach_callback(function<void()>)"


bool GPIODevice::on_EXTI_callback(uint16_t pin)
{
    if(pin == m_pin)
    {
        // If the callback is assigned
        // Then call it
        if(m_callback != nullptr)
            m_callback();

        // Return true since the pin was the correct one
        return true;
    }

    // Return false since it was not the right pin
    return false;

} // end of "on_EXTI_callbacK(uint16_t)"


GPIO_PinState GPIODevice::get_state()
{
    return HAL_GPIO_ReadPin(m_gpio_family, m_pin);

} // end of "get_state()"


bool GPIODevice::is_high()
{
    // SET is HIGH, RESET is LOW
    return get_state() == GPIO_PIN_SET;

} // end of "is_high()"


bool GPIODevice::is_low()
{
    // SET is HIGH, RESET is LOW
    return get_state() == GPIO_PIN_RESET;

} // end of "is_low()"


void GPIODevice::set_high()
{
    set(GPIO_PIN_SET);

} // end of "set_high()"


void GPIODevice::set_low()
{
    set(GPIO_PIN_RESET);

} // end of "set_low()"


void GPIODevice::toggle(bool should_set_high)
{
    should_set_high ? set_high() : set_low();

} // end of "toggle(bool)"


void GPIODevice::toggle()
{
    // If pin is high, toggle(false) will be called, setting it low
    // If pin is low, toggle(true) will be called, setting it high
    toggle(!is_high());

} // end of "toggle()"


void GPIODevice::set(GPIO_PinState state)
{
    HAL_GPIO_WritePin(m_gpio_family, m_pin, state);

} // end of "set(GPIO_PinState)"