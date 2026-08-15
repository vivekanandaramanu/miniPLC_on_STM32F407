#include "stm32_gpio_driver.h"

/*
peripheral clock setup
*/
/*****************************************************************
 * @fn             - GPIO_PeriClockControl
 * 
 * @brief          - This function enables or disbales pheripheral clock for the given GPIO port
 * 
 * @param[in]      - base address of the GPIO pheriperal
 * @param[in]      - ENABLE or DISABLE macros
 * @param[in]      -
 * 
 * @return         - none
 * 
 * @note           - none
 */
void GPIO_PeriClockControl(GPIOx_RegDef_t* pGPIOx, uint8_t EnorDi){
    if (EnorDi == ENABLE){
        if (pGPIOx == GPIOA){
            GPIOA_PCLK_EN();
        }else if (pGPIOx == GPIOB){
            GPIOB_PCLK_EN();
        }else if (pGPIOx == GPIOC){
            GPIOC_PCLK_EN();
        }else if (pGPIOx == GPIOD){
            GPIOD_PCLK_EN();
        }else if (pGPIOx == GPIOE){
            GPIOE_PCLK_EN();
        }else if (pGPIOx == GPIOF){
            GPIOF_PCLK_EN();
        }else if (pGPIOx == GPIOG){
            GPIOG_PCLK_EN();
        }else if (pGPIOx == GPIOH){
            GPIOH_PCLK_EN();
        }else if (pGPIOx == GPIOI){
            GPIOI_PCLK_EN();
        }else if (pGPIOx == GPIOJ){
            GPIOJ_PCLK_EN();
        }else if (pGPIOx == GPIOK){
            GPIOK_PCLK_EN();
        }
    }else{
        if (pGPIOx == GPIOA){
            GPIOA_PCLK_DI();
        }else if (pGPIOx == GPIOB){
            GPIOB_PCLK_DI();
        }else if (pGPIOx == GPIOC){
            GPIOC_PCLK_DI();
        }else if (pGPIOx == GPIOD){
            GPIOD_PCLK_DI();
        }else if (pGPIOx == GPIOE){
            GPIOE_PCLK_DI();
        }else if (pGPIOx == GPIOF){
            GPIOF_PCLK_DI();
        }else if (pGPIOx == GPIOG){
            GPIOG_PCLK_DI();
        }else if (pGPIOx == GPIOH){
            GPIOH_PCLK_DI();
        }else if (pGPIOx == GPIOI){
            GPIOI_PCLK_DI();
        }else if (pGPIOx == GPIOJ){
            GPIOJ_PCLK_DI();
        }else if (pGPIOx == GPIOK){
            GPIOK_PCLK_DI();
        }
    }
}

/*
Init and De-init
*/
/*****************************************************************
 * @fn             - GPIO_Init
 * 
 * @brief          - This function initializes the given GPIO pin/port
 * 
 * @param[in]      - address of the struct GPIO Handle variable 
 * @param[in]      - 
 * @param[in]      -
 * 
 * @return         - none
 * 
 * @note           - none
 */
void GPIO_Init(GPIO_Handle_t* pGPIOHandle){
    
    //1. configure the mode of the gpio pin
    uint32_t temp = 0;  //temp register
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_PIN_MODE_ANALOG){
        temp =(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIOHandle->pGPIOx->GPIOx_MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing the required bits
        pGPIOHandle->pGPIOx->GPIOx_MODER |= temp;
    }else{
        //this we will code later (for interrupt modes)
    }
    temp = 0;

    //2. configure the speed
    temp =(pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed <<(2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->GPIOx_OSPEEDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing the required bits
    pGPIOHandle->pGPIOx->GPIOx_OSPEEDR |= temp;
    temp = 0;

    //3. configure the pupd settings
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->GPIOx_PUPDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing the required bits
    pGPIOHandle->pGPIOx->GPIOx_PUPDR |= temp;
    temp = 0;
    //4 .configure the optype
    temp =(pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->GPIOx_OTYPER &= ~(0x1 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing the required bits
    pGPIOHandle->pGPIOx->GPIOx_OTYPER |= temp;

    //5. configure the alternate functionality
    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_PIN_MODE_ALTFN){
        uint8_t temp1 = 0, temp2 =0;
        temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
        temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8; 
        pGPIOHandle->pGPIOx->GPIOx_AFR[temp1] &= ~(0xf <<(4* temp2));  //clearing the required bits
        pGPIOHandle->pGPIOx->GPIOx_AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode <<(4 * temp2));
    }
}

/*****************************************************************
 * @fn             - GPIO_DeInit
 * 
 * @brief          - This function resets the given GPIO port 
 * 
 * @param[in]      - base address of the GPIO pheriperal
 * @param[in]      - 
 * @param[in]      -
 * 
 * @return         - none
 * 
 * @note           - none
 */
void GPIO_DeInit(GPIOx_RegDef_t* pGPIOx){
     if (pGPIOx == GPIOA){
            GPIOA_REG_RESET();
        }else if (pGPIOx == GPIOB){
            GPIOB_REG_RESET();
        }else if (pGPIOx == GPIOC){
            GPIOC_REG_RESET();
        }else if (pGPIOx == GPIOD){
            GPIOD_REG_RESET();
        }else if (pGPIOx == GPIOE){
            GPIOE_REG_RESET();
        }else if (pGPIOx == GPIOF){
            GPIOF_REG_RESET();
        }else if (pGPIOx == GPIOG){
            GPIOG_REG_RESET();
        }else if (pGPIOx == GPIOH){
            GPIOH_REG_RESET();
        }else if (pGPIOx == GPIOI){
            GPIOI_REG_RESET();
        }else if (pGPIOx == GPIOJ){
            GPIOJ_REG_RESET();
        }else if (pGPIOx == GPIOK){
            GPIOK_REG_RESET();
    }
}

/*
Data read and write
*/
/*****************************************************************
 * @fn             - GPIO_ReadFromInputPin
 * 
 * @brief          - This function gives the value from the given GPIO pin
 * 
 * @param[in]      - base address of the GPIO pheriperal
 * @param[in]      - the pin number of the GPIO port (0-15)
 * @param[in]      -
 * 
 * @return         - the 8-bit read value from the given GPIO pin Input data register (either 0/1)
 * 
 * @note           - none
 */
uint8_t GPIO_ReadFromInputPin(GPIOx_RegDef_t* pGPIOx, uint8_t PinNumber){
    uint8_t value;
    value = (uint8_t)((pGPIOx->GPIOx_IDR >> PinNumber) & 0x00000001);
    return value;
}

/*****************************************************************
 * @fn             - GPIO_ReadFromInputPort
 * 
 * @brief          - This function reads data from the given GPIO port
 * 
 * @param[in]      - base address of the GPIO pheriperal
 * @param[in]      - 
 * @param[in]      -
 * 
 * @return         - the 16-bit read value from given GPIO port
 * 
 * @note           - none
 */
uint16_t GPIO_ReadFromInputPort(GPIOx_RegDef_t*pGPIOx){
    uint16_t value;
    value = (uint16_t)pGPIOx->GPIOx_IDR;
    return value;
}

/*****************************************************************
 * @fn             - GPIO_WriteToOutputPin
 * 
 * @brief          - This function writes output value to the given GPIO pin.
 * 
 * @param[in]      - base address of the GPIO pheriperal
 * @param[in]      - the pin number of the GPIO port (0-15)
 * @param[in]      - the 8-bit value 
 * 
 * @return         - none
 * 
 * @note           - none
 */
void GPIO_WriteToOutputPin(GPIOx_RegDef_t* pGPIOx, uint8_t PinNumber, uint8_t value){
    if(value == GPIO_PIN_SET){
        //write 1 to the output data register at the bit feild corresponding to pin number.
        pGPIOx->GPIOx_ODR |=  (1 << PinNumber);
    }else{
        //write 0 to the output data register at the bit feild corresponding to pin number.
        pGPIOx->GPIOx_ODR &= ~(1 << PinNumber);
    }
}

/*****************************************************************
 * @fn             - GPIO_WriteToOutputPort
 * 
 * @brief          - This function writes output to the given GPIO port
 * 
 * @param[in]      - base address of the GPIO pheriperal
 * @param[in]      - the 16-bit value
 * @param[in]      -
 * 
 * @return         - none
 * 
 * @note           - none
 */
void GPIO_WriteToOutputPort(GPIOx_RegDef_t* pGPIOx, uint16_t value){
    pGPIOx->GPIOx_ODR = value;
}

/*****************************************************************
 * @fn             - GPIO_ToggleOutputPin
 * 
 * @brief          - This function toggles the GPIO output pin
 *
 * @param[in]      - base address of the GPIO pheriperal
 * @param[in]      - the pin number of the GPIO port (0-15)
 * @param[in]      -
 * 
 * @return         - none
 * 
 * @note           - none
 */
void GPIO_ToggleOutputPin(GPIOx_RegDef_t* pGPIOx, uint8_t PinNumber){
    pGPIOx->GPIOx_ODR = pGPIOx->GPIOx_ODR ^ (1 << PinNumber);
}

/*
IRQ configuration and ISR handling
*/

/*****************************************************************
 * @fn             - GPIO_PeriClockControl
 * 
 * @brief          - This function enables or disbales pheripheral clock for the given GPIO port
 * 
 * @param[in]      - base address of the GPIO pheriperal
 * @param[in]      - ENABLE or DISABLE macros
 * @param[in]      -
 * 
 * @return         - none
 * 
 * @note           - none
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi){

}

/*****************************************************************
 * @fn             - GPIO_PeriClockControl
 * 
 * @brief          - This function enables or disbales pheripheral clock for the given GPIO port
 * 
 * @param[in]      - base address of the GPIO pheriperal
 * @param[in]      - ENABLE or DISABLE macros
 * @param[in]      -
 * 
 * @return         - none
 * 
 * @note           - none
 */
void GPIO_ISRHandling(uint8_t PinNumber){

}
