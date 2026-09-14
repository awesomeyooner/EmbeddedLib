# SPI EEPROM

This driver is based off of the [ST M95320-W](https://www.st.com/resource/en/datasheet/m95320-w.pdf)

## Usage

```c++
#include "core.hpp"

#include <cstdint>

#include "WireLib/communication/protocols/serial_interface.hpp"

#include "EmbeddedLib/devices/gpio_device.hpp"

#include "WireLib/util/byte_converter.hpp"

#include "EmbeddedLib/devices/eeprom/eeprom_spi.hpp"


GPIODevice led = GPIODevice(GPIOC, GPIO_PIN_1);
EEPROMSPI eeprom = EEPROMSPI(&hspi2, GPIOB, GPIO_PIN_12);


void init()
{
    // Wait for COM Port to open
    while(!Serial.is_connected())
    {
        HAL_Delay(100);
    }

    // Freeze code if EEPROM isn't connected
    while(!eeprom.is_connected())
    {
        HAL_Delay(100)

        led.set_high();
    }

    // Write the data starting at address 0
    uint16_t address = 0;

    // Data to write
    double data = 150.15;

    // Write data to EEPROM
    eeprom.write_bytes(address, ByteConverter::to_bytes<double>(data));

    // Read data from EEPROM
    double read = ByteConverter::from_bytes<double>(
        eeprom.read_bytes(address, sizeof(double))
    );

    HAL_Delay(500);

    // Print the read data
    Serial.println("Hello World!");
    Serial.println(read, 9);

} // end of "init()"


void update()
{

    
} // end of "update()"

```