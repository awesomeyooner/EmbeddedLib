#ifndef SYSTEM_HPP
#define SYSTEM_HPP


#include "EmbeddedLib/util/status.hpp"
#include "EmbeddedLib/watchdog.hpp"


// Forward Declaration
class Watchdog;


enum class SystemState
{
    OK, // Fully functional
    TIMEOUT, // Watchdog not fed
    HALT // Something bad has happened

}; // enum class SystemState


class System
{

    public:

        /**
         * @brief Initialize the system (optional, based on implementation)
         * 
         */
        static void init();
        
        /**
         * @brief Gets the time since epoch in seconds
         * 
         * @return `double` The time since epoch in seconds
         */
        static double get_seconds();

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


}; // class System

#endif // SYSTEM_HPP