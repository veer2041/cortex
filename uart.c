/*****************************************************************************
 *   uarttest.c:  main C entry file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.27  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "lpc17xx.h"
#include "type.h"
#include "uart.h"

extern volatile uint32_t UART3Count;
extern volatile uint8_t UART3Buffer[BUFSIZE];
extern volatile uint32_t UART2Count;
extern volatile uint8_t UART2Buffer[BUFSIZE];
extern volatile uint32_t UART1Count;
extern volatile uint8_t UART1Buffer[BUFSIZE];
extern volatile uint32_t UART0Count;
extern volatile uint8_t UART0Buffer[BUFSIZE];
/*****************************************************************************
**   Main Function  main()
This program has been test on Keil LPC1700 board.
*****************************************************************************/
int main (void)
{
  SystemInit();

  UARTInit(0, 9600);
  UARTInit(1, 9600);	/* baud rate setting */
  UARTInit(2, 9600);
  UARTInit(3, 9600);	/* baud rate setting */
  
  UARTSend( 0, "\r\nCoiNel Technology Solutions LLP\r\n", sizeof("\r\nCoiNel Technology Solutions LLP\r\n"));																	  
  UARTSend( 1, "\r\nCoiNel Technology Solutions LLP\r\n", sizeof("\r\nCoiNel Technology Solutions LLP\r\n"));	
   UARTSend( 2, "\r\nCoiNel Technology Solutions LLP\r\n", sizeof("\r\nCoiNel Technology Solutions LLP\r\n"));																  
  UARTSend( 3, "\r\nCoiNel Technology Solutions LLP\r\n", sizeof("\r\nCoiNel Technology Solutions LLP\r\n"));																	  

  UARTSend( 0, "Testing UART0\r\n", sizeof("Testing Uart0\r\n"));																	  
  UARTSend( 1, "Testing UART1\r\n", sizeof("Testing Uart1\r\n"));
   UARTSend( 2, "Testing UART3\r\n", sizeof("Testing Uart3\r\n"));
  UARTSend( 3, "Testing UART3\r\n", sizeof("Testing Uart3\r\n"));																	  
  
  while (1) 
  {				/* Loop forever */
	if ( UART3Count != 0 )
	{
	  LPC_UART3->IER = IER_THRE | IER_RLS;			/* Disable RBR */
	  UARTSend( 3, (uint8_t *)UART3Buffer, UART3Count );
	  UART3Count = 0;
	  LPC_UART3->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */
	}
	if ( UART2Count != 0 )
	{
	  LPC_UART2->IER = IER_THRE | IER_RLS;			/* Disable RBR */
	  UARTSend( 2, (uint8_t *)UART2Buffer, UART2Count );
	  UART2Count = 0;
	  LPC_UART2->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */
	}
	if ( UART1Count != 0 )
	{
	  LPC_UART1->IER = IER_THRE | IER_RLS;			/* Disable RBR */
	  UARTSend( 1, (uint8_t *)UART1Buffer, UART1Count );
	  UART1Count = 0;
	  LPC_UART1->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */
	}

   	if ( UART0Count != 0 )
	{
	  LPC_UART0->IER = IER_THRE | IER_RLS;			/* Disable RBR */
	  UARTSend( 0, (uint8_t *)UART0Buffer, UART0Count );
	  UART0Count = 0;
	  LPC_UART0->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */
	}





  }
}

/*****************************************************************************
**                            End Of File
*****************************************************************************/
