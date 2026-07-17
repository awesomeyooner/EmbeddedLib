#ifndef WATCHDOG_HPP
#define WATCHDOG_HPP


#include "EmbeddedLib/util/status.hpp"
#include "EmbeddedLib/system.hpp"


class Watchdog
{
    public:

        /**
         * @brief Create a new Watchdog with the default timeout
         * 
         */
        Watchdog() = default;

        /**
         * @brief Create a new Watchdog with the given timeout
         * 
         * @param timeout_s `double` The timeout in seconds
         */
        Watchdog(double timeout_s);

        /**
         * @brief Regularly call this to check if the watchdog 
         * has been fed for not
         * 
         * @return `status_utils::StatusCode` `OK` if watchdog is fed,
         * `ERROR` if in timeout 
         */
        status_utils::StatusCode update();

        /**
         * @brief Feed the watchdog a new timestamp
         * 
         * @param timestamp_s `double` The new timestamp in seconds
         */
        void feed(double timestamp_s);

        /**
         * @brief Feed the watchdog the current timestamp
         * 
         */
        void feed();

        /**
         * @brief Gets if the watchdog has been fed / is OK
         * 
         * @return `true` If fed
         * @return `false` If in TIMEOUT 
         */
        bool is_OK();

    private:

        // Default length of TIMEOUT
        const double DEFAULT_TIMEOUT_s = 0.05; // 50 ms

        // How long to wait until the system is in TIMEOUT
        double m_timeout_s = DEFAULT_TIMEOUT_s; 

        // Previous timestamp in seconds
        double m_prev_timestamp_s = 0;

        // If the watchdog is fed
        bool m_is_fed = false;


}; // class Watchdog


#endif // WATCHDOG_HPP