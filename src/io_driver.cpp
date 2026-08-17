#include <generated.hpp>
#include <stm32f407.h>

using namespace strucpp;

//read plc inputs
extern "C" void plc_read_inputs()
{
    // %IX0.0 → CONTROL ON CLEARANCE
    bool CONTROL_ON_CLEARANCE = GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0);
    *(static_cast<bool*>(locatedVars[0].pointer)) = CONTROL_ON_CLEARANCE;
    // %IX0.1 → EMERGENCY
    bool EMERGENCY = GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_1);
    *(static_cast<bool*>(locatedVars[1].pointer)) = EMERGENCY;
    // %IX0.2 → JOG FWD SPEED 1
    bool JOG_FWD_SPEED_1 = GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_2);
    *(static_cast<bool*>(locatedVars[2].pointer)) = JOG_FWD_SPEED_1;
    // %IX0.3 → JOG REV SPEED 1
    bool JOG_REV_SPEED_1 = GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_3);
    *(static_cast<bool*>(locatedVars[3].pointer)) = JOG_REV_SPEED_1;
    //%IX0.4 → JOG FWD SPEED 2
    bool JOG_FWD_SPEED_2 = GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_4);
    *(static_cast<bool*>(locatedVars[4].pointer)) = JOG_FWD_SPEED_2;
    //%IX0.5 → JOG REV SPEED 2
    bool JOG_REV_SPEED_2 = GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_5);
    *(static_cast<bool*>(locatedVars[5].pointer)) = JOG_REV_SPEED_2;
    //%IX0.6 → CARRIAGE FWD
    bool CARRIAGE_FWD = GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_6);
    *(static_cast<bool*>(locatedVars[6].pointer)) = CARRIAGE_FWD;
    //%IX0.7 → CARRIAGE REV
    bool CARRIAGE_REV = GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_7);
    *(static_cast<bool*>(locatedVars[7].pointer)) = CARRIAGE_REV;
   
    //%IX1.0 → JOG MODE
    bool JOG_MODE = GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_0);
    *(static_cast<bool*>(locatedVars[8].pointer)) = JOG_MODE;
    //%IX1.1 → MDI/AUTO
    bool MDI_AUTO = GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_1);
    *(static_cast<bool*>(locatedVars[9].pointer)) = MDI_AUTO;
    //%IX1.2 → SPINDLE DRIVE READY
    bool SPINDLE_DRVE_READY = GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_2);
    *(static_cast<bool*>(locatedVars[10].pointer)) = SPINDLE_DRVE_READY;
    //%IX1.3 → MPCB TRIPPED
    bool MPCB_TRIPPED = GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_3);
    *(static_cast<bool*>(locatedVars[11].pointer)) = MPCB_TRIPPED;
    //%IX1.4 → DOOR OPEN LIMIT
    bool DOOR_OPEN_LIMIT = GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_4);
    *(static_cast<bool*>(locatedVars[12].pointer)) = DOOR_OPEN_LIMIT;
    //%IX1.5 → DOOR CLOSE LIMIT
    bool DOOR_CLOSE_LIMIT = GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_5);
    *(static_cast<bool*>(locatedVars[13].pointer)) = DOOR_CLOSE_LIMIT;
    //%IX1.6 → RESERVED FOR FUTURE
    bool RESERVED_0 = GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_0);
    *(static_cast<bool*>(locatedVars[14].pointer)) = RESERVED_0;
    //%IX1.7 → RESERVED FOR FUTURE
    bool RESERVED_1 = GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_1);
    *(static_cast<bool*>(locatedVars[15].pointer)) = RESERVED_1;
   
    //%IX2.O → CARRIAGE FWD END LIMIT
    bool CARRIAGE_FWD_END_LIMIT = GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_2);
    *(static_cast<bool*>(locatedVars[16].pointer)) = CARRIAGE_FWD_END_LIMIT;
    //%IX2.1 → CARRIAGE REV END LIMIT
    bool CARRIAGE_REV_END_LIMIT = GPIO_ReadFromInputPin(GPIOE, GPIO_PIN_NO_7);
    *(static_cast<bool*>(locatedVars[17].pointer)) = CARRIAGE_REV_END_LIMIT;
    //%IX2.2 → RUN CMD FROM RPI
    bool RUN_CMD_RPI = GPIO_ReadFromInputPin(GPIOE, GPIO_PIN_NO_8);
    *(static_cast<bool*>(locatedVars[18].pointer)) = RUN_CMD_RPI;
    //%IX2.3 → DIRECTION CMD FROM RPI
    bool DIRECTION_CMD_FROM_RPI = GPIO_ReadFromInputPin(GPIOE, GPIO_PIN_NO_9);
    *(static_cast<bool*>(locatedVars[19].pointer)) = RUN_CMD_RPI;
    //%IX2.4 → RESERVED FOR FUTURE
    bool RESERVED_2 = GPIO_ReadFromInputPin(GPIOE, GPIO_PIN_NO_10);
    *(static_cast<bool*>(locatedVars[20].pointer)) = RESERVED_2;
    //%IX2.5 → RESERVED FOR FUTURE
    bool RESERVED_3 = GPIO_ReadFromInputPin(GPIOE, GPIO_PIN_NO_11);
    *(static_cast<bool*>(locatedVars[21].pointer)) = RESERVED_3;
    //%IX2.6 → RESERVED FOR FUTURE
     bool RESERVED_4 = GPIO_ReadFromInputPin(GPIOE, GPIO_PIN_NO_12);
    *(static_cast<bool*>(locatedVars[22].pointer)) = RESERVED_4;
    //%IX2.7 → RESERVED FOR FUTURE
    bool RESERVED_5 = GPIO_ReadFromInputPin(GPIOE, GPIO_PIN_NO_13);
    *(static_cast<bool*>(locatedVars[23].pointer)) = RESERVED_5;
    
}

