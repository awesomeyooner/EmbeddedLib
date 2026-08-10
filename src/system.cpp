#include "EmbeddedLib/system.hpp"


using namespace status_utils;


// Instantiate watchdog timer
Watchdog System::m_watchdog = Watchdog();


void System::init()
{
    enable_DWT();

} // end of "init()"


void System::enable_DWT()
{
    // Enable the trace and debug block
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    // Reset the cycle counter
    DWT->CYCCNT = 0;

    // Enable the cycle counter
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

} // end of "enable_DWT()"


double System::get_seconds()
{
    return (double)HAL_GetTick() / 1000.0;

} // end of "get_seconds()"


double System::get_seconds(bool use_DWT)
{
    if(use_DWT)
    {
        uint32_t counts = get_DWT_count();

        // In a perfect world, counts should never decrease, but in reality it overflows
        // So we can tell if it overflowed by checking if it did decrease
        // If the DWT overflowed
        // Then track it
        if(counts < m_prev_DWT_count)
            m_num_DWT_overflows++;

        // Update the previous counts since we're done checking logic
        m_prev_DWT_count = counts;

        // The current seconds measured by the DWT at an "ambiguous" timepoint
        double ambi_seconds = (double)counts / (double)SystemCoreClock;

        // The amount of time since epoch accounting for the overflows
        // The value of an overflow is UINT32_MAX, and that value divided by SystemCoreClock gives seconds
        double overflowed_seconds = (double)m_num_DWT_overflows * UINT32_MAX / (double)SystemCoreClock;

        // Add the two
        return ambi_seconds + overflowed_seconds;
    }
    else
        return get_seconds();

} // end of "get_seconds(bool)"


uint32_t System::get_milliseconds()
{
    return HAL_GetTick();

} // end of "get_milliseconds()"


uint32_t System::get_nanoseconds()
{
    uint32_t counts = get_DWT_count();

    // uint64_t = unsigned long long (ULL)
    // Doing this ensures no loss in precision
    // Nano is 10^9, 9 zeros
    // DWT->CYCNT updates every system clock, so counts / SystemCoreClock is in seconds
    return (uint32_t)((uint64_t)counts * 1000000000ULL / SystemCoreClock);

} // end of "get_nanoseconds()"


uint32_t System::get_DWT_count()
{
    return DWT->CYCCNT;

} // end of "get_DWT_count()"


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
