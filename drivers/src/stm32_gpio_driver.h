#ifndef stm32f407_gpio_driver_h_
#define stm32f407_gpio_driver_h_

#include <stm32f407.h>

/*
this is the configuration structure of GPIO pin
*/
typedef struct{
    uint8_t GPIO_PinNumber;
    uint8_t GPIO_PinMode;         /*!< possible values from  @GPIO_PIN_MODES >*/
    uint8_t GPIO_PinSpeed;        /*!< possible values from  @GPIO_PIN_SPEED >*/
    uint8_t GPIO_PinPuPdControl;  /*!< possible values from  @GPIO_PIN_PUPD >*/
    uint8_t GPIO_PinOPType;       /*!< possible values from  @GPIO_PIN_OPTYPE >*/
    uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;

/*
this is the handle structure for GPIO pin
*/
typedef struct{
    GPIOx_RegDef_t*pGPIOx;
    GPIO_PinConfig_t GPIO_PinConfig; 
}GPIO_Handle_t;

/*
@GPIO_PIN_NUMBERS
GPIO pin numbers
*/
#define GPIO_PIN_NO_0    0
#define GPIO_PIN_NO_1    1
#define GPIO_PIN_NO_2    2
#define GPIO_PIN_NO_3    3
#define GPIO_PIN_NO_4    4
#define GPIO_PIN_NO_5    5
#define GPIO_PIN_NO_6    6
#define GPIO_PIN_NO_7    7
#define GPIO_PIN_NO_8    8
#define GPIO_PIN_NO_9    9
#define GPIO_PIN_NO_10   10
#define GPIO_PIN_NO_11   11
#define GPIO_PIN_NO_12   12
#define GPIO_PIN_NO_13   13
#define GPIO_PIN_NO_14   14
#define GPIO_PIN_NO_15   15

/*
@GPIO_PIN_MODES
GPIO pin possible modes
*/
#define GPIO_PIN_MODE_IN       0
#define GPIO_PIN_MODE_OUT      1
#define GPIO_PIN_MODE_ALTFN    2
#define GPIO_PIN_MODE_ANALOG   3
#define GPIO_PIN_MODE_IT_RT    4
#define GPIO_PIN_MODE_IT_FT    5
#define GPIO_PIN_MODE_IT_RFT   6

/*
@GPIO_PIN_OPTYPE
GPIO pin possible output type modes
*/
#define GPIO_PIN_OP_TYPE_PP    0
#define GPIO_PIN_OP_TYPE_OD    1

/*
@GPIO_PIN_SPEED
GPIO pin possible speed modes
*/
#define GPIO_PIN_SPEED_LOW      0
#define GPIO_PIN_SPEED_MEDIUM   1
#define GPIO_PIN_SPEED_FAST     2
#define GPIO_PIN_SPEED_HIGH     3

/*
@GPIO_PIN_PUPD
GPIO pin pull-up AND pull-down configuration macros
*/
#define GPIO_PIN_NO_PUPD    0
#define GPIO_PIN_PU         1
#define GPIO_PIN_PD         2

/* 
 * If a C++ file (.cpp) includes this header, this guard automatically 
 * wraps all prototypes below inside an hidden extern "C" block.
 * If a plain C file (.c) includes it, this line is completely ignored.
 */
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************
 *                   APIs supported by this driver
 *          For more info about APIs check Function definitions
 **********************************************************************************/

/*
peripheral clock setup
*/
void GPIO_PeriClockControl(GPIOx_RegDef_t* pGPIOx, uint8_t EnorDi);

/*
Init and De-init
*/
void GPIO_Init(GPIO_Handle_t* pGPIOHandle);
void GPIO_DeInit(GPIOx_RegDef_t* pGPIOx);

/*
Data read and write
*/
uint8_t GPIO_ReadFromInputPin(GPIOx_RegDef_t* pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIOx_RegDef_t*pGPIOx);
void GPIO_WriteToOutputPin(GPIOx_RegDef_t* pGPIOx, uint8_t PinNumber, uint8_t value);
void GPIO_WriteToOutputPort(GPIOx_RegDef_t* pGPIOx, uint16_t value);
void GPIO_ToggleOutputPin(GPIOx_RegDef_t* pGPIOx, uint8_t PinNumber);

/*
IRQ configuration and ISR handling
*/
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_ISRHandling(uint8_t PinNumber);

#ifdef __cplusplus
}
#endif

#endif