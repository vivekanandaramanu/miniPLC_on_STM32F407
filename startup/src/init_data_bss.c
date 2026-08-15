#include <stdint.h>
#include<stm32f407.h>

// extern data from linker (linker symbols)
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t __bss_start__, __bss_end__;
extern uint32_t _sframe, _eframe, _siframe;

void data_init(void);
void bss_init(void);
void tasks_stack_init(void);


stack_t stacks[MAX_TASKS];

//copy .data section from FLASH to RAM.
void data_init(void){
    uint32_t * src = &_sidata;  //FLASH .data section start Addr
    uint32_t * dst = &_sdata;  //RAM .data section start Addr

    while (dst < &_edata)
    {
        *dst++ = *src++;
    }
}
//initalize .bss section in RAM.
void bss_init(void){
    uint32_t * dst = &__bss_start__;
    
    while(dst < &__bss_end__){
        *dst++ = 0;
    }
}
