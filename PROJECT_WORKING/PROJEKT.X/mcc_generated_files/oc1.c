
/**
  OC1 Generated Driver API Source File

  @Company
    Microchip Technology Inc.

  @File Name
    oc1.c

  @Summary
    This is the generated source file for the OC1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for driver for OC1.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.4
        Device            :  PIC24FJ128GA705
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB 	          :  MPLAB X v6.05
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

#include "oc1.h"

/** OC Mode.

  @Summary
    Defines the OC Mode.

  @Description
    This data type defines the OC Mode of operation.

*/

static uint16_t         gOC1Mode;

/**
  Section: Driver Interface
*/


void OC1_Initialize (void)
{
    // ENFLT0 disabled; ENFLT1 disabled; OCFLT2 disabled; ENFLT2 disabled; OCSIDL disabled; OCM Center-Aligned PWM mode; OCFLT1 disabled; OCFLT0 disabled; OCTSEL TMR1; TRIGMODE Only Software; 
    OC1CON1 = 0x1007;
    // SYNCSEL TMR1; TRIGSTAT disabled; DCB Start of instruction cycle; OCINV disabled; OCTRIG Sync; OC32 disabled; FLTOUT disabled; OCTRIS disabled; FLTMD Cycle; FLTTRIEN disabled; 
    OC1CON2 = 0x0B;
    // OC1RS 0; 
    OC1RS = 0x00;
    // OC1R 0; 
    OC1R = 0x00;
	
    gOC1Mode = OC1CON1bits.OCM;
    
    IFS0bits.OC1IF = false;
    IEC0bits.OC1IE = true;
}

void __attribute__ ((weak)) OC1_CallBack(void)
{
    // Add your custom callback code here
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _ISR _OC1Interrupt( void )
{	
    if(IFS0bits.OC1IF)
    {
		// OC1 callback function 
		OC1_CallBack();
        IFS0bits.OC1IF = 0;
    }
}


void OC1_Start( void )
{
    OC1CON1bits.OCM = gOC1Mode;
}


void OC1_Stop( void )
{
    OC1CON1bits.OCM = 0;
}

void OC1_SecondaryValueSet( uint16_t secVal )
{
   
    OC1RS = secVal;
}


void OC1_PrimaryValueSet( uint16_t priVal )
{
   
    OC1R = priVal;
}

bool OC1_IsCompareCycleComplete( void )
{
    return(IFS0bits.OC1IF);
}


bool OC1_FaultStatusGet( OC1_FAULTS faultNum )
{
    bool status;
    /* Return the status of the fault condition */
   
    switch(faultNum)
    { 
        case OC1_FAULT0:
			status = OC1CON1bits.OCFLT0;
            break;
        case OC1_FAULT1:
			status = OC1CON1bits.OCFLT1;
            break;
        case OC1_FAULT2:
			status = OC1CON1bits.OCFLT2;
            break;
        default :
            break;

    }
    return(status);
}


void OC1_FaultStatusClear( OC1_FAULTS faultNum )
{
    
    switch(faultNum)
    { 
        case OC1_FAULT0:
			OC1CON1bits.OCFLT0 = 0;
                break;
        case OC1_FAULT1:
			OC1CON1bits.OCFLT1 = 0;
                break;
        case OC1_FAULT2:
			OC1CON1bits.OCFLT2 = 0;
                break;
        default :
                break;
    }    
}


void OC1_ManualTriggerSet( void )
{
    OC1CON2bits.TRIGSTAT= true; 
}

bool OC1_TriggerStatusGet( void )
{
    return( OC1CON2bits.TRIGSTAT );
}


void OC1_TriggerStatusClear( void )
{
    /* Clears the trigger status */
    OC1CON2bits.TRIGSTAT = 0;
}

/**
 End of File
*/
