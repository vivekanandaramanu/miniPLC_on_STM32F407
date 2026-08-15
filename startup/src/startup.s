.section .vectors, "a", %progbits
.p2align 2
.global vector_table
.thumb

vector_table:
    /* =====================================================================
     * ARM CORTEX-M4 SYSTEM CORE VECTOR TABLE (FIRST 16 VECTORS)
     * =====================================================================
     * Vector #  | Address Offset | Exception / Handler Description
     * =====================================================================
     */
    .word _estack               /*  0 | 0x0000 | Initial Main Stack Pointer (MSP) */
    .word Reset_Handler         /*  1 | 0x0004 | Reset Handler (Boot Entry Point) */
    .word NMI_Handler           /*  2 | 0x0008 | Non-Maskable Interrupt Handler   */
    .word HardFault_Handler     /*  3 | 0x000C | All Classes of Fault Handler     */
    .word MemManage_Handler     /*  4 | 0x0010 | Memory Management Fault Handler  */
    .word BusFault_Handler      /*  5 | 0x0014 | Pre-Fetch & Memory Bus Fault     */
    .word UsageFault_Handler    /*  6 | 0x0018 | Undefined Instr / Illegal State  */
    
    /* Vector Positions 7 to 10 are Reserved by ARM Hardware Specs */
    .word 0                     /*  7 | 0x001C | Reserved                         */
    .word 0                     /*  8 | 0x0020 | Reserved                         */
    .word 0                     /*  9 | 0x0024 | Reserved                         */
    .word 0                     /* 10 | 0x0028 | Reserved                         */
    
    .word SVC_Handler           /* 11 | 0x002C | System Service Call (via SVC instr)*/
    .word DebugMon_Handler      /* 12 | 0x0030 | Debug Monitor Handler            */
    
    /* Vector Position 13 is Reserved by ARM Hardware Specs */
    .word 0                     /* 13 | 0x0034 | Reserved                         */
    
    .word PendSV_Handler        /* 14 | 0x0038 | Pendable Request for System Service*/
    .word SysTick_Handler       /* 15 | 0x003C | System Tick Timer Handler (PLC base)*/

    /* 
     * ===============================================================================
     * STM32F407 PERIPHERAL INTERRUPT PADDING [WILL IMPLEMENT LATE AS PER REQUIRMENTS]
     * ================================================================================
     * Your original code included a '.zero 400' padding block.
     * This allocates 400 bytes of empty space right here to reserve 
     * room for the 80+ STM32 physical hardware interrupts (Timers, UARTs, DMA) 
     * that live at Address Offset 0x0040 and onward.
     */
    .zero 400
//vector table ends here.
 
/* 
 * ===============================================================================
 *             HANDLER FUNCTIONS (STRONG,WEAK AND DEFAULT)
 * ===============================================================================
 */
    .section .text
    .p2align 1

    .extern data_init
    .extern bss_init
    .extern main

    .thumb_func
    .global Reset_Handler
   .type Reset_Handler, %function
Reset_Handler:
// .data section copy from FLASH (MEM) into RAM
    bl data_init

// .bss initailize it to 0
    bl bss_init

 // system_init (Hardware Initialization) can be implemented (if required)

/*
* INITIALIZE THE C++ STANDARD LIBRARY RUNTIME (CRITICAL!)
* This calls the hidden compiler constructor tables. It will run the
* constructors for OpenPLC's 'config', 'INSTANCE0', and all related 
* function blocks before main() executes.
*/
    bl __libc_init_array     

/* 
 MAIN PLC EXECUTION CORE
 */
    
    bl main              //; Jump to main(). 

    b .

/*
* EMERGENCY ESCAPE SAFETY NET
* If the cyclic loop inside main escapes, redirect safely to your C++ stub.
*/
    MOV R0, #0           // ; Pass '0' as the status parameter into Register R0
    bl _exit             // ; Execute a permanent jump to your custom _exit in syscalls.cpp

Assembly_Halt:
    b Assembly_Halt      // ; Absolute baseline fallback trap

   
/* 
 * ===========================================================================
 * WEAK INTERRUPT HANDLER ALIASES
 * ===========================================================================
 * The .weak directive tells the linker that these handlers can be overridden 
 * by a strong definition in C/C++ files (e.g., inside main.cpp).
 * 
 * The .thumb_set directive binds them to Default_Handler as a fallback 
 * if no strong definition is provided by the application.
 */
 
    .weak   NMI_Handler
    .thumb_set NMI_Handler, Default_Handler

    .weak   HardFault_Handler
    .thumb_set HardFault_Handler, Default_Handler

    .weak   MemManage_Handler
    .thumb_set MemManage_Handler, Default_Handler

    .weak   BusFault_Handler
    .thumb_set BusFault_Handler, Default_Handler

    .weak   UsageFault_Handler
    .thumb_set UsageFault_Handler, Default_Handler

    .weak   SVC_Handler
    .thumb_set SVC_Handler, Default_Handler

    .weak   PendSV_Handler
    .thumb_set PendSV_Handler, Default_Handler

    .weak   SysTick_Handler
    .thumb_set SysTick_Handler, Default_Handler

    .weak   DebugMon_Handler_Handler
    .thumb_set DebugMon_Handler, Default_Handler

/* ===========================================================================
 * DEFAULT HANDLER FALLBACK TRAP
 * =========================================================================== */
    /* 1. Open the executable text block section in Flash memory */
    .section .text.Default_Handler, "ax", %progbits
    
    /* 2. Mark this specific destination label as a Thumb instruction set function */
    .thumb_func
    .global Default_Handler
    .type Default_Handler, %function

Default_Handler:
    Infinite_Loop:
    b .
    bl _exit /* Real hardware instructions live here */

    .size Default_Handler, .-Default_Handler
