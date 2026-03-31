#include "EmbeddedLib/System.hpp"

#include "adc.h"
#include "can.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

#include "usbd_cdc_if.h"


void System::init()
{
    // Nothing to be done for now

} // end of "init()"



double System::get_seconds()
{
    return (double)HAL_GetTick() / 1000.0;

} // end of "get_seconds()"