/*
 *  Project Name	: ASE Tutorial Unit-1
 *  File Name		: main.c
 */

/* Includes ******************************************************************/
#include "init.h"

#include "xpc56el.h"
#include "siu.h"

/* Global variables **********************************************************/

// put any global variables you need here
int counter = 0;
int up_counter = 1;
int pot_value;
int ldr_value;

/* Task-1 implementation *****************************************************/
void task_pot(int value)
{

        /* TO-DO: your task implementations **************************************/

        if (value < 682)
        {
                SIU.GPDO[59].R = 0; // U1
                SIU.GPDO[43].R = 0; // U2
                SIU.GPDO[6].R = 0;  // U3
                SIU.GPDO[58].R = 0; // Tx
                SIU.GPDO[57].R = 0; // Rx
                SIU.GPDO[56].R = 1; // P
        }
        else if (value < 1364)
        {
                SIU.GPDO[59].R = 0; // U1
                SIU.GPDO[43].R = 0; // U2
                SIU.GPDO[6].R = 0;  // U3
                SIU.GPDO[58].R = 0; // Tx
                SIU.GPDO[57].R = 1; // Rx
                SIU.GPDO[56].R = 1; // P
        }
        else if (value < 2046)
        {
                SIU.GPDO[59].R = 0; // U1
                SIU.GPDO[43].R = 0; // U2
                SIU.GPDO[6].R = 0;  // U3
                SIU.GPDO[58].R = 1; // Tx
                SIU.GPDO[57].R = 1; // Rx
                SIU.GPDO[56].R = 1; // P
        }
        else if (value < 2728)
        {
                SIU.GPDO[59].R = 0; // U1
                SIU.GPDO[43].R = 0; // U2
                SIU.GPDO[6].R = 1;  // U3
                SIU.GPDO[58].R = 1; // Tx
                SIU.GPDO[57].R = 1; // Rx
                SIU.GPDO[56].R = 1; // P
        }
        else if (value < 3410)
        {
                SIU.GPDO[59].R = 0; // U1
                SIU.GPDO[43].R = 1; // U2
                SIU.GPDO[6].R = 1;  // U3
                SIU.GPDO[58].R = 1; // Tx
                SIU.GPDO[57].R = 1; // Rx
                SIU.GPDO[56].R = 1; // P
        }
        else
        {
                SIU.GPDO[59].R = 1; // U1
                SIU.GPDO[43].R = 1; // U2
                SIU.GPDO[6].R = 1;  // U3
                SIU.GPDO[58].R = 1; // Tx
                SIU.GPDO[57].R = 1; // Rx
                SIU.GPDO[56].R = 1; // P
        }

        /*************************************************************************/
}

/* Task-2 implementation *****************************************************/
void task_ldr(int value)
{

        /* TO-DO: your task implementations **************************************/

        task_pot(value);

        /*************************************************************************/
}

/* Task-3 implementation *****************************************************/
void task_counter(void)
{

        /* TO-DO: your task implementations **************************************/

        if (up_counter)
        {
                counter = (counter + 1) % 8; // Circular increment (0-7)
        }
        else
        {
                counter = (counter == 0) ? 7 : counter - 1; // Circular decrement
        }

        switch (counter)
        {
        case 0:
                SIU.GPDO[59].R = 0;
                SIU.GPDO[43].R = 0;
                SIU.GPDO[6].R = 0;
                break;
        case 1:
                SIU.GPDO[59].R = 0;
                SIU.GPDO[43].R = 0;
                SIU.GPDO[6].R = 1;
                break;
        case 2:
                SIU.GPDO[59].R = 0;
                SIU.GPDO[43].R = 1;
                SIU.GPDO[6].R = 0;
                break;
        case 3:
                SIU.GPDO[59].R = 0;
                SIU.GPDO[43].R = 1;
                SIU.GPDO[6].R = 1;
                break;
        case 4:
                SIU.GPDO[59].R = 1;
                SIU.GPDO[43].R = 0;
                SIU.GPDO[6].R = 0;
                break;
        case 5:
                SIU.GPDO[59].R = 1;
                SIU.GPDO[43].R = 0;
                SIU.GPDO[6].R = 1;
                break;
        case 6:
                SIU.GPDO[59].R = 1;
                SIU.GPDO[43].R = 1;
                SIU.GPDO[6].R = 0;
                break;
        case 7:
                SIU.GPDO[59].R = 1;
                SIU.GPDO[43].R = 1;
                SIU.GPDO[6].R = 1;
                break;
        }

        /*************************************************************************/
}

/*
 * @brief	Main program
 *
 * @param	void
 * @retval	int
 */
int main(void)
{
        /* peripherals initialization, do not remove */
        peripheralsInit();

        /* TO-DO: your task implementations **************************************/

        /* Configure and start timer channels */
        // PIT_ConfigureTimer(<channel>, <interval in milliseconds>);
        PIT_ConfigureTimer(1, 1000);

        /*************************************************************************/

        /* main program */
        while (1)
        {
                /* System function, do not remove */
                systemFunction();
                /* TO-DO: your task implementations **********************************/

                if (SIU.GPDI[52].R == 1 && SIU.GPDI[53].R == 0 && SIU.GPDI[54].R == 0)
                {
                        pot_value = ADC0.CDR[5].R & 0x00000FFF;
                        task_pot(pot_value);
                }
                else if (SIU.GPDI[52].R == 0 && SIU.GPDI[53].R == 1 && SIU.GPDI[54].R == 0)
                {
                        ldr_value = ADC1.CDR[3].R & 0x00000FFF;
                        task_ldr(ldr_value);
                }
                else if (SIU.GPDI[52].R == 0 && SIU.GPDI[53].R == 0 && SIU.GPDI[54].R == 1)
                {
                        /* Start/Stop timer based on SW4 */
                        if (SIU.GPDI[55].R == 1)
                        {
                                PIT_StartTimer(1); // Start timer if SW4 is active
                        }
                        else
                        {
                                PIT_StopTimer(1); // Stop the timer when SW4 is inactive
                        }
                }
                else
                {
                        SIU.GPDO[59].R = 0; // U1
                        SIU.GPDO[43].R = 0; // U2
                        SIU.GPDO[6].R = 0;  // U3
                        SIU.GPDO[58].R = 0; // Tx
                        SIU.GPDO[57].R = 0; // Rx
                        SIU.GPDO[56].R = 0; // P
                }

                /* Switch between up-counter and down-counter */
                if (SIU.GPDI[62].R == 1)
                { // If BT2 pressed, switch to down-counter
                        up_counter = 0;
                }
                else if (SIU.GPDI[60].R == 1)
                { // If BT1 pressed, switch back to up-counter
                        up_counter = 1;
                }

                /*********************************************************************/

                /* 10 ms OS delay */
                osalThreadDelayMilliseconds(10UL);
        }
}

/*
 * @brief	PIT timer channel 1 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_1(void)
{

        /* TO-DO: your task implementations **************************************/

        task_counter();

        /*************************************************************************/
}

/*
 * @brief	PIT timer channel 2 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_2(void)
{

        /* TO-DO: your task implementations **************************************/

        /*************************************************************************/
}

/*
 * @brief	PIT timer channel 3 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_3(void)
{

        /* TO-DO: your task implementations **************************************/

        /*************************************************************************/
}
