#include "ISR.h"
#include "Button.h"
#include "Motor.h"
#include "HMI.h"
#include "LCD.h"
#include "Console.h"
#include "Events.h"
#include "MXK.h"
#include "SPI.h"
#include "ADC.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ISR_Disable()
{
    INTCONbits.PEIE	= 0;
    INTCONbits.GIE	= 0;
    INTCONbits.INT0IE	= 0;
    INTCONbits.INT0IF	= 0;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ISR_Enable()
{
    INTCONbits.PEIE	= 1;
    INTCONbits.GIE	= 1;
    INTCONbits.INT0IE	= 1;
    INTCONbits.INT0IF	= 0;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void interrupt ISR_Function()
{
    //Clear Interrupt flag
    INTCONbits.INT0IF	= 0;

#ifdef ISR_NOBLOCK
    ISR_Disable();
#endif

#ifdef ISR_SPI
    //SPI1 Interrupt
    if (SPI1_ISR_CONDITION)
	SPI1_ISR();
    //SPI2 Interrupt
    if (SPI2_ISR_CONDITION)
	SPI2_ISR();
#endif

#ifdef ISR_I2C
    //I2C1 Interrupt
    if (I2C1_ISR_CONDITION)
	I2C1_ISR();
    //I2C2 Interrupt
    if (I2C2_ISR_CONDITION)
	I2C2_ISR();
#endif    

#if defined(ENABLEMOTOR)
    //Timer0 Interrupt
    if (TIMER0_ISR_CONDITION)
	Timer0_ISR();
#endif
    
#ifdef ADCTEST
    //ADC Interrupt
    if (ADC_ISR_CONDITION)
	ADC_ISR();
#endif
    
#ifdef ISR_NOBLOCK
    ISR_Enable();
#endif

}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
