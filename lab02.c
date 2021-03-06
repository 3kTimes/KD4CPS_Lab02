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

volatile uint8_t min = 0;
volatile uint8_t sec = 0;
volatile uint16_t msec = 0;

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
    
    //Timer 1
    
    T1CONbits.TON = 0; // Disable the Timers
    T1CONbits.TCKPS = 0b11; // Set Prescaler 256
    T1CONbits.TCS = 1; // Set Clock Source (external = 1)
    T1CONbits.TGATE = 0; // Set Gated Timer Mode -> don't use gating //this line can be ignored, if TCS =  1 (have a look at the manual)  
    T1CONbits.TSYNC = 0; // T1: Set External Clock Input Synchronization -> no sync
    PR1 = 128; // Load Timer Periods (???)
    TMR1 = 0x00; // Reset Timer Values
    IPC0bits.T1IP = 0x01; // Set Interrupt Priority (actually Level 1)
    IFS0bits.T1IF = 0; // Clear Interrupt Flags
    IEC0bits.T1IE = 1; // Enable Interrupts
    T1CONbits.TON = 1; // Enable the Timers
    
    //Timer 2
    
    T2CONbits.TON = 0; // Disable the Timers
    T2CONbits.TCKPS = 0b11; // Set Prescaler 256
    T2CONbits.TCS = 0; // Set Clock Source (internal = 0)
    T2CONbits.TGATE = 0; // Set Gated Timer Mode -> don't use gating  
    PR2 = 100; // Load Timer Periods (???)
    TMR2 = 0x00; // Reset Timer Values
    IPC1bits.T2IP = 0x01; // Set Interrupt Priority (actually Level 1)
    IFS0bits.T2IF = 0; // Clear Interrupt Flags
    IEC0bits.T2IE = 1; // Enable Interrupts
    T2CONbits.TON = 1; // Enable the Timers
    
    // Timer 3
    
    T3CONbits.TON = 0; // Disable the Timers
    T3CONbits.TCKPS = 0b00; // Set Prescaler 1:1
    T3CONbits.TCS = 0; // Set Clock Source (internal = 0)
    T3CONbits.TGATE = 0; // Set Gated Timer Mode -> don't use gating //this line can be ignored, if TCS =  1 (have a look at the manual)  
    PR3 = 0xFFFF; // Load Timer Periods (highest value possible?)
    TMR3 = 0x00; // Reset Timer Values
    IPC2bits.T3IP = 0x01; // Set Interrupt Priority (actually Level 1)
    CLEARBIT(IFS0bits.T3IF); //= 0; // Clear Interrupt Flags
    IEC0bits.T3IE = 0; // Enable Interrupts --> (important: all)
    T3CONbits.TON = 1; // Enable the Timers
  
}

void timer_loop()
{
    uint16_t i = 1;
    
    // print assignment information
    lcd_printf("Lab02: Int & Timer");
    lcd_locate(0, 1);
    lcd_printf("Group: Boyang & Ron");
    
    CLEARBIT(LED1_TRIS);   //set LED1 as output
    CLEARBIT(LED2_TRIS);   //set LED2 as output
    CLEARBIT(LED3_TRIS);   //set LED3 as output
    CLEARBIT(LED5_TRIS);   //set LED3 as output
    
    while(TRUE)
    {
       i = i + 1;
       float store;
     
       if(i == 2000){
           
           lcd_locate(0, 4);
           lcd_printf("Cycle:%u", TMR3);
           
           lcd_locate(0, 5);
           store = (float) TMR3 / 12800;
           lcd_printf("Cycletime: %1.3f ms", store);
           TMR3 = 0x00;
           
           lcd_locate(0, 7);
           lcd_printf("%02u:%02u.%03u", min,sec,msec);
           TOGGLELED(LED3_PORT);
           i = 1;
       }
    }
}

void __attribute__((__interrupt__, __shadow__, __auto_psv__)) _T1Interrupt(void)
{ 
    
    TOGGLELED(LED2_PORT);
    
    
    IFS0bits.T1IF = 0;
      
}

void __attribute__((__interrupt__, __shadow__, __auto_psv__)) _T2Interrupt(void)
{ // invoked every ??
      
    TOGGLELED(LED1_PORT);
    
    msec = msec +2;
    
    if(msec == 1000){
        msec = 0;
        sec++;
    }
    if(sec == 60){
        sec = 0;
        min++;
    }
    
       
    IFS0bits.T2IF = 0;
}



   
