#ifndef LED_HPP
#define LED_HPP


#include "gpio.h"

#include <stm32f446xx.h>


class LED
{

    public:

        LED(GPIO_TypeDef* gpio_family, uint16_t pin);

        /**
         * @brief Gets if the LED is on or not
         * 
         * @return `bool` True if the LED is on, false otherwise 
         */
        bool is_on();

        /**
         * @brief Turns on the LED
         * 
         */
        void on();

        /**
         * @brief Turns off the LED
         * 
         */
        void off();

        /**
         * @brief Turns the LED on if true, off if false
         * 
         * @param turn_on `bool` True to turn on, false to turn off
         */
        void toggle(bool turn_on);

        /**
         * @brief Toggles the LED. If it's on, it turns off. If it's off,
         * it turns on
         * 
         */
        void toggle();

    private:

        // The GPIO Family (The second letter in PA, PB, PC, PD)
        GPIO_TypeDef* m_gpio_family = nullptr;

        // The Pin Number (The number part of PA8, PC1)
        uint16_t m_pin;

        // Whether or not the LED is on
        bool m_is_on;

}; // class LED


#endif // LED_HPP