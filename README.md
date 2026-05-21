# EmbeddedLib
A CMake based library that contains helper functions and classes. Primarily for STM32 

## Usage

### Adding to Project
To include this library, please `git clone` or `git submodule add` this repo into the `\lib` folder of your project

Then add this to link the library

```cmake
# Add EmbeddedLib
add_subdirectory(lib/EmbeddedLib)

# Add Compile Defines
target_compile_definitions(EmbeddedLib PUBLIC
    # Add user defined symbols
    STM32CUBE
    STM32F446xx
)

# Add MX Include dirs to compile correctly
set(MX_Include_Dirs
    ${CMAKE_SOURCE_DIR}/Core/Inc
    ${CMAKE_SOURCE_DIR}/USB_DEVICE/App
    ${CMAKE_SOURCE_DIR}/USB_DEVICE/Target
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
    ${CMAKE_SOURCE_DIR}/Middlewares/ST/STM32_USB_Device_Library/Core/Inc
    ${CMAKE_SOURCE_DIR}/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include
)

# Link the MX Dirs
target_include_directories(EmbeddedLib
    PUBLIC
        ${MX_Include_Dirs}
)

...

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
    EmbeddedLib
)

```