#ifndef SYSTEM_HPP
#define SYSTEM_HPP


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

    private:

}; // class System

#endif // SYSTEM_HPP