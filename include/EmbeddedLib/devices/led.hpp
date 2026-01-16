#ifndef LED_HPP
#define LED_HPP

#include <Arduino.h>

class LED
{

    public:

        LED();

        LED(int pin);

        /**
         * @brief Configures the pinmode to output
         * 
         */
        void initialize();

        /**
         * @brief Configures the pinmode of the specific pin to output
         * 
         * @param _pin `int` The pin to use
         */
        void initialize(int pin);

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
        int m_pin;

        bool m_is_on;

}; // class LED


#endif // LED_HPP