#include<stm32f407.h>

void PLC_GPIO_Init();
void software_delay(void);

//software delay
void software_delay(void){
    for(uint32_t i = 0;i<50000; i++);
}

void PLC_GPIO_Init(){
/*
GPIO INPUTS AND OUTPUTS
*/
//plc inputs
    GPIO_Handle_t IX_0_0;            /* CONTROL ON CLEARANCE       */
    GPIO_Handle_t IX_0_1;            /* EMERGENCY                  */
    GPIO_Handle_t IX_0_2;            /* JOG FWD SPEED 1            */
    GPIO_Handle_t IX_0_3;            /* JOG REV SPEED 1            */
    GPIO_Handle_t IX_0_4;            /* JOG FWD SPEED 2            */
    GPIO_Handle_t IX_0_5;            /* JOG REV SPEED 2            */
    GPIO_Handle_t IX_0_6;            /* CARRIAGE FWD               */
    GPIO_Handle_t IX_0_7;            /* CARRIAGE REV               */
    
    GPIO_Handle_t IX_1_0;            /* JOG MODE                   */
    GPIO_Handle_t IX_1_1;            /* MDI/AUTO                   */
    GPIO_Handle_t IX_1_2;            /* SPINDLE DRIVE READY        */
    GPIO_Handle_t IX_1_3;            /* MPCB TRIPPED               */
    GPIO_Handle_t IX_1_4;            /* DOOR OPEN LIMIT            */
    GPIO_Handle_t IX_1_5;            /* DOOR CLOSE LIMIT           */
    GPIO_Handle_t IX_1_6;            /* RESERVED FOR FUTURE INPUT  */
    GPIO_Handle_t IX_1_7;            /* RESERVED FOR FUTURE INPUT  */
   
    GPIO_Handle_t IX_2_0;            /* CARRAIGE FWD END LIMIT     */
    GPIO_Handle_t IX_2_1;            /* CARRIAGE REV END LIMIT     */
    GPIO_Handle_t IX_2_2;            /* RUN CMD FROM RPI           */
    GPIO_Handle_t IX_2_3;            /* DIRECTION CMD FROM RPI     */
    GPIO_Handle_t IX_2_4;            /* RESERVED FOR FUTURE INPUT  */
    GPIO_Handle_t IX_2_5;            /* RESERVED FOR FUTURE INPUT  */
    GPIO_Handle_t IX_2_6;            /* RESERVED FOR FUTURE INPUT  */
    GPIO_Handle_t IX_2_7;            /* RESERVED FOR FUTURE INPUT  */

//plc outputs
    GPIO_Handle_t QX_0_0;            /* CONTROL ON                 */
    GPIO_Handle_t QX_0_1;            /* SPINDLE BLOWER MOTOR       */
    GPIO_Handle_t QX_0_2;            /* JSPINDLE BRAKE RELEA       */
    GPIO_Handle_t QX_0_3;            /* CARRIAGE FWD OUTPUT        */
    GPIO_Handle_t QX_0_4;            /* CARRAIGE REV OUTPUT        */
    GPIO_Handle_t QX_0_5;            /* DRIVE ENABLE - 38          */
    GPIO_Handle_t QX_0_6;            /* DRIVE RUN COMMAND - 37     */
    GPIO_Handle_t QX_0_7;            /* DRIVE COMMAND-36           */
    
    GPIO_Handle_t QX_1_0;            /* JOG SPEED 2 - 39           */
    GPIO_Handle_t QX_1_1;            /* AUTO/MDI TO RPI            */
    GPIO_Handle_t QX_1_2;            /* RESERVED FOR FUTURE OUTPUT */
    GPIO_Handle_t QX_1_3;            /* RESERVED FOR FUTURE OUTPUT */
    GPIO_Handle_t QX_1_4;            /* RESERVED FOR FUTURE OUTPUT */   
    GPIO_Handle_t QX_1_5;            /* RED                        */
    GPIO_Handle_t QX_1_6;            /* ORANGE                     */
    GPIO_Handle_t QX_1_7;            /* GREEN                      */
    
/*
GPIO PORT AND PIN CONFIGURATIONS
*/
    //port and pin configurations for inputs
    IX_0_0 = (GPIO_Handle_t) {GPIOA, GPIO_PIN_NO_0,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_0_1 = (GPIO_Handle_t) {GPIOA, GPIO_PIN_NO_1,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_0_2 = (GPIO_Handle_t) {GPIOA, GPIO_PIN_NO_2,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_0_3 = (GPIO_Handle_t) {GPIOA, GPIO_PIN_NO_3,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_0_4 = (GPIO_Handle_t) {GPIOA, GPIO_PIN_NO_4,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_0_5 = (GPIO_Handle_t) {GPIOA, GPIO_PIN_NO_5,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_0_6 = (GPIO_Handle_t) {GPIOA, GPIO_PIN_NO_6,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_0_0 = (GPIO_Handle_t) {GPIOA, GPIO_PIN_NO_7,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    
    IX_1_0 = (GPIO_Handle_t) {GPIOC, GPIO_PIN_NO_0,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_1_1 = (GPIO_Handle_t) {GPIOC, GPIO_PIN_NO_1,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_1_2 = (GPIO_Handle_t) {GPIOC, GPIO_PIN_NO_2,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_1_3 = (GPIO_Handle_t) {GPIOC, GPIO_PIN_NO_3,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_1_4 = (GPIO_Handle_t) {GPIOC, GPIO_PIN_NO_4,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_1_5 = (GPIO_Handle_t) {GPIOC, GPIO_PIN_NO_5,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_1_6 = (GPIO_Handle_t) {GPIOB, GPIO_PIN_NO_0,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_1_7 = (GPIO_Handle_t) {GPIOB, GPIO_PIN_NO_1,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};

    IX_2_0 = (GPIO_Handle_t) {GPIOB, GPIO_PIN_NO_2,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_2_1 = (GPIO_Handle_t) {GPIOE, GPIO_PIN_NO_7,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_2_2 = (GPIO_Handle_t) {GPIOE, GPIO_PIN_NO_8,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_2_3 = (GPIO_Handle_t) {GPIOE, GPIO_PIN_NO_9,  GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_2_4 = (GPIO_Handle_t) {GPIOE, GPIO_PIN_NO_10, GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_2_5 = (GPIO_Handle_t) {GPIOE, GPIO_PIN_NO_11, GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_2_6 = (GPIO_Handle_t) {GPIOE, GPIO_PIN_NO_12, GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};
    IX_2_7 = (GPIO_Handle_t) {GPIOE, GPIO_PIN_NO_13, GPIO_PIN_MODE_IN, 0, GPIO_PIN_PD, 0, 0};

    //port and pin configurations for outputs
    QX_0_0 = (GPIO_Handle_t) {GPIOD, GPIO_PIN_NO_15, GPIO_PIN_MODE_OUT, GPIO_PIN_SPEED_FAST, 
        GPIO_PIN_NO_PUPD, GPIO_PIN_OP_TYPE_PP, 0};
    QX_0_1 = (GPIO_Handle_t) {GPIOD, GPIO_PIN_NO_11, GPIO_PIN_MODE_OUT, GPIO_PIN_SPEED_FAST, 
        GPIO_PIN_NO_PUPD, GPIO_PIN_OP_TYPE_PP, 0};
    QX_0_2 = (GPIO_Handle_t) {GPIOD, GPIO_PIN_NO_10, GPIO_PIN_MODE_OUT, GPIO_PIN_SPEED_FAST, 
        GPIO_PIN_NO_PUPD, GPIO_PIN_OP_TYPE_PP, 0};
    QX_0_3 = (GPIO_Handle_t) {GPIOD, GPIO_PIN_NO_9,  GPIO_PIN_MODE_OUT, GPIO_PIN_SPEED_FAST, 
        GPIO_PIN_NO_PUPD, GPIO_PIN_OP_TYPE_PP, 0};
    QX_0_4 = (GPIO_Handle_t) {GPIOD, GPIO_PIN_NO_8,  GPIO_PIN_MODE_OUT, GPIO_PIN_SPEED_FAST, 
        GPIO_PIN_NO_PUPD, GPIO_PIN_OP_TYPE_PP, 0};
    QX_0_5 = (GPIO_Handle_t) {GPIOB, GPIO_PIN_NO_15, GPIO_PIN_MODE_OUT, GPIO_PIN_SPEED_FAST, 
        GPIO_PIN_NO_PUPD, GPIO_PIN_OP_TYPE_PP, 0};
    QX_0_6 = (GPIO_Handle_t) {GPIOB, GPIO_PIN_NO_14, GPIO_PIN_MODE_OUT, GPIO_PIN_SPEED_FAST, 
        GPIO_PIN_NO_PUPD, GPIO_PIN_OP_TYPE_PP, 0};
    QX_0_7 = (GPIO_Handle_t) {GPIOB, GPIO_PIN_NO_13, GPIO_PIN_MODE_OUT, GPIO_PIN_SPEED_FAST, 
        GPIO_PIN_NO_PUPD, GPIO_PIN_OP_TYPE_PP, 0};

    QX_1_0 = (GPIO_Handle_t) {GPIOB, GPIO_PIN_NO_12, GPIO_PIN_MODE_OUT, GPIO_PIN_SPEED_FAST, 
        GPIO_PIN_NO_PUPD, GPIO_PIN_OP_TYPE_PP, 0};
    QX_1_1 = (GPIO_Handle_t) {GPIOB, GPIO_PIN_NO_11, GPIO_PIN_MODE_OUT, GPIO_PIN_SPEED_FAST, 
        GPIO_PIN_NO_PUPD, GPIO_PIN_OP_TYPE_PP, 0};
    QX_1_2 = (GPIO_Handle_t) {GPIOB, GPIO_PIN_NO_10, GPIO_PIN_MODE_OUT, GPIO_PIN_SPEED_FAST, 
        GPIO_PIN_NO_PUPD, GPIO_PIN_OP_TYPE_PP, 0};
    QX_1_3 = (GPIO_Handle_t) {GPIOE, GPIO_PIN_NO_15, GPIO_PIN_MODE_OUT, GPIO_PIN_SPEED_FAST, 
        GPIO_PIN_NO_PUPD, GPIO_PIN_OP_TYPE_PP, 0};
    QX_1_4 = (GPIO_Handle_t) {GPIOE, GPIO_PIN_NO_14, GPIO_PIN_MODE_OUT, GPIO_PIN_SPEED_FAST, 
        GPIO_PIN_NO_PUPD, GPIO_PIN_OP_TYPE_PP, 0};
    QX_1_5 = (GPIO_Handle_t) {GPIOD, GPIO_PIN_NO_14, GPIO_PIN_MODE_OUT, GPIO_PIN_SPEED_FAST, 
        GPIO_PIN_NO_PUPD, GPIO_PIN_OP_TYPE_PP, 0};
    QX_1_6 = (GPIO_Handle_t) {GPIOD, GPIO_PIN_NO_13, GPIO_PIN_MODE_OUT, GPIO_PIN_SPEED_FAST, 
        GPIO_PIN_NO_PUPD, GPIO_PIN_OP_TYPE_PP, 0};
    QX_1_7 = (GPIO_Handle_t) {GPIOD, GPIO_PIN_NO_12, GPIO_PIN_MODE_OUT, GPIO_PIN_SPEED_FAST, 
        GPIO_PIN_NO_PUPD, GPIO_PIN_OP_TYPE_PP, 0};

/*
PLC GPIO CLOCK ENABLE & INITILALIZATION FUNCTIONS
*/
    
    //GPIO pheripheral clock enable 
    GPIO_PeriClockControl(GPIOA,ENABLE);  // INPUTS : PA0-PA7      | OUTPUTS : (NIL)
    GPIO_PeriClockControl(GPIOC,ENABLE);  // INPUTS : PC0-PC5      | OUTPUTS : (NIL)
    GPIO_PeriClockControl(GPIOB,ENABLE);  // INPUTS : PB0,PB1,PB2  | OUTPUTS : PB10-PB15
    GPIO_PeriClockControl(GPIOE,ENABLE);  // INPUTS : PE7-PE13     | OUTPUTS : PE14,PE15
    GPIO_PeriClockControl(GPIOD,ENABLE);  // INPUTS : (NIL)        | OUTPUTS : PD8-PD15

    volatile uint32_t delay1 = 0;
    delay1++;
    delay1++;

    //GPIO pin initialization of inputs
    GPIO_Init(&IX_0_0);
    GPIO_Init(&IX_0_1);
    GPIO_Init(&IX_0_2);
    GPIO_Init(&IX_0_3);
    GPIO_Init(&IX_0_4);
    GPIO_Init(&IX_0_5);
    GPIO_Init(&IX_0_6);
    GPIO_Init(&IX_0_7);

    GPIO_Init(&IX_1_0);
    GPIO_Init(&IX_1_1);
    GPIO_Init(&IX_1_2);
    GPIO_Init(&IX_1_3);
    GPIO_Init(&IX_1_4);
    GPIO_Init(&IX_1_5);
    GPIO_Init(&IX_1_6);
    GPIO_Init(&IX_1_7);

    GPIO_Init(&IX_2_0);
    GPIO_Init(&IX_2_1);
    GPIO_Init(&IX_2_2);
    GPIO_Init(&IX_2_3);
    GPIO_Init(&IX_2_4);
    GPIO_Init(&IX_2_5);
    GPIO_Init(&IX_2_6);
    GPIO_Init(&IX_2_7);

    //GPIO pin initialization of inputs
    GPIO_Init(&QX_0_0);
    GPIO_Init(&QX_0_1);
    GPIO_Init(&QX_0_2);
    GPIO_Init(&QX_0_3);
    GPIO_Init(&QX_0_4);
    GPIO_Init(&QX_0_5);
    GPIO_Init(&QX_0_6);
    GPIO_Init(&QX_0_7);
    
    GPIO_Init(&QX_1_0);
    GPIO_Init(&QX_1_1);
    GPIO_Init(&QX_1_2);
    GPIO_Init(&QX_1_3);
    GPIO_Init(&QX_1_4);
    GPIO_Init(&QX_1_5);
    GPIO_Init(&QX_1_6);
    GPIO_Init(&QX_1_7);

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