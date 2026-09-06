#ifndef GPIO_DEVICE_HPP
#define GPIO_DEVICE_HPP


#include <functional>

#include "EmbeddedLib/status.hpp"

#include "gpio.h"

#include "stm32f4xx_hal_gpio.h"
#include <stm32f446xx.h>


class GPIODevice
{

    public:

        /**
         * @brief Creates a new GPIO pin wrapper with the given GPIO Family and pin number
         * 
         * Example:
         * 
         * `PA13` <-> `GPIODevice(GPIOA, GPIO_PIN_13)`
         * 
         * @param gpio_family `GPIO_TypeDef*`
         * @param pin `uint16_t`
         */
        GPIODevice(GPIO_TypeDef* gpio_family, uint16_t pin);

        /**
         * @brief Attach the callback function to run when the corresponding pin is called in
         * `on_EXTI_callback`. 
         * 
         * To use EXTI, first enable your pin as `GPIO_EXTIx` in `CubeMX`, then under `System Core` on the left click `GPIO`, 
         * then `NVIC`, then enable the EXTI interrupt
         * 
         * @param callback `std::function<void()>`
         */
        void attach_callback(std::function<void()> callback);

        /**
         * @brief Call this inside `HAL_GPIO_EXTI_Callback`. This will automatically checn if `pin` is equal to the internal pin
         * assigned and call the callback accordingly. If the pin is not the right one, nothing will happen
         * 
         * To use this, simple add
         * 
         * ```
         * void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
         * {
         *     my_gpio.on_EXTI_callback(GPIO_Pin);
         *
         * } // end of "HAL_GPIO_EXTI_Callback(uint16_t)"
         * ```
         * 
         * @param pin `uint16_t` The GPIO pin that triggered the interrupt
         * @return `bool` `true` if the pin was the right pin. `false` otherwise
         */
        bool on_EXTI_callback(uint16_t pin);

        /**
         * @brief Gets the PinState of this pin
         * 
         * `GPIO_PIN_SET` for `HIGH`
         * 
         * `GPIO_PIN_RESET` for `LOW`
         * 
         * @return `GPIO_PinState` 
         */
        GPIO_PinState get_state();

        /**
         * @brief Gets if the pin is set to high or not
         * 
         * @return `true` If the pin state is `GPIO_PIN_SET`
         * @return `false` If the pin state is `GPIO_PIN_RESET`
         */
        bool is_high();

        /**
         * @brief Gets if the pin is set to low or not
         * 
         * @return `true` If the pin state is `GPIO_PIN_RESET`
         * @return `false` If the pin state is `GPIO_PIN_SET`
         */
        bool is_low();

        /**
         * @brief Set the pin `HIGH`
         * 
         */
        void set_high();

        /**
         * @brief Set the pin `LOW`
         * 
         */
        void set_low();

        /**
         * @brief Sets the pin depending on the boolean given. `True` sets the
         * pin `HIGH`, `False` sets the pin `LOW`
         * 
         * @param should_set_high `bool` Whether or not to set the pin high
         */
        void toggle(bool should_set_high);

        /**
         * @brief Toggles the pin so that if the pin is `HIGH`, it'll be set to `LOW`
         * and vice versa
         * 
         */
        void toggle();

    private:

        // The GPIO Family, i.e. PA13 is `GPIOA`
        GPIO_TypeDef* m_gpio_family = nullptr;

        // The GPIO pin number, i.e. PA13 is `GPIO_PIN_13`
        uint16_t m_pin = 0;

        // The (optional) callback function when using GPIO_EXTI
        std::function<void()> m_callback = nullptr;

        /**
         * @brief HAL wrapper to set the pin
         * 
         * @param state `GPIO_PinState` `GPIO_PIN_SET` for `HIGH` or `GPIO_PIN_RESET` for `LOW`
         */
        void set(GPIO_PinState state);

}; // class GPIODevice


#endif // GPIO_DEVICE_HPP