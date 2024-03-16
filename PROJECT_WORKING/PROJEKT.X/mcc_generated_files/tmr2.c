
/**
  TMR2 Generated Driver API Source File 

  @Company
    Microchip Technology Inc.

  @File Name
    tmr2.c

  @Summary
    This is the generated source file for the TMR2 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for driver for TMR2. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.4
        Device            :  PIC24FJ128GA705
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB             :  MPLAB X v6.05
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include <stdio.h>
#include "tmr2.h"
#include "oc1.h"
#include "oc2.h"

/**
 Section: File specific functions
*/
void (*TMR2_InterruptHandler)(void) = NULL;
void TMR2_CallBack(void);

/**
  Section: Data Type Definitions
*/

/** TMR Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintenance of the hardware instance.

  @Description
    This defines the object required for the maintenance of the hardware
    instance. This object exists once per hardware instance of the peripheral.

  Remarks:
    None.
*/

typedef struct _TMR_OBJ_STRUCT
{
    /* Timer Elapsed */
    volatile bool           timerElapsed;
    /*Software Counter value*/
    volatile uint8_t        count;

} TMR_OBJ;

static TMR_OBJ tmr2_obj;

/**
  Section: Driver Interface
*/

void TMR2_Initialize (void)
{
    //TMR2 0; 
    TMR2 = 0x00;
    //Period = 0.001 s; Frequency = 16000000 Hz; PR2 249; 
    PR2 = 0xF9;
    //TCKPS 1:64; T32 16 Bit; TON enabled; TSIDL disabled; TCS FOSC/2; TECS SOSC; TGATE disabled; 
    T2CON = 0x8020;

    if(TMR2_InterruptHandler == NULL)
    {
        TMR2_SetInterruptHandler(&TMR2_CallBack);
    }

    IFS0bits.T2IF = false;
    IEC0bits.T2IE = true;
	
    tmr2_obj.timerElapsed = false;

}


void __attribute__ ( ( interrupt, no_auto_psv ) ) _T2Interrupt (  )
{
    /* Check if the Timer Interrupt/Status is set */

    //***User Area Begin

    // ticker function call;
    // ticker is 1 -> Callback function gets called everytime this ISR executes
    if(TMR2_InterruptHandler) 
    { 
           TMR2_InterruptHandler(); 
    }

    //***User Area End

    tmr2_obj.count++;
    tmr2_obj.timerElapsed = true;
    IFS0bits.T2IF = false;
}

void TMR2_Period16BitSet( uint16_t value )
{
    /* Update the counter values */
    PR2 = value;
    /* Reset the status information */
    tmr2_obj.timerElapsed = false;
}

uint16_t TMR2_Period16BitGet( void )
{
    return( PR2 );
}

void TMR2_Counter16BitSet ( uint16_t value )
{
    /* Update the counter values */
    TMR2 = value;
    /* Reset the status information */
    tmr2_obj.timerElapsed = false;
}

uint16_t TMR2_Counter16BitGet( void )
{
    return( TMR2 );
}

uint16_t CompareValue1;
uint16_t CompareValue2;
extern int buzzer_flag;

enum Brightness_States {
    Brightness_Increment,
    Brightness_Decrement
};

enum Brightness_States My__Brightness_States;


void __attribute__ ((weak)) TMR2_CallBack(void)
{
    if(buzzer_flag == 1){
        
    CompareValue1 = CompareValue1 <= 0x0190? CompareValue1+1:0;
    OC1_PrimaryValueSet(CompareValue1);
    CompareValue2 = CompareValue2 <= 0x0190? CompareValue2-1:0x0190;
    OC2_PrimaryValueSet(CompareValue2);
    
    }else{

    switch (My__Brightness_States){
        case Brightness_Increment:
          if(CompareValue1 < 0x18F){
               CompareValue1++;
               OC1_PrimaryValueSet(CompareValue1);
               OC2_PrimaryValueSet(CompareValue1);
          }else{
              My__Brightness_States = Brightness_Decrement;
          }
          
        break;
        
        case Brightness_Decrement:
            if(CompareValue1 > 0x0){
               CompareValue1--;
               OC1_PrimaryValueSet(CompareValue1);
               OC2_PrimaryValueSet(CompareValue1);
            }else{
                My__Brightness_States = Brightness_Increment;
            }
            
        break;  
    }
    }
}

    
void  TMR2_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC0bits.T2IE = false;
    TMR2_InterruptHandler = InterruptHandler; 
    IEC0bits.T2IE = true;
}

void TMR2_Start( void )
{
    /* Reset the status information */
    tmr2_obj.timerElapsed = false;

    /*Enable the interrupt*/
    IEC0bits.T2IE = true;

    /* Start the Timer */
    T2CONbits.TON = 1;
}

void TMR2_Stop( void )
{
    /* Stop the Timer */
    T2CONbits.TON = false;

    /*Disable the interrupt*/
    IEC0bits.T2IE = false;
}

bool TMR2_GetElapsedThenClear(void)
{
    bool status;
    
    status = tmr2_obj.timerElapsed;

    if(status == true)
    {
        tmr2_obj.timerElapsed = false;
    }
    return status;
}

int TMR2_SoftwareCounterGet(void)
{
    return tmr2_obj.count;
}

void TMR2_SoftwareCounterClear(void)
{
    tmr2_obj.count = 0; 
}

/**
 End of File
*/
