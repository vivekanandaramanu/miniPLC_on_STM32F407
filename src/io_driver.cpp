#include <generated.hpp>
#include <stm32f407.h>

using namespace strucpp;

//read plc inputs
extern "C" void plc_read_inputs()
{
    // %IX0.0 → CONTROL_ON_PB
    bool control_on_pb_state = GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_1);
    *(static_cast<bool*>(locatedVars[0].pointer)) = control_on_pb_state;
    // %IX0.1 → EMERGENCY_PB
    bool emergency_pb_state = GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_3);
    *(static_cast<bool*>(locatedVars[1].pointer)) = emergency_pb_state;
    // %IX0.2 → MOTOR_STOP_PB
    bool motor_stop_pb_state = GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_2);
    *(static_cast<bool*>(locatedVars[2].pointer)) = motor_stop_pb_state;
}

//write to plc outputs
extern "C" void plc_write_outputs()
{
    // %QX0.0 → MOTOR_ON
    bool motor_on_state = *(static_cast<bool*>(locatedVars[3].pointer));
    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_15, motor_on_state ? GPIO_PIN_SET : GPIO_PIN_RESET);

    // %QX0.1 → GREEN LAMP
    bool green_lamp_state = *(static_cast<bool*>(locatedVars[4].pointer));
    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_12, green_lamp_state ? GPIO_PIN_SET : GPIO_PIN_RESET);

    // %QX0.2 → RED LAMP
    bool red_lamp_state = *(static_cast<bool*>(locatedVars[5].pointer));
    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_14, red_lamp_state ? GPIO_PIN_SET : GPIO_PIN_RESET);

    // %QX0.3 → ORANGE LAMP
    bool orange_lamp_state = *(static_cast<bool*>(locatedVars[6].pointer));
    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_13, orange_lamp_state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}