#ifndef stm32f407_h_
#define stm32f407_h_

#include<stdint.h>
//tasks and stacks
#define MAX_TASKS  (uint32_t)2

typedef struct {
uint32_t stack_gap[100];
uint32_t stack_frame[16];
}stack_t;

/****************************pheripheral register definition structures**************************************************** */

//register definition structure GPIOx (variable place holders)
typedef struct {
    volatile uint32_t GPIOx_MODER;     /*Regsiter for configuring the mode in which GPIO pin operates (input/output/AF/Analog).                                                     | Address offset: 0x00      */
    volatile uint32_t GPIOx_OTYPER;    /*Regsiter for configuring the output type of register (push-pull/open drain), applies only when pin is configured in Output Mode.           | Address offset: 0x04      */
    volatile uint32_t GPIOx_OSPEEDR;   /*Regsiter for configuring the speed with which pin operates(low/meduim/high/very high), applies only when pin is configured in Output Mode. | Address offset: 0x08      */
    volatile uint32_t GPIOx_PUPDR;     /*Register for configuring the pull-up/pull-down of a GPIO pin.                                                                              | Address offset: 0x0c      */                   
    volatile uint32_t GPIOx_IDR;       /*Input Data Register, updates register with the pin value on every AHB1 cycle.                                                              | Address offset: 0x10      */
    volatile uint32_t GPIOx_ODR;       /*Output Data Register, updates pin value on every AHB1 cycle.                                                                               | Address offset: 0x14      */
    volatile uint32_t GPIOx_BSRR;      /*TODO,                                                                                                                                                                  */
    volatile uint32_t GPIOx_LCKR;      /*TODO,                                                                                                                                                                  */
    volatile uint32_t GPIOx_AFR[2];    /*AFRL (AFR[0]) & AFRH (AFR[1]) register for configuring the Alternate Functionality mode of a GPIO pin.                                     | Address offset: 0x20-0x24 */
} GPIOx_RegDef_t;

typedef struct {
    uint32_t RCC_CR;           /*TODO,                                                     | Address offset: 0x00      */
    uint32_t RCC_PLLCFGR;      /*TODO,                                                     | Address offset: 0x04      */
    uint32_t RCC_CFGR;         /*TODO,                                                     | Address offset: 0x08      */
    uint32_t RCC_CIR;          /*TODO,                                                     | Address offset: 0x0C      */
    uint32_t RCC_AHB1RSTR;     /*TODO,                                                     | Address offset: 0x10      */
    uint32_t RCC_AHB2RSTR;     /*TODO,                                                     | Address offset: 0x14      */
    uint32_t RCC_AHB3RSTR;     /*TODO,                                                     | Address offset: 0x18      */
    uint32_t Reserved_0;       /*TODO,                                                     | Address offset: 0x1C      */
    uint32_t RCC_APB1RSTR;     /*TODO,                                                     | Address offset: 0x20      */
    uint32_t RCC_APB2RSTR;     /*TODO,                                                     | Address offset: 0x24      */
    uint32_t Reserved_1;       /*TODO,                                                     | Address offset: 0x28      */
    uint32_t Reserved_2;       /*TODO,                                                     | Address offset: 0x2C      */
    volatile uint32_t RCC_AHB1ENR;      /*TODO,                                                     | Address offset: 0x30      */
    uint32_t RCC_AHB2ENR;      /*TODO,                                                     | Address offset: 0x34      */
    uint32_t RCC_AHB3ENR;      /*TODO,                                                     | Address offset: 0x38      */
    uint32_t Reserved_3;       /*TODO,                                                     | Address offset: 0x3C      */
    uint32_t RCC_APB1ENR;      /*TODO,                                                     | Address offset: 0x40      */
    uint32_t RCC_APB2ENR;      /*TODO,                                                     | Address offset: 0x44      */
    uint32_t Reserved_4;       /*TODO,                                                     | Address offset: 0x48      */
    uint32_t Reserved_5;       /*TODO,                                                     | Address offset: 0x4C      */
    uint32_t RCC_AHB1LPENR;    /*TODO,                                                     | Address offset: 0x50      */
    uint32_t RCC_AHB2LPENR;    /*TODO,                                                     | Address offset: 0x54      */
    uint32_t RCC_AHB3LPENR;    /*TODO,                                                     | Address offset: 0x58      */
    uint32_t Reserved_6;       /*TODO,                                                     | Address offset: 0x5C      */
    uint32_t RCC_APB1LPENR;    /*TODO,                                                     | Address offset: 0x60      */
    uint32_t RCC_APB2LPENR;    /*TODO,                                                     | Address offset: 0x64      */
    uint32_t Reserved_7;       /*TODO,                                                     | Address offset: 0x68      */
    uint32_t Reserved_8;       /*TODO,                                                     | Address offset: 0x6C      */
    uint32_t RCC_BDCR;         /*TODO,                                                     | Address offset: 0x70      */
    uint32_t RCC_CSR;          /*TODO,                                                     | Address offset: 0x74      */
    uint32_t Reserved_9;       /*TODO,                                                     | Address offset: 0x78      */
    uint32_t Reserved_10;      /*TODO,                                                     | Address offset: 0x7C      */
    uint32_t RCC_SSCGR;        /*TODO,                                                     | Address offset: 0x80      */
    uint32_t RCC_PLLI2SCFGR;   /*TODO,                                                     | Address offset: 0x84      */
    uint32_t RCC_PLLSAICFGR;   /*TODO,                                                     | Address offset: 0x88      */
    uint32_t RCC_DCKCFGR;      /*TODO,                                                     | Address offset: 0x8C      */
}RCC_Regdef_t;

