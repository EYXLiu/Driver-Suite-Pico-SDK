cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake) # requires PICO_SDK_PATH to be set in bash (export PICO_SDK_PATH=/path)

project(driver_suite_project C CXX ASM)

pico_sdk_init()

add_executable(driver_suite
    src/gpio.c
    src/uart.c
    src/spi.c
    src/i2c.c
    src/timer.c
    src/adc.c
    src/pwm.c
    src/dma.c
    src/system.c
)

target_include_directories(driver_suite PRIVATE include)

target_link_libraries(driver_suite pico_stdlib)

pico_add_extra_outputs(driver_suite)