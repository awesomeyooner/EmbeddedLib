#include "EmbeddedLib/watchdog.hpp"


using namespace status_utils;


Watchdog::Watchdog(double timeout_s)
{
    m_timeout_s = timeout_s;

} // end of "Watchdog(double)"


StatusCode Watchdog::update()
{
    double current_timestamp_s = System::get_seconds();

    double delta_time_s = current_timestamp_s - m_prev_timestamp_s;

    // If the previous timestamp is too old
    // Then watchdog is not fed
    if(delta_time_s > m_timeout_s)
    {
        m_is_fed = false;

        return StatusCode::ERROR;
    }

    m_is_fed = true;

    return StatusCode::OK;

} // end of "update()"


void Watchdog::feed(double timestamp_s)
{
    m_prev_timestamp_s = timestamp_s;

    update();

} // end of "feed(double)"


void Watchdog::feed()
{
    feed(System::get_seconds());

} // end of "feed()"


bool Watchdog::is_OK()
{
    return m_is_fed;

} // end of "is_OK()"