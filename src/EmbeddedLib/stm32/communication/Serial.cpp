#ifdef STM32CUBE

#include "EmbeddedLib/stm32/communication/Serial.hpp"

#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "usbd_def.h"


// Initialize the members
std::vector<uint8_t> Serial::m_read_buffer;

std::function<bool(const std::vector<uint8_t>&)> Serial::m_receive_callback;


void Serial::configure_callback(std::function<bool(const std::vector<uint8_t>&)> callback)
{
    m_receive_callback = callback;

} // end of "configure_callback(std::function<bool(const std::vector<uint8_t>&)>)"


bool Serial::transmit_bytes(const std::vector<uint8_t>& bytes)
{
    return CDC_Transmit_FS(const_cast<uint8_t*>(bytes.data()), bytes.size()) == USBD_OK;

} // end of "transmit(bytes(const std::vector<uint8_t>&))"


bool Serial::on_receive(const std::vector<uint8_t>& bytes)
{
    // Fill the read buffer
    m_read_buffer = bytes;

    // If the callback is set
    // Then call it
    if(m_receive_callback)
        return m_receive_callback(m_read_buffer);

    return true;

} // end of "on_receive(uint8_t*, uint32_t*)"


bool Serial::print(std::string text)
{
    // Convert to byte vector
    std::vector<uint8_t> buffer(text.begin(), text.end());

    // Send the data over
    // Return true if trasmit was USBD_OK
    return transmit_bytes(buffer);

} // end of "print(std::string)"


bool Serial::print(double data)
{
    // Convert data to string and send it over
    return print(std::to_string(data));

} // end of "print(double)"


bool Serial::println(std::string text)
{
    // Add carriage return and newline
    return print(text + "\r\n");

} // end of println(std::string)


bool Serial::println(double data)
{
    // Convert data to string and send it over
    return println(std::to_string(data));
    
} // end of println(double)


bool Serial::info(std::string text)
{
    string_util::timestamped_header("INFO", text);

} // end of "info(std::string)"


bool Serial::info(double data)
{
    info(std::to_string(data));

} // end of "info(double)"


bool Serial::debug(std::string text)
{
    string_util::timestamped_header("DEBUG", text);

} // end of "debug(std::string)"


bool Serial::debug(double data)
{
    debug(std::to_string(data));

} // end of "debug(double)"


bool Serial::error(std::string text)
{
    string_util::timestamped_header("ERROR", text);

} // end of "error(std::string)"


bool Serial::error(double data)
{
    error(std::to_string(data));

} // end of "error(double)"

#endif // STM32CUBE