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

#include "string.h"

extern volatile uint32_t UART3Count;
extern volatile uint8_t UART3Buffer[BUFSIZE];
extern volatile uint32_t UART2Count;
extern volatile uint8_t UART2Buffer[BUFSIZE];
extern volatile uint32_t UART1Count;
extern volatile uint8_t UART1Buffer[BUFSIZE];
extern volatile uint32_t UART0Count;
extern volatile uint8_t UART0Buffer[BUFSIZE];

void send_command(unsigned char *data);
int getreply(void);
void delay_ms(int a),init_esp(),connectrouter(),mux(),server(),senddata(),clear_sting(unsigned char *str, unsigned int val ),ledon();
signed int tp_strcmp( unsigned char *s1, unsigned char *s2);
unsigned char string_rec[20];
unsigned char machine_num[50];
void senddata(void);

/*****************************************************************************
**   Main Function  main()
This program has been test on Keil LPC1700 board.
*****************************************************************************/
int main (void)
{
	unsigned short int i;
	SystemInit();
	LPC_PINCON->PINSEL4 = 0x000000;  //Configure the PORT2 Pins as GPIO;
    LPC_GPIO2->FIODIR = 0xffffffff;  //Configure the PORT2 pins as OUTPUT;
 
  	init_esp();
  
  	UARTSend( 0, "echo completed", 15);
  
 //	connectrouter();
	UARTSend( 0, "router completed", 15);


//	mux();

	  	

	delay_ms(100);

 		while (1) 
 		 {				/* Loop forever */

		 	if ( UART0Count != 0 )
			{
	  			LPC_UART1->IER = IER_THRE | IER_RLS;			/* Disable RBR */
	  			UARTSend( 0, (uint8_t *)UART1Buffer, UART1Count );
	  			UART1Count = 0;
	  		
			delay_ms(300);

  			i=getreply();


			switch(i) {
					case 1  :
										ledon();
   				 							 
	
					case 2  :
										senddata();
										

					}

	   	

/*	if ( UART0Count != 0 )
	{
	  LPC_UART1->IER = IER_THRE | IER_RLS;		
	  UARTSend( 1, (uint8_t *)UART0Buffer, UART0Count );
	  UART0Count = 0;
	  LPC_UART1->IER = IER_THRE | IER_RLS | IER_RBR;
	  break;
	}

   	else if ( UART1Count != 0 )
	{
	  LPC_UART0->IER = IER_THRE | IER_RLS;		
	  UARTSend( 0, (uint8_t *)UART1Buffer, UART1Count );
	  UART1Count = 0;
	  LPC_UART0->IER = IER_THRE | IER_RLS | IER_RBR;	
	}	 */
/*	else{
		UARTSend( 0, "no", 3 );
	}						  */
 		 	  }
			
	}												  
}

void connectrouter(){
	unsigned short int i,j;
	unsigned char data_rcv[3];
 
//  	unsigned char s;
  	send_command("AT+CWJAP=\"D-Link_DIR-600M\",\"\"\r\n");
  	delay_ms(100);
	UARTSend( 0, (uint8_t *)UART1Buffer, UART1Count );
	i=0;

	while(UART1Buffer[i++] != 'O');
//	data_rcv[0]='O';
//	data_rcv[1]='K';
//	
//	data_rcv[2]='\0';
	i--;
	for(j=0;j<2;j++)
	{
	 	data_rcv[j]= UART1Buffer[i++];
	}
	data_rcv[j]='\0';
	UARTSend( 0, (uint8_t *)data_rcv, sizeof(data_rcv) );
	if((tp_strcmp((uint8_t *)data_rcv,"OK")) == 0)
			{
				UARTSend( 0, "ROUTER completed", 5 );
				//	server();	
			}
		else
		{
			UARTSend( 0, "ROUTER unsuccess", 9 );
		}
  	send_command("AT+CIFSR\r\n");
   	delay_ms(100);
	return;
}								  

void init_esp(){
	unsigned short int i,j;
	unsigned char data_rcv[3];
	clear_sting(UART1Buffer,UART1Count);
	UARTInit(0, 9600); /* uart0 */
  	UARTInit(1, 9600);	/* baud rate setting for esp */
   	UARTSend( 0, "wait", 4);
	UARTSend( 1, "ATE0\r\n", sizeof("ATE0\r\n"));	
 	delay_ms(100);
	clear_sting(UART1Buffer,UART1Count);
	UARTSend( 0, (uint8_t *)UART1Buffer, UART1Count );

	UARTSend( 1, "AT\r\n", sizeof("AT\r\n"));	
 	delay_ms(100); 
	UARTSend( 0, (uint8_t *)UART1Buffer, UART1Count );



	UARTSend( 0, (uint8_t *)UART1Buffer, UART1Count );
	i=0;

	while(UART1Buffer[i++] != 'O');
//	data_rcv[0]='O';
//	data_rcv[1]='K';
//	
//	data_rcv[2]='\0';
	i--;
	for(j=0;j<2;j++)
	{
	 	data_rcv[j]= UART1Buffer[i++];
	}
	data_rcv[j]='\0';
	UARTSend( 0, (uint8_t *)data_rcv, sizeof(data_rcv) );
	if((tp_strcmp((uint8_t *)data_rcv,"OK")) == 0)
		{
			UARTSend( 0, "Initialiize", 5 );	
		}
		else
		{
			UARTSend( 0, "Initialiize unsuccess", 9 );
		}
	return;
}

void mux(){
	unsigned short int i,j;
	unsigned char data_rcv[3];
	clear_sting(UART1Buffer,UART1Count);
	UARTSend( 1, "AT+CIPMUX=1\r\n", sizeof("AT+CIPMUX=1\r\n"));
	delay_ms(300);
	

	UARTSend( 0, (uint8_t *)UART1Buffer, UART1Count );
	i=0;

	while(UART1Buffer[i++] != 'O');
//	data_rcv[0]='O';
//	data_rcv[1]='K';
//	
//	data_rcv[2]='\0';
	i--;
	for(j=0;j<2;j++)
	{
	 	data_rcv[j]= UART1Buffer[i++];
	}
	data_rcv[j]='\0';
	UARTSend( 0, (uint8_t *)data_rcv, sizeof(data_rcv) );
	if((tp_strcmp((uint8_t *)data_rcv,"OK")) == 0)
			{
				UARTSend( 0, "Mux completed", 5 );
					server();	
			}
		else
		{
			UARTSend( 0, "Mux unsuccess", 9 );
		}
	return;	
}
void server(){
	unsigned short int i,j;
	unsigned char data_rcv[3];
	clear_sting(UART1Buffer,UART1Count);
	UARTSend( 1, "AT+CIPSERVER=1,139\r\n", sizeof("AT+CIPSERVER=1,139\r\n"));
 	delay_ms(200);
	UARTSend( 0, (uint8_t *)UART1Buffer, UART1Count );
	i=0;

	while(UART1Buffer[i++] != 'O');
//	data_rcv[0]='O';
//	data_rcv[1]='K';
//	
//	data_rcv[2]='\0';
	i--;
	for(j=0;j<2;j++)
	{
	 	data_rcv[j]= UART1Buffer[i++];
	}
	data_rcv[j]='\0';
	UARTSend( 0, (uint8_t *)data_rcv, sizeof(data_rcv) );
	if((tp_strcmp((uint8_t *)data_rcv,"OK")) == 0)
			{
				UARTSend( 0, "set as Server completed", 20 );
				//	return;
					getreply();	
			}
		else
		{
			UARTSend( 0, "server unsuccess", 9 );
		}
	return;		
}

void send_command(unsigned char *data){
	UARTSend( 1, data, sizeof(data) );
//	getreply();
	return;	
}

void ledon(){

	clear_sting(UART1Buffer,UART1Count);
	UARTSend( 0, "LED1 ON\r\n", sizeof("LED1 ON\r\n"));
	LPC_GPIO2->FIOSET = 0xffffffff;     // Make all the Port pins as high  
    delay_ms(100);
	return;
}

void senddata(){
   	unsigned short int i,j;
	unsigned char data_rcv[3];
//	clear_sting(UART1Buffer,UART1Count);
//	clear_sting(string_rec,sizeof(string_rec));

	UART1Count=0; 
//	delay_ms(10000);
	UARTSend( 0, "sending data", 13);
	UARTSend( 1, "AT+CIPSEND=0,5\r\n", sizeof("AT+CIPSEND=0,5\r\n"));
	delay_ms(100);


	UARTSend( 0, (uint8_t *)UART1Buffer, UART1Count );
	i=0;

	while(UART1Buffer[i++] != '>');

	
	i--;
	for(j=0;j<1;j++)
	{
	 	data_rcv[j]= UART1Buffer[i++];
	}
	data_rcv[j]='\0';
	UARTSend( 0, (uint8_t *)data_rcv, sizeof(data_rcv) );
	if((tp_strcmp((uint8_t *)data_rcv,">")) == 0)
			{
		//		UARTSend( 0, "DATA SENT", 20 );
				UARTSend( 1, "START\r\n", sizeof("START\r\n"));
			}
		else
		{
			UARTSend( 0, "DATA NOT SENT to client", 9 );
		}
	return;
}

signed int tp_strcmp( unsigned char *s1, unsigned char *s2)
	{
   		for (; *s1 == *s2; s1++, s2++)
      		if (*s1 == '\0')
         	return(0);
   		return((*s1 < *s2) ? -1: 1);
	}


void clear_sting(unsigned char *str, unsigned int val ){
	int i = 0 ;
     for( i = 0 ; i < val ; i++ )
     {
          str[i] = '\0' ;
     }
	 return ;
}

int getreply(){
	unsigned short int i,j;
	unsigned char data_rcv[6];
		clear_sting(UART0Buffer,UART0Count);
 	while (1) 
 	 {				/* Loop forever */
 	 delay_ms(300);

  	UARTSend( 0, (uint8_t *)UART0Buffer, UART0Count );
	i=0;

	while(UART0Buffer[i++] != 'S');

	i--;
	for(j=0;j<7;j++)
	{
	 	data_rcv[j]= UART0Buffer[i++];
	}
	data_rcv[j]='\0';
	UARTSend( 0, (uint8_t *)data_rcv, sizeof(data_rcv) );

	if((tp_strcmp((uint8_t *)data_rcv,"START:1")) == 0)
			{
		//		UARTSend( 0, "Data Received", 13 );
				return 1;
			}
		else if((tp_strcmp((uint8_t *)data_rcv,"START:2")) == 0)
			{
			 	return 2;
			}
			else
				{
					return 3;
				}
  }

}
void delay_ms(int a){
	int i,j;
	for(i = 0 ; i < a ; i++ )
	{
		for(j = 0 ; j < 10000 ; j++ ) ;
	}
	return ;
}

/*****************************************************************************
**                            End Of File
*****************************************************************************/
