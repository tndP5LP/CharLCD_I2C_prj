/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

cystatus I2C_status;

_Bool FlgLCD_ERR;

int main()
{
    
	CyGlobalIntEnable; /* Enable global interrupts. */

	/* Start SCB UART module */
	UART_dbg_Start();
	/* initialize tinyprintf with PSoC putchar function */
	init_printf(NULL,putdata);
	UART_dbg_PutString("USB_UART\n");
	NewLine();
	NewLine();

	/* printf examples */
	UART_dbg_PutString("printf Examples");
	NewLine();
	NewLine();
    /* Run the TinyPrintf example */
    tpf_test();

    
	I2C_M_FF_Start();
	CharLCD_PCF8574_I2C_Start();

    
    
	for(;;)
    {
/*
		======================================
		| ** CHECK LCD DISPLAY CONNECTION ** |
		======================================
*/
		I2C_status = I2C_M_FF_MasterStatus();
		
		if ((I2C_status != I2C_M_FF_MSTAT_WR_CMPLT) && !FlgLCD_ERR){FlgLCD_ERR = 1;}
	
		if (FlgLCD_ERR && (I2C_status == I2C_M_FF_MSTAT_WR_CMPLT)) {
			CyDelay(250u);
			CharLCD_PCF8574_I2C_Init();
			CyDelay(250u);
			FlgLCD_ERR = 0;}
		CyDelay(1u);			
		
		I2C_M_FF_MasterClearStatus();		
/*
		=============================================
		| ** END of LCD DISPLAY CONNECTION CHECK ** |
		=============================================

		
		=====================================================================
		| ** Code Works with either 2x16 LCD Display or 4x20 LCD Display ** |
		=====================================================================
		
*/
		CharLCD_PCF8574_I2C_Position(0u,1u);
		CharLCD_PCF8574_I2C_PrintString("Cypress PSoC 4");
		//CharLCD_PCF8574_I2C_Position(1u,2u);
		CharLCD_PCF8574_I2C_PosPrintString(1u,2u,"Hello World");
		CharLCD_PCF8574_I2C_PosPrintString(2u,0u,"CY8CKIT-042 20x4 LCD");
		CharLCD_PCF8574_I2C_PosPrintString(3u,0u,"DEMO of CharLCD_PCF8574_I2C");
   		CyDelay(1u);
	}
}

/* [] END OF FILE */