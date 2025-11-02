# Driver Suite for Raspberry Pi Pico
A modular, hardware-abstraction driver suite for microcontrollers, designed around the Raspberry Pi Pico SDK. Developed in C with CMake. <br/>
Bare-metal implementation avaliable [here](https://github.com/EYXLiu/Driver-Suite-Bare-Metal)

# Features
- GPIO (input and output pins; read inputs (buttons, sensors) and write outputs (LEDs, relays))
- UART (Asyncronous communication over tx/rx (PCS,sensors, MCUS))
- SPI (Communicates with SPI peripherals (displays, memory chips, sensors))
- I2C (Communicates with devices over two wires (SDA, SCL) (sensors, EEPROMS, RTCS))
- Timer (Precise timings, periodic events, counters)
- ADC (Analog voltages to digital numbers (potentiometers, light, temperature))
- PWM (Generates signales of variable duty cycles (motor control, LED brightness, audio signals))
- DMA (Transfer data between memory and peripherals without CPU (SPI data streaming or ADC sampling))
- System (System clocks, peripherals, watchdog)

# Design highlights
Modular architecture (similar to pico-sdk) <br/>
User-space APIs (high level abstraction) <br/>
Simulator tested (using Wokwi and PlatformIO -> `diagram.json` and `main.c` can be found in `/examples`) <br/>
CMake Build (Easy to build and integrate accross other microcontroller systems) <br/>

# To compile
1. In `c_cpp_properties.json` in `.vscode`, replace the path to the `pico-sdk` folder with the path to your pico-sdk folder <br/>
  Account for dependancies <br/>
2. Run cmake to build <br/>
3. Include the drivers in the project and initialize peripherals with provided APIs <br/>
