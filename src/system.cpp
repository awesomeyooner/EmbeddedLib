#include "EmbeddedLib/system.hpp"

#include "stm32f4xx_hal.h"


using namespace status_utils;


// Instantiate the Watchdog timer
Watchdog System::m_watchdog = Watchdog();


void System::init()
{
    // Nothing to be done for now

} // end of "init()"


double System::get_seconds()
{
    return (double)HAL_GetTick() / 1000.0;

} // end of "get_seconds()"


Watchdog& System::get_watchdog()
{
    return m_watchdog;

} // end of "get_watchdog()"


void System::set_state(SystemState state)
{
    m_state = state;

} // end of "set_state(SystemState)"


SystemState System::get_state()
{
    return m_state;

} // end of "get_state()"


bool System::is_OK()
{
    return m_state == SystemState::OK;

} // end of "is_OK()"


void System::update()
{
    m_watchdog.update();

    switch(m_state)
    {
        case SystemState::OK:
        {
            if(!m_watchdog.is_OK())
                m_state = SystemState::TIMEOUT;

            break;
        }
        
        case SystemState::TIMEOUT:
        {
            if(m_watchdog.is_OK())
                m_state = SystemState::OK;

            break;
        }

        case SystemState::HALT:
        {
            // Do nothing for now
            
            break;
        }
    }

} // end of "update()"


void System::feed(double timestamp_s)
{
    m_watchdog.feed(timestamp_s);

} // end of "feed(double)"


void System::feed()
{
    m_watchdog.feed();

} // end of "feed()"