//write to plc outputs
extern "C" void plc_write_outputs()
{
    // %QX0.0 → CONTROL ON
    bool CONTROL_ON = *(static_cast<bool*>(locatedVars[24].pointer));
    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_15, CONTROL_ON ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // %QX0.1 → SPINDLE BLOWER MOTOR ON
    bool SPINDLE_BLOWER_MOTOR_ON = *(static_cast<bool*>(locatedVars[25].pointer));
    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_11, SPINDLE_BLOWER_MOTOR_ON ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // %QX0.2 → SPINDLE BRAKE RELEASE
    bool SPINDLE_BRAKE_RELEASE = *(static_cast<bool*>(locatedVars[26].pointer));
    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_10, SPINDLE_BRAKE_RELEASE ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // %QX0.3 → CARRIAGE FWD OUTPUT
    bool CARRIAGE_FWD_OUTPUT = *(static_cast<bool*>(locatedVars[27].pointer));
    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_9, CARRIAGE_FWD_OUTPUT ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // %QX0.4 → CARRIAGE REV OUTPUT
    bool CARRIAGE_REV_OUTPUT = *(static_cast<bool*>(locatedVars[28].pointer));
    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_8, CARRIAGE_REV_OUTPUT ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // %QX0.5 → DRIVE ENABLE- 38
    bool QX0_5 = *(static_cast<bool*>(locatedVars[29].pointer));
    GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_15, QX0_5 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // %QX0.6 → DRIVE RUN COMMAND - 37
    bool DRIVE_ENABLE_38 = *(static_cast<bool*>(locatedVars[30].pointer));
    GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_14, DRIVE_ENABLE_38 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // %QX0.7 → DIRECTION COMMAND - 36
    bool DIRECTION_COMMAND_36 = *(static_cast<bool*>(locatedVars[31].pointer));
    GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_13, DIRECTION_COMMAND_36 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    
    // %QX1.0 → JOG SPEED 2-39
    bool JOG_SPEED_2_39 = *(static_cast<bool*>(locatedVars[32].pointer));
    GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_12, JOG_SPEED_2_39 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // %QX1.1 → AUTO/MDI TO RPI
    bool AUTO_MDI_TO_RPI = *(static_cast<bool*>(locatedVars[33].pointer));
    GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_11, AUTO_MDI_TO_RPI ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // %QX1.2 → RESERVED FOR FUTURE OUTPUT
    bool RESERVED_6 = *(static_cast<bool*>(locatedVars[34].pointer));
    GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_10, RESERVED_6 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    //%QX1.3 → RESERVED FOR FUTURE OUTPUT
    bool RESERVED_7 = *(static_cast<bool*>(locatedVars[35].pointer));
    GPIO_WriteToOutputPin(GPIOE, GPIO_PIN_NO_15, RESERVED_7 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // %QX1.4 → RESERVED FOR FUTURE OUTPUT
    bool RESERVED_8 = *(static_cast<bool*>(locatedVars[36].pointer));
    GPIO_WriteToOutputPin(GPIOE, GPIO_PIN_NO_14, RESERVED_8 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // %QX1.5 → RED
    bool RED = *(static_cast<bool*>(locatedVars[37].pointer));
    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_14, RED ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // %QX1.6 → ORANGE
    bool ORANGE = *(static_cast<bool*>(locatedVars[38].pointer));
    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_13, ORANGE ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // %QX1.7 → GREEN
    bool GREEN = *(static_cast<bool*>(locatedVars[39].pointer));
    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_12, GREEN ? GPIO_PIN_SET : GPIO_PIN_RESET);
}