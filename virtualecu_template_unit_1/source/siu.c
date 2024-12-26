/*
 *	Project Name	: ASE Tutorial Unit-1
 *  File Name		: siu.c
 */

/* Includes ******************************************************************/
#include "siu.h"
#include "xpc56el.h"

/*
 * @brief	SIU pin configuration function
 *
 * @param	void
 * @retval	void
 */
void SIU_Init(void)
{
	// Configure all pins which are required for your task here

	/* TO-DO: your task implementations **************************************/

	/* Input pin configurations */

	// SIU.PCR[...].R = ...;
	SIU.PCR[52].R = 0x0100;
	SIU.PCR[53].R = 0x0100;
	SIU.PCR[54].R = 0x0100;
	SIU.PCR[55].R = 0x0100;
	SIU.PCR[60].R = 0x0100;
	SIU.PCR[62].R = 0x0100;

	/* Output pin configurations */

	// SIU.PCR[...].R = ...;
	SIU.PCR[59].R = 0x0200;
	SIU.PCR[43].R = 0x0200;
	SIU.PCR[6].R = 0x0200;
	SIU.PCR[56].R = 0x0200;
	SIU.PCR[57].R = 0x0200;
	SIU.PCR[58].R = 0x0200;

	/* Analog pin configurations */

	// SIU.PCR[...].R = ...;
	SIU.PCR[66].R = 0x2500;
	SIU.PCR[32].R = 0x2500;

	/*************************************************************************/
}
