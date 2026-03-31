#ifdef STM32CUBE

#ifndef SERIAL_HPP
#define SERIAL_HPP

#include "EmbeddedLib/System.hpp"
#include "EmbeddedLib/util/string_util.hpp"

#include <string>
#include <vector>
#include <functional>


class Serial
{

    public:

        static void configure_callback(std::function<bool(const std::vector<uint8_t>&)> callback);

        static bool transmit_bytes(const std::vector<uint8_t>& bytes);

        static bool on_receive(uint8_t* buffer, uint32_t length);

        static bool print(std::string text);

        static bool print(double data);

        static bool println(std::string text);

        static bool println(double data);

        static bool info(std::string text);

        static bool info(double data);

        static bool debug(std::string text);

        static bool debug(double data);

        static bool error(std::string text);

        static bool error(double data);

    private:

        static std::vector<uint8_t> m_read_buffer;

        static std::function<bool(const std::vector<uint8_t>&)> m_receive_callback;


}; // class Serial


#endif // SERIAL_HPP

#endif // STM32CUBE