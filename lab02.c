#include "lab02.h"

#include <xc.h>
#include <p33Fxxxx.h>
//do not change the order of the following 2 definitions
#define FCY 12800000UL
#include <libpic30.h>

#include "types.h"
#include "lcd.h"
#include "led.h"

#define FCY_EXT 32768

void initialize_timer()
{
    // Enable RTC Oscillator -> this effectively does OSCCONbits.LPOSCEN = 1
    // but the OSCCON register is lock protected. That means you would have to 
    // write a specific sequence of numbers to the register OSCCONL. After that 
    // the write access to OSCCONL will be enabled for one instruction cycle.
    // The function __builtin_write_OSCCONL(val) does the unlocking sequence and
    // afterwards writes the value val to that register. (OSCCONL represents the
    // lower 8 bits of the register OSCCON)
    __builtin_write_OSCCONL(OSCCONL | 2);
    
    //Timer 2
    
    T2CONbits.TON = 0; // Disable the Timers
    
    T2CONbits.TCKPS = 0x11; // Set Prescaler 256

    T2CONbits.TCS = 0; // Set Clock Source (internal = 0)
    
    T2CONbits.TGATE = 0; // Set Gated Timer Mode -> don't use gating  

    T2CONbits.TSYNC = 0; // T1: Set External Clock Input Synchronization -> no sync

    PR2 = 100000; // Load Timer Periods (???)
    
    TMR2 = 0x00; // Reset Timer Values

    IPC0bits.T1IP = 0x01; // Set Interrupt Priority (actually Level 1)

    IFS1bits.T2IF = 0; // Clear Interrupt Flags

    IEC1bits.T2IE = 1; // Enable Interrupts

    T2CONbits.TON = 1; // Enable the Timers
    
    //Timer 1
    
    T1CONbits.TON = 0; // Disable the Timers
    
    T1CONbits.TCKPS = 0x11; // Set Prescaler 256

    T1CONbits.TCS = 1; // Set Clock Source (external = 1)
    
    //T1CONbits.TGATE = 0; // Set Gated Timer Mode -> don't use gating //this line can be ignored, if TCS =  1 (have a look at the manual)  

    T1CONbits.TSYNC = 0; // T1: Set External Clock Input Synchronization -> no sync

    PR1 = 100000; // Load Timer Periods (???)
    
    TMR1 = 0x00; // Reset Timer Values

    IPC0bits.T1IP = 0x01; // Set Interrupt Priority (actually Level 1)

    IFS0bits.T2IF = 0; // Clear Interrupt Flags

    IEC0bits.T2IE = 1; // Enable Interrupts

    T2C0Nbits.TON = 1; // Enable the Timers

    
    // Timer 3
    
    T3CONbits.TON = 0; // Disable the Timers
    
    T1CONbits.TCKPS = 0x00; // Set Prescaler 1:1

    T1CONbits.TCS = 0; // Set Clock Source (internal = 0)
    
    T1CONbits.TGATE = 0; // Set Gated Timer Mode -> don't use gating //this line can be ignored, if TCS =  1 (have a look at the manual)  

    T1CONbits.TSYNC = 0; // T1: Set External Clock Input Synchronization -> no sync

    PR3 = 1000000000000000000000; // Load Timer Periods (highets value possible?)
    
    TMR3 = 0x00; // Reset Timer Values

    IPC2bits.T1IP = 0x01; // Set Interrupt Priority (actually Level 1)

    IFS2bits.T2IF = 0; // Clear Interrupt Flags

    IEC2bits.T2IE = 1; // Enable Interrupts

    T2C2Nbits.TON = 1; // Enable the Timers
}

void timer_loop()
{
    // print assignment information
    lcd_printf("Lab02: Int & Timer");
    lcd_locate(0, 1);
    lcd_printf("Group: Ron & Leo");
    
    while(TRUE)
    {
        
    }
}

void __attribute__((__interrupt__, __shadow__, __auto_psv__)) _T1Interrupt(void)
{ // invoked every ??
    
}

void __attribute__((__interrupt__, __shadow__, __auto_psv__)) _T2Interrupt(void)
{ // invoked every ??
    
}
