/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/interrupt_manager.h"
#include "mcc_generated_files/oc1.h"
#include "mcc_generated_files/oc2.h"
#include "mcc_generated_files/mcc.h"
#include <stdbool.h>
//#include "mcc_generated_files/tmr1.h"
//#include "mcc_generated_files/tmr2.h"

/*
                         Main application
 */
int btn_set;
int btn_stop;
int BTN_0;
int BTN_1;
int counter_set = 0;
int sec_counter = 0;
int buzzer_flag = 0;
int BTN0_prev;
int BTN1_prev;
 

/*
bool EdgeDetector(int *BTN, int *BTN_PREV )
{
        
    if(*BTN == 0 && *BTN != *BTN_PREV){
        *BTN_PREV = *BTN;
        printf("true");
        return true;
    }    
    else{
        *BTN_PREV = *BTN;
        //printf("false");
        return false;
    }
}

*/
 
 
int main(void)
{
    //int *ptr_BTN_0 = &BTN_0;
    //int *ptr_BTN_1 = &BTN_1;
  
    SYSTEM_Initialize();
   
  
    
    buzzer_SetDigitalOutput();
    BTN_0_SetDigitalInput();
    BTN_1_SetDigitalInput();
    int stop;
    
while (1)
    {
        if (BTN_0_GetValue() == 0) {
            if (stop == 0) {
                btn_set = 1;
            }else{
            }
        stop = 1;
        } else if (BTN_1_GetValue()== 0){
            if (stop == 0) {
                btn_stop = 1;
            }else{
            }
        stop = 1;
        } else {
            stop = 0; 
        }
    
        
  
        if(buzzer_flag == 1){
            buzzer_SetLow();
            Nop();
            buzzer_SetHigh();
            Nop();
        }else{
            
            
        }
    }

}
/**
 End of File
*/