/***********************************Base addresses of pheripheral registers******************************************* */

//Base addresses of various memory sections of STM32f407 MCU
#define FLASH_BASEADDR 0x08000000U                   //base address of flash memory
#define SRAM1_BASEADDR 0x20000000U                   //base address of SRAM1
#define SRAM2_BASEADDR (SRAM1_BASEADDR + 112K)       //base address of SRAM2
#define SRAM_BASEADDR SRAM1_BASEADDR                 //base address of SRAM

//Base address of various BUS domains
#define APB1_BASEADDR 0x40000000U                    //base address of APB1 bus
#define APB2_BASEADDR 0x40010000U                    //base address of APB2 bus
#define AHB1_BASEADDR 0x40020000U                    //base address of AHB1 bus
#define AHB2_BASEADDR 0x50000000U                    //base address of AHB2 bus

//Base address of various GPIOx ports
#define GPIOA_BASEADDR AHB1_BASEADDR                 //base address of GPIOA_BASEADDRESS
#define GPIOB_BASEADDR (AHB1_BASEADDR + 0x0400)      //Base address of GPIOB_BASEADDRESS
#define GPIOC_BASEADDR (AHB1_BASEADDR + 0x0800)      //base address of GPIOC_BASEADDRESS
#define GPIOD_BASEADDR (AHB1_BASEADDR + 0x0C00)      //base address of GPIOD_BASEADDRESS
#define GPIOE_BASEADDR (AHB1_BASEADDR + 0x1000)      //base address of GPIOE_BASEADDRESS
#define GPIOF_BASEADDR (AHB1_BASEADDR + 0x1400)      //base address of GPIOF_BASEADDRESS
#define GPIOG_BASEADDR (AHB1_BASEADDR + 0x1800)      //base address of GPIOF_BASEADDRESS
#define GPIOH_BASEADDR (AHB1_BASEADDR + 0x1C00)      //base address of GPIOF_BASEADDRESS
#define GPIOI_BASEADDR (AHB1_BASEADDR + 0x2000)      //base address of GPIOF_BASEADDRESS
#define GPIOJ_BASEADDR (AHB1_BASEADDR + 0x2400)      //base address of GPIOF_BASEADDRESS
#define GPIOK_BASEADDR (AHB1_BASEADDR + 0x2800)      //base address of GPIOF_BASEADDRESS

#define RCC_BASEADDR   (AHB1_BASEADDR + 0x3800)      //base address of RCC_BASEADDRESS

//Addresses of various GPIOx with Register Definitions
#define  GPIOA (GPIOx_RegDef_t*)GPIOA_BASEADDR
#define  GPIOB (GPIOx_RegDef_t*)GPIOB_BASEADDR
#define  GPIOC (GPIOx_RegDef_t*)GPIOC_BASEADDR
#define  GPIOD (GPIOx_RegDef_t*)GPIOD_BASEADDR
#define  GPIOE (GPIOx_RegDef_t*)GPIOE_BASEADDR
#define  GPIOF (GPIOx_RegDef_t*)GPIOF_BASEADDR
#define  GPIOG (GPIOx_RegDef_t*)GPIOG_BASEADDR
#define  GPIOH (GPIOx_RegDef_t*)GPIOH_BASEADDR
#define  GPIOI (GPIOx_RegDef_t*)GPIOI_BASEADDR
#define  GPIOJ (GPIOx_RegDef_t*)GPIOJ_BASEADDR
#define  GPIOK (GPIOx_RegDef_t*)GPIOK_BASEADDR

//Address of RCC base register with Register definition.
#define RCC ((RCC_Regdef_t*)RCC_BASEADDR)

/*
clock enable macros for GPIOx peripherals
*/
#define GPIOA_PCLK_EN()  (RCC->RCC_AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN()  (RCC->RCC_AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN()  (RCC->RCC_AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN()  (RCC->RCC_AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN()  (RCC->RCC_AHB1ENR |= (1<<0))
#define GPIOF_PCLK_EN()  (RCC->RCC_AHB1ENR |= (1<<5))
#define GPIOG_PCLK_EN()  (RCC->RCC_AHB1ENR |= (1<<6))
#define GPIOH_PCLK_EN()  (RCC->RCC_AHB1ENR |= (1<<7))
#define GPIOI_PCLK_EN()  (RCC->RCC_AHB1ENR |= (1<<8))
#define GPIOJ_PCLK_EN()  (RCC->RCC_AHB1ENR |= (1<<9))
#define GPIOK_PCLK_EN()  (RCC->RCC_AHB1ENR |= (1<<10))

/*
clock enable peripheral for USARTx pheripherals
*/
#define USART1_PCLK_EN()  (RCC->RCC_APB2ENR |= (1<<4))
#define USART6_PCLK_EN()  (RCC->RCC_APB2ENR |= (1<<5))

/*
clock enable register for UARTx pheripherals
*/
#define UART4_PCLK_EN()  (RCC->RCC_APB1ENR |= (1<<19))
#define UART5_PCLK_EN()  (RCC->RCC_APB1ENR |= (1<<20))

/*
clock disable register for GPIOx pheripherals
*/
#define GPIOA_PCLK_DI()  (RCC->RCC_AHB1ENR &= ~(1<<0))
#define GPIOB_PCLK_DI()  (RCC->RCC_AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DI()  (RCC->RCC_AHB1ENR &= ~(1<<2))
#define GPIOD_PCLK_DI()  (RCC->RCC_AHB1ENR &= ~(1<<3))
#define GPIOE_PCLK_DI()  (RCC->RCC_AHB1ENR &= ~(1<<4))
#define GPIOF_PCLK_DI()  (RCC->RCC_AHB1ENR &= ~(1<<5))
#define GPIOG_PCLK_DI()  (RCC->RCC_AHB1ENR &= ~(1<<6))
#define GPIOH_PCLK_DI()  (RCC->RCC_AHB1ENR &= ~(1<<7))
#define GPIOI_PCLK_DI()  (RCC->RCC_AHB1ENR &= ~(1<<8))
#define GPIOJ_PCLK_DI()  (RCC->RCC_AHB1ENR &= ~(1<<9))
#define GPIOK_PCLK_DI()  (RCC->RCC_AHB1ENR &= ~(1<<10))

/*
clock disable pheripheral for USARTx pheripherals
*/
#define USART1_PCLK_DI()  (RCC->RCC_APB2ENR &= ~(1<<4))
#define USART6_PCLK_DI()  (RCC->RCC_APB2ENR &= ~(1<<5))

/*
clock disable pheripheral for UARTx pheripherals
*/
#define UART4_PCLK_DI()  (RCC->RCC_APB1ENR &= ~(1<<19))
#define UART5_PCLK_DI()  (RCC->RCC_APB1ENR &= ~(1<<20))

/*
macros to reset the GPIOx pheripherals
*/
#define GPIOA_REG_RESET()   do{(RCC->RCC_AHB1RSTR |= (1<<0));(RCC->RCC_AHB1RSTR &= ~(1<<0));}while(0)
#define GPIOB_REG_RESET()   do{(RCC->RCC_AHB1RSTR |= (1<<1));(RCC->RCC_AHB1RSTR &= ~(1<<1));}while(0)
#define GPIOC_REG_RESET()   do{(RCC->RCC_AHB1RSTR |= (1<<2));(RCC->RCC_AHB1RSTR &= ~(1<<2));}while(0)
#define GPIOD_REG_RESET()   do{(RCC->RCC_AHB1RSTR |= (1<<3));(RCC->RCC_AHB1RSTR &= ~(1<<3));}while(0)
#define GPIOE_REG_RESET()   do{(RCC->RCC_AHB1RSTR |= (1<<4));(RCC->RCC_AHB1RSTR &= ~(1<<4));}while(0)
#define GPIOF_REG_RESET()   do{(RCC->RCC_AHB1RSTR |= (1<<5));(RCC->RCC_AHB1RSTR &= ~(1<<5));}while(0)
#define GPIOG_REG_RESET()   do{(RCC->RCC_AHB1RSTR |= (1<<6));(RCC->RCC_AHB1RSTR &= ~(1<<5));}while(0)
#define GPIOH_REG_RESET()   do{(RCC->RCC_AHB1RSTR |= (1<<7));(RCC->RCC_AHB1RSTR &= ~(1<<5));}while(0)
#define GPIOI_REG_RESET()   do{(RCC->RCC_AHB1RSTR |= (1<<8));(RCC->RCC_AHB1RSTR &= ~(1<<5));}while(0)
#define GPIOJ_REG_RESET()   do{(RCC->RCC_AHB1RSTR |= (1<<9));(RCC->RCC_AHB1RSTR &= ~(1<<5));}while(0)
#define GPIOK_REG_RESET()   do{(RCC->RCC_AHB1RSTR |= (1<<10));(RCC->RCC_AHB1RSTR &= ~(1<<5));}while(0)


/*
some useful macros (can be used by all drivers,applications, etc.)
*/
 #define ENABLE           1
 #define DISABLE          0
 #define SET              ENABLE
 #define RESET            DISABLE
 #define GPIO_PIN_SET     SET
 #define GPIO_PIN_RESET   RESET

/*pheripheral header files*/
#include<stm32_gpio_driver.h>

 #endif