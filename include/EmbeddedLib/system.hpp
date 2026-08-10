#ifndef SYSTEM_HPP
#define SYSTEM_HPP


#include "EmbeddedLib/status.hpp"
#include "EmbeddedLib/watchdog.hpp"

#include "stm32f4xx_hal.h"


// Forward Declaration
class Watchdog;


enum class SystemState
{
    OK, // Fully functional
    TIMEOUT, // Watchdog not fed
    HALT // Something bad has happened

}; // enum class SystemState


/**
 * @brief Contains basic functionalities like watchdog timer and methods to get time.
 * 
 * `get_seconds()` will return the time in seconds with millisecond precision using `HAL_GetTick()`
 * 
 * In order to use `get_nanoseconds()`, `enable_DWT()` or `init()` must be called 
 * 
 * 
 */
class System
{

    public:

        /**
         * @brief Initialize the system (optional, based on implementation)
         * 
         */
        static void init();

        /**
         * @brief Enable the DWT (Data Watchpoint and Trace) Cycle Counter. You must enable this
         * in order to use `get_nanoseconds()`
         * 
         */
        static void enable_DWT();
        
        /**
         * @brief Gets the time since epoch in seconds
         * 
         * @return `double` The time since epoch in seconds
         */
        static double get_seconds();

        /**
         * @brief Gets the time since epoch in seconds with the option to use DWT for ~nanosecond precision
         * 
         * @param use_DWT `bool` Set to true to use DWT to get ~nanosecond precision. `init()` or `enable_DWT()` must be called
         * to use this feature. Set to true for standard millisecond precision 
         * @return `double` 
         */
        static double get_seconds(bool use_DWT);

        /**
         * @brief Gets the time since epoch in milliseconds. This is a wrapper for `HAL_GetTicK()`
         * 
         * @return `double` The time since epoch in milliseconds 
         */
        static uint32_t get_milliseconds();

        /**
         * @brief Get the DWT cycle count in nanoseconds. This will overflow often, so only use this
         * to measure small increments of time. `init()` or `enable_DWT()` must be called in order to use this
         * 
         * @return `uint32_t` An arbitrary timepoint in nanoseconds 
         */
        static uint32_t get_nanoseconds();

        /**
         * @brief Get the raw DWT cycle count
         * 
         * @return `uint32_t` The raw counts. Dividing this by `SystemCoreClock` gives you seconds, since
         * DWT count updates every System clock tick. `init()` or `enable_DWT()` must be called in order to use this
         */
        static uint32_t get_DWT_count();

        /**
         * @brief Get the main watchdog
         * 
         * @return `Watchdog&` 
         */
        static Watchdog& get_watchdog();

        static void set_state(SystemState state);

        /**
         * @brief Get the internal state
         * 
         * @return `SystemState` 
         */
        static SystemState get_state();

        /**
         * @brief Shorthand for `get_state() == SystemState::OK`
         * 
         * @return `true` 
         * @return `false` 
         */
        static bool is_OK();

        /**
         * @brief Check if the watchdog is OK and update the state
         * accordingly
         * 
         */
        static void update();

        /**
         * @brief Feed the watchdog the given timestamp in seconds
         * 
         * @param timestamp_s `double` Timestamp in seconds
         */
        static void feed(double timestamp_s);

        /**
         * @brief Feed the watchdog using the current timepoint
         * 
         */
        static void feed();

    private:

        // State of the system
        static inline SystemState m_state = SystemState::TIMEOUT;

        // Primary watchdog for the system
        static Watchdog m_watchdog;

        // The previous DWT count from the last update call
        static inline uint32_t m_prev_DWT_count = 0;

        // The number of times the DWT count has overflowed
        static inline uint32_t m_num_DWT_overflows = 0;


}; // class System

#endif // SYSTEM_HPP