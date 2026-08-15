#include<stm32f407.h>

void PLC_GPIO_Init();
void software_delay(void);

//software delay
void software_delay(void){
    for(uint32_t i = 0;i<500000; i++);
}

void PLC_GPIO_Init(){
/*
GPIO INPUTS AND OUTPUTS
*/
    //plc inputs
    GPIO_Handle_t MOTOR_ON_PB;
    GPIO_Handle_t EMERGENCY_PB;
    GPIO_Handle_t MOTOR_STOP_PB;

    //plc outputs
    GPIO_Handle_t MOTOR_ON;
    GPIO_Handle_t GREEN_LAMP;
    GPIO_Handle_t RED_LAMP;
    GPIO_Handle_t ORANGE_LAMP;

/*
GPIO PORT AND PIN CONFIGURATIONS
*/
    //port and pin configurations for MOTOR_ON_PB
    MOTOR_ON_PB.pGPIOx = GPIOA;
    MOTOR_ON_PB.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
    MOTOR_ON_PB.GPIO_PinConfig.GPIO_PinMode = GPIO_PIN_MODE_IN;
    MOTOR_ON_PB.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PD;

    //port and pin configurations for EMERGENCY_PB
    EMERGENCY_PB.pGPIOx = GPIOA;
    EMERGENCY_PB.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
    EMERGENCY_PB.GPIO_PinConfig.GPIO_PinMode = GPIO_PIN_MODE_IN;
    EMERGENCY_PB.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PD;

    //port and pin configurations for MOTOR_STOP_PB
    MOTOR_STOP_PB.pGPIOx = GPIOA;
    MOTOR_STOP_PB.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
    MOTOR_STOP_PB.GPIO_PinConfig.GPIO_PinMode = GPIO_PIN_MODE_IN;
    MOTOR_STOP_PB.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PD;
    
    //port and pin configurations for MOTOR_ON
    MOTOR_ON.pGPIOx = GPIOD;
    MOTOR_ON.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
    MOTOR_ON.GPIO_PinConfig.GPIO_PinMode = GPIO_PIN_MODE_OUT;
    MOTOR_ON.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_SPEED_FAST;
    MOTOR_ON.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OP_TYPE_PP;
    MOTOR_ON.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_NO_PUPD;

    //port and pin configurations for GREEN_LAMP
    GREEN_LAMP.pGPIOx = GPIOD;
    GREEN_LAMP.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
    GREEN_LAMP.GPIO_PinConfig.GPIO_PinMode = GPIO_PIN_MODE_OUT;
    GREEN_LAMP.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_SPEED_FAST;
    GREEN_LAMP.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OP_TYPE_PP;
    GREEN_LAMP.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_NO_PUPD;
    
    //port and pin configurations for RED_LAMP
    RED_LAMP.pGPIOx = GPIOD;
    RED_LAMP.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
    RED_LAMP.GPIO_PinConfig.GPIO_PinMode = GPIO_PIN_MODE_OUT;
    RED_LAMP.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_SPEED_FAST;
    RED_LAMP.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OP_TYPE_PP;
    RED_LAMP.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_NO_PUPD;

    //port and pin configurations for ORANGE_LAMP
    ORANGE_LAMP.pGPIOx = GPIOD;
    ORANGE_LAMP.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    ORANGE_LAMP.GPIO_PinConfig.GPIO_PinMode = GPIO_PIN_MODE_OUT;
    ORANGE_LAMP.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_SPEED_FAST;
    ORANGE_LAMP.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OP_TYPE_PP;
    ORANGE_LAMP.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_NO_PUPD;

/*
PLC GPIO CLOCK ENABLE & INITILALIZATION FUNCTIONS
*/
    
    //GPIO pheripheral clock enable 
    GPIO_PeriClockControl(GPIOA,ENABLE);
    GPIO_PeriClockControl(GPIOD,ENABLE);
    
    volatile uint32_t delay1 = 0;
    delay1++;
    delay1++;

    //GPIO pin Initialization
    GPIO_Init(&MOTOR_ON_PB);
    GPIO_Init(&EMERGENCY_PB);
    GPIO_Init(&MOTOR_STOP_PB);
    GPIO_Init(&MOTOR_ON);
    GPIO_Init(&GREEN_LAMP);
    GPIO_Init(&RED_LAMP);
    GPIO_Init(&ORANGE_LAMP);


    
    /*testing module*/
    // while(1){
        
    //     if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0)){
    //         GPIO_WriteToOutputPin(GPIOD,GPIO_PIN_NO_14,GPIO_PIN_SET);
    //         software_delay();
    //     }else{
    //         GPIO_WriteToOutputPin(GPIOD,GPIO_PIN_NO_14,GPIO_PIN_RESET);
    //         software_delay();
    //     }
    // }
    
}