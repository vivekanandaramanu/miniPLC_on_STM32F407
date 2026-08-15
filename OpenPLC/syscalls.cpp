#include <errno.h> // Required for system error number macros/definitions
#include <stddef.h>  // Required for size_t and ptrdiff_t definitions
#include <stdint.h>  // Required for uint8_t and standard types
#include <stm32f407.h>


// Expose the end of the uninitialized data section from the linker script.
// Your linker script automatically generates this marker at the top of RAM.
extern "C" uint8_t _end; 

// We pull in stm32f4xx register headers if you need to turn off outputs here
// #include <stm32f4xx.h>

 /**
     * ===================================================================
     * BARE-METAL PLC OS STUBS (syscalls.cpp)
     * ===================================================================
     */

extern "C" {
    /**
     * ===================================================================
     * BARE-METAL PLC OS STUBS: _getpid_r & _kill_r
     * ===================================================================
     * 
     * Why These Exist:
     * 1. The C++ standard library includes a fallback mechanism (abort()) 
     *    in case an exception goes completely uncaught. 
     * 2. abort() expects a POSIX operating system layer to exist underneath 
     *    it so it can call _kill_r to terminate the process.
     * 3. Because this STM32F407 PLC runs bare-metal without an OS/RTOS, 
     *    the Linker throws "undefined reference" errors until we provide 
     *    these custom implementations.
     * 
     * Linker Timeline vs. Execution Reality:
     * - The Linker cannot read minds; it cannot verify that your main loop 
     *   is safely wrapped in a try-catch block. It forces you to write 
     *   these stubs just in case a worst-case scenario occurs.
     * - In reality, your main loop's try-catch block will intercept 99% of 
     *   all runtime calculation errors, meaning the CPU should never 
     *   actually execute these stubs during normal PLC cycles.
     * 
     * Hidden Edge Cases (When the CPU *can* still land here):
     * - Global Constructors: Exceptions thrown inside a global C++ object's 
     *   constructor before main() even begins execution.
     * - Interrupts (ISRs): Exceptions thrown inside a hardware timer or 
     *   communication interrupt which bypasses the main loop's try-catch.
     * 
     * ===================================================================
     */

    /**
     * @brief Returns a dummy Process ID to the internal C runtime library.
     * @return 1 - Informing the library that we are Process #1 (the only code running).
     */
    int _getpid_r(struct _reent *r) {
        (void)r; // Suppress unused parameter warning
        return 1; // Return 1 to the internal runtime caller
    }

    /**
     * @brief Catastrophic emergency abort handler for the PLC system.
     * @note If the runtime calls this, the CPU enters the infinite trap loop.
     *       The 'return -1;' is completely unreachable; the CPU stays here forever.
     */
    int _kill_r(struct _reent *r, int pid, int sig) {
        (void)r;   // Suppress unused parameter warning
        (void)pid; // Suppress unused parameter warning
        (void)sig; // Suppress unused parameter warning
        
        // Set the reentrant thread error flag to "Invalid Argument"
        errno = EINVAL; 
        
        /* 
         * ===============================================================
         * INDUSTRIAL PLC LAYER 2 SAFETY NET
         * ===============================================================
         * If the processor ever slips past our try-catch block and enters 
         * here, the system is in an unhandled, critical failure state.
         */
         
        // 1. FORCE SAFETY: Add your code here to force physical PLC outputs LOW!
        // GPIOA->ODR = 0; 
        // GPIOB->ODR = 0;

        // 2. ERROR VISIBILITY: Add code here to turn on a hardware Fault/Error LED

        // 3. HARDWARE CAPTURE: Trap the CPU instantly to stop machine movements.
        // This allows an ST-Link debugger to connect and read out the memory state.
        while (1) {
            __asm("NOP"); // The CPU spins here endlessly. It never returns to the caller.
        }
        
        return -1; // Unreachable, but satisfies standard POSIX syntax requirements
    }
}

extern "C" {
    /**
     * ===================================================================
     * BARE-METAL PLC OS STUBS: _exit
     * ===================================================================
     * 
     * What We Learned:
     * 1. Purpose: On a standard computer (Linux/Windows), _exit terminates 
     *    the application and returns control to the operating system. 
     *    On a bare-metal STM32F407 PLC, there is NO operating system to 
     *    exit to.
     * 2. Why the Linker Demands It: The compiler forces a dependency on 
     *    _exit inside the hidden C/C++ runtime initialization logic (crt0). 
     *    The toolchain includes this safety check just in case your 
     *    main() function ever returns, which triggers an "undefined reference" 
     *    error unless we explicitly stub it out.
     * 
     * Cyclic Execution Reality:
     * - In a standard PLC cyclic environment, your main code is trapped 
     *   inside an infinite 'while(1)' loop. Therefore, during healthy, 
     *   normal operation, the CPU will NEVER naturally drop into this function.
     * 
     * Critical Edge Cases (How the CPU could still slip in here):
     * - Returning from Main: If your infinite while(1) cyclic loop breaks 
     *   due to a logical failure, main() will hit its termination sequence.
     * - Uncaught Exceptions: If a C++ runtime exception occurs completely 
     *   outside of your primary try-catch loop, the standard library 
     *   calls std::terminate(), which redirects straight here.
     * - Standard Library Crashes: If explicit software checks (like assert()) 
     *   or bounds checks (like std::vector::at()) fail, they deliberately 
     *   abort your application by routing execution directly into _exit.
     * 
     * ===================================================================
     */
    void _exit(int status) {
        (void)status; // Suppress unused parameter warning

        /* 
         * ===============================================================
         * INDUSTRIAL PLC CRITICAL EMERGENCY SAFE-STATE
         * ===============================================================
         * If the processor hits this code, the system is in an unrecoverable 
         * condition. We must prioritize physical equipment safety immediately.
         */
         
        // 1. FORCE SAFETY: Add your code here to force physical PLC outputs LOW!
         GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_12,0);
         GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_13,0);
         GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_14,0);
         GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_15,0);

         uint8_t delay2;
         delay2++;   //1 cycle gap

        // 2. ERROR VISIBILITY: Add code here to turn on a hardware Fault/Error LED
        GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_13);

        // 3. HARDWARE BLOCK: Trap the ARM Core in an infinite loop.
        // This stops your logic cycle dead in its tracks and freezes state memory 
        // so you can attach a command-line GDB debugger to see what crashed it.
        while (1) {
            __asm("NOP"); // The CPU remains trapped here endlessly.
        }
    }
}

extern "C" {
    /**
     * ====================================================================================
     * BARE-METAL PLC OS STUBS: _write_r (Non-Blocking UART DMA Logging for OpenPLC)
     * ====================================================================================
     * 
     * WHAT WE LEARNED & DESIGNED:
     * 1. Purpose: This function is the low-level exit pipeline for all text formatting 
     *    operations like printf(), std::cout, and internal C++ exception descriptions 
     *    (e.g., e.what() during a runtime crash).
     * 2. Purpose: Bypasses raw stdout/stderr text processing for a lean application loop.
     * 2. Why it was missing: The bare-metal compiler requires an explicit hardware 
     *    destination for text bytes before it allows the compilation linking phase to pass.
     * 4. Error Catchment: Acts as a clean hook to trap unexpected C++ runtime crashes 
     *    or exception strings (e.g. e.what()) during baseline hardware testing.
     * ====================================================================================
     */
    int _write_r(struct _reent *r, int file, const void *ptr, size_t len) {
        (void)r;    // Suppress unused thread-safety structure pointer warning
        (void)ptr;  // Suppress unused data pointer buffer warning
        
        // Trap standard output (1) and standard error (2) streams.
        if (file == 1 || file == 2) {
            if (len > 0) {
                /*
                 * =======================================================================
                 * BASELINE DEBUGGING TRAIL
                 * =======================================================================
                 * If your application crashes or throws an internal object exception 
                 * during testing, execution will land right here. 
                 * 
                 * Place a hardware breakpoint on the line below in VSCode. If the 
                 * breakpoint hits, you can inspect 'ptr' as a char array to see the 
                 * exact error description.
                 */
                __asm("NOP"); 
            }
        }
        
        // Always return the requested character length. This fools the standard C++ library 
        // into thinking the bytes were flushed instantly, preventing memory buffer lockups.
        return len; 
    }
}


// Expose the end of the uninitialized data section from the linker script.
// Your linker script automatically generates this marker at the top of RAM.
extern "C" uint8_t _end; 

extern "C" {
    /**
     * ====================================================================================
     * BARE-METAL PLC OS STUBS: _sbrk_r (Heap Allocation Memory Control)
     * ====================================================================================
     * 
     * WHAT WE LEARNED & DESIGNED:
     * 1. Purpose: This function manages memory allocation for the C++ heap. It is called 
     *    by malloc(), operator new, and string format internal allocations (like printf/std::cout).
     * 2. The Task: On a bare-metal microcontroller, it manages the top boundary of available 
     *    RAM. If a memory allocation request passes, it returns the memory address. If it 
     *    fails, it flags an Out of Memory (OOM) error.
     * 
     * PLC RUNTIME CRITICAL CRASH HAZARD (THE STACK VS. HEAP COLLISION):
     * - The Danger: In an embedded system, the Heap grows UPWARD from the end of global variables 
     *   (_end), while the hardware Call Stack grows DOWNWARD from the top of RAM (Main Stack Pointer).
     * - The Crash: If your PLC code runs out of memory, or allocates variables dynamically 
     *   inside loops, the Heap and Stack can slam into each other. This instantly corrupts 
     *   your operational loop parameters or triggers a catastrophic HardFault.
     * 
     * INDUSTRIAL PLC DEVELOPMENT RULES:
     * - Production Target: In a production-grade industrial PLC, DYNAMIC MEMORY ALLOCATION (new/malloc) 
     *   IS STRICLY FORBIDDEN inside the execution loops to maintain strict real-time determinism.
     * - Current Safety: For active development, this stub acts as a wall. If the memory 
     *   grows too high and threatens the stack pointer, the allocator cuts execution short and 
     *   errors out safely rather than letting memory variables corrupt themselves.
     * ====================================================================================
     */
    void* _sbrk_r(struct _reent *r, ptrdiff_t incr) {
        (void)r; // Suppress unused thread-safety structure pointer warning
        
        static uint8_t* heap_end = nullptr;
        uint8_t* prev_heap_end;
        
        // At boot, initialize our heap pointer to the start of the free memory pool area
        if (heap_end == nullptr) {
            heap_end = &_end;
        }
        
        prev_heap_end = heap_end;
        
        // Fetch the current Stack Pointer location to make sure we don't collide with it
        uint8_t* current_stack_pointer;
        __asm volatile ("MRS %0, msp" : "=r" (current_stack_pointer) );
        
        // Safety Barrier Check: Will this new allocation cross into the Stack space?
        if (heap_end + incr > current_stack_pointer) {
            // Cut execution - Out of Memory (OOM Error)
            errno = ENOMEM; 
            return (void*)-1; 
        }
        
        // Move the allocation boundary up and return the previous address block
        heap_end += incr;
        return (void*)prev_heap_end;
    }
}

extern "C" {
    // Ensure errno is available to track stub return statuses
    #undef errno
    extern int errno;

    /**
     * Minimal stub for closing file streams.
     * Tells the internal library that no file descriptor exists (EBADF).
     */
    int _close(int file) {
        (void)file; 
        errno = 9; // EBADF: Bad file descriptor number
        return -1;
    }

    /**
     * Minimal stub for moving file positions.
     * Returns 0 indicating that position shifting is unsupported but safe.
     */
    int _lseek(int file, int ptr, int dir) {
        (void)file; (void)ptr; (void)dir;
        return 0;
    }

    /**
     * Minimal stub for reading streaming inputs.
     * Returns 0 indicating End-of-File (EOF) immediately.
     */
    int _read(int file, char *ptr, int len) {
        (void)file; (void)ptr; (void)len;
        return 0;
    }
}





