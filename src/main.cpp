#include <stm32f407.h>
#include <generated.hpp>
#include <stdint.h>
#include <stddef.h>

using namespace strucpp;

// Create config → contains INSTANCE0
Configuration_CONFIG0 config;

// Hardware drivers from plc_gpio_init.c / uart_dma.cpp
extern "C" void PLC_GPIO_Init();
extern "C" void software_delay(void);

// IO mapping routines from io_driver.cpp file
extern "C" void plc_read_inputs();
extern "C" void plc_write_outputs();

extern "C" int main(void)
{
    // 🔹 1. Initialize Microcontroller Hardware Clocks & Pins
    PLC_GPIO_Init();
    
    while (1)
    {
        try {
            // 🔹 3. Physical Input Scanning
            plc_read_inputs();

            // 🔹 4. Solve PLC Ladder Logic Cycle
            // This natively updates the live state variables inside the locatedVars array
            config.INSTANCE0.run();

            // 🔹 5. Physical Output Updating
            plc_write_outputs();

            software_delay();
        }
        catch (...) { 
        /* 
         * ===============================================================
         * INDUSTRIAL PLC LAYER 2 SAFETY NET (Layer 1 Safe State Halt Loop)
         * ===============================================================
         * If the processor ever slips past our try-catch block and enters 
         * here, the system is in an unhandled, critical failure state.
         */
         
        // 1. FORCE SAFETY: Add your code here to force physical PLC outputs LOW!
         GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_15,0);
         GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_11,0);
         GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_10,0);
         GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_9, 0);
         GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_8, 0);
         GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_15,0);
         GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_14,0);
         GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_13,0);
         GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_12,0);
         GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_11,0);
         GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_10,0);
         GPIO_WriteToOutputPin(GPIOE, GPIO_PIN_NO_15,0);
         GPIO_WriteToOutputPin(GPIOE, GPIO_PIN_NO_14,0);
         GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_14,0);
         GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_13,0);
         GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_12,0);

         uint8_t delay2;
         delay2++;   //1 cycle gap

        // 2. ERROR VISIBILITY: Add code here to turn on a hardware Fault/Error LED
        GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_13);

        // 3. HARDWARE CAPTURE: Trap the CPU instantly to stop machine movements.
        // This allows an ST-Link debugger to connect and read out the memory state.
            while (1) { __asm("NOP"); }
        }
    }
}

