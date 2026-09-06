cmake_minimum_required(VERSION 3.12)

project( EmbeddedLib LANGUAGES C CXX )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Base source files with no / minimal include headers outside of std
set( SRC_FILES

    src/system.cpp
    src/watchdog.cpp
    src/status.cpp

    # /util
    src/util/string_formatter.cpp    

    # /math
    src/math/math_util.cpp
    src/math/vector2d.cpp

)

# `gpio.h` Dependents
    option(EMBEDDEDLIB_BUILD_GPIO
        "Compile code that uses `gpio.h`"
        ON
    )

    if(EMBEDDEDLIB_BUILD_GPIO)
        list(APPEND SRC_FILES
            # /devices
            src/devices/gpio_device.cpp
            src/devices/led.cpp
        )
    endif()

# `tim.h` Dependents
    option(EMBEDDEDLIB_BUILD_TIMER
        "Compile code that uses `tim.h`"
        ON
    )

    if(EMBEDDEDLIB_BUILD_TIMER)
        list(APPEND SRC_FILES
            # /devices
            src/devices/timer_device.cpp
            src/devices/ws2812b.cpp
        )
    endif()

# `adc.h` Dependents
    option(EMBEDDEDLIB_BUILD_ADC
        "Compile code that uses `adc.h`"
        ON
    )

    if(EMBEDDEDLIB_BUILD_ADC)
        list(APPEND SRC_FILES
            # /devices
            src/devices/adc_device.cpp
        )
    endif()

# `i2c.h` Dependents
    option(EMBEDDEDLIB_BUILD_I2C
        "Compile code that uses `i2c.h`"
        ON
    )

    if(EMBEDDEDLIB_BUILD_ADC)
        list(APPEND SRC_FILES
            # /devices
            src/devices/lcd.cpp
        )
    endif()

# === Main Library ===
add_library(${PROJECT_NAME}
    ${SRC_FILES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Add the test executables only if this project is at the top level (aka not used with add_subdirectory)
if(PROJECT_IS_TOP_LEVEL)
    add_executable(Test test/test.cpp)
    target_link_libraries(Test PRIVATE 
        ${PROJECT_NAME}
    )
endif()