//-----------------------------------------------------------------------------
// TP1_BSE.c
//-----------------------------------------------------------------------------
// AUTH: 
// DATE: 
//
// Target: C8051F02x
// Tool chain: KEIL Microvision5
//
//-----------------------------------------------------------------------------
// Déclarations Registres et Bits de l'espace SFR
#include "intrins.h"
#include<c8051F020.h>
#include<c8051F020_SFR16.h>
#include<TP1_BSE_Lib_Config_Globale.h>
#include<TP1_BSE_Lib_Divers.h>

#define LED_ON 1
#define LED_OFF 0

#define BP_ON 0
#define BP_OFF 1

sbit LED = P1^6;  // LED
sbit BP = P3^7; // BOUTON
bit ACK_BP = BP_OFF;
bit ETAT_LED = LED_ON;
sbit VISU_INT7_START = P2^0;

//------------------------------------------------------------------------------------
// Function Prototypes

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------
void ISR_INT7() interrupt 19
{
	P3IF &=~0x80;
	ETAT_LED = !ETAT_LED;
	
	VISU_INT7_START=1;
	VISU_INT7_START=0;
	
	P6 |= (1<<1);
	P6 &=~(1<<1);
	
	P6 |= (1<<0);
	P6 &=~(1<<1);
}

void enableInterrupt(void)
	{
		P3IF &= ~(1<<7);
		P3IF |= (1<<2);
		EIE2 |= (1<<5);
		EIP2 |= (1<<5);
	}

void main (void) {
				enableInterrupt();
				EA =1;
	      Init_Device();
						P3MDOUT&=~(1<<7);
						BP=1;
						P2MDOUT |= (1<<0);
						while(1)
						{
//							if ((BP == BP_ON) && (ACK_BP == BP_OFF))
//								{
//									ETAT_LED = !ETAT_LED;
//									ACK_BP = BP_ON;
//								}
//							if (BP== BP_OFF)
//								{
//									ACK_BP = BP_OFF;
//								}
							if (ETAT_LED == LED_ON)
								{
									 LED = LED_ON;
									 Software_Delay(2); // Allumaghe 20ms
									 LED = LED_OFF;
									 Software_Delay(10); // Extinction 100ms						 
								}
							else
								{
									LED= LED_OFF;
								}	
					}
					               	
			}
//*****************************************************************************	 
