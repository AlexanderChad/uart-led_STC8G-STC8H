#include	"config.h"
#include	"GPIO.h"
#include	"delay.h"
#include	"UART.h"

void	GPIO_config(void)
{
  GPIO_InitTypeDef	GPIO_InitStructure;
  GPIO_InitStructure.Pin  = GPIO_Pin_2;		//IO
  GPIO_InitStructure.Mode = GPIO_OUT_PP;		//GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
  GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);
}
void	UART_config(void)
{
  COMx_InitDefine		COMx_InitStructure;					//????
  COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//??, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
  COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//????????, BRT_Timer1, BRT_Timer2 (??: ??2????BRT_Timer2)
  COMx_InitStructure.UART_BaudRate  = 115200ul;			//???, ?? 110 ~ 115200
  COMx_InitStructure.UART_RxEnable  = ENABLE;				//????,   ENABLE?DISABLE
  COMx_InitStructure.BaudRateDouble = DISABLE;			//?????, ENABLE?DISABLE
  COMx_InitStructure.UART_Interrupt = ENABLE;				//????,   ENABLE?DISABLE
  COMx_InitStructure.UART_Priority    = Priority_0;			//???????(???) Priority_0,Priority_1,Priority_2,Priority_3
  COMx_InitStructure.UART_P_SW      = UART1_SW_P30_P31;	//????,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
  UART_Configuration(UART1, &COMx_InitStructure);		//?????1 UART1,UART2,UART3,UART4

  PrintString1("STC8H1K08 UART1 Test Program!\r\n");	//UART1???????
}
void main(void)
{
  GPIO_config();
  UART_config();
  EA = 1;
  P1=0;
  while (1)
    {
      delay_ms(1);
      if(COM1.RX_TimeOut > 0)
        {
          if(--COM1.RX_TimeOut == 0)
            {
              if(COM1.RX_Cnt > 0)
                {
                  //for(i=0; i<COM1.RX_Cnt; i++){TX1_write2buff(RX1_Buffer[i]);}
                  switch(RX1_Buffer[0])
                    {
                    case 'q':
                      P1=GPIO_Pin_2;
                      PrintString1("led ON\r\n");
                      break;
                    case 'w':
                      P1=0;
                      PrintString1("led OFF\r\n");
                      break;
                    }
                }
              COM1.RX_Cnt = 0;
            }
        }
    }
}