# EmbeddedLib
A PlatformIO based library that contains helper functions and classes 

## Usage

### Adding to Project
To include this library, please `git clone` or `git submodule add` this repo into the `\lib` folder of your project

Then add this to link the library

```ini
lib_deps = 
    symlink://lib/EmbeddedLib
```

### Using with STM32

When using the STM32Cube HAL code, please include this in the build flags to compile STM32 specific code

```ini
build_flags =
  -D STM32CUBE
  -Wl,-u_printf_float ; (optional) since we're here, use this flag to output floats to the monitor
```