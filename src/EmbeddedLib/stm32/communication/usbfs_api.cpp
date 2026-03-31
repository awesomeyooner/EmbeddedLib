#include "EmbeddedLib/stm32/communication/usbfs_api.hpp"
#include "EmbeddedLib/communication/Serial.hpp"


bool USBFS_on_receive(uint8_t* buffer, uint32_t length)
{
    // Convert dynamic array to vector
    std::vector<uint8_t> bytes(buffer, buffer + length);

    // Call the C++ version
    return Serial::on_receive(bytes);

} // end of "USBFS_on_receive(uint8_t*, uint32_t*)"
