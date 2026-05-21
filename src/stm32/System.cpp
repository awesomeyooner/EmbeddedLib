#ifdef STM32CUBE


#include "EmbeddedLib/System.hpp"

#include "stm32f4xx_hal.h"


void System::init()
{
    // Nothing to be done for now

} // end of "init()"



double System::get_seconds()
{
    return (double)HAL_GetTick() / 1000.0;

} // end of "get_seconds()"


#endif // STM32CUBE