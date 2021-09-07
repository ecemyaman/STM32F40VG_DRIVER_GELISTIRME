#include <stdint.h>
#include "STM32F407xx.h"
#include "GPIO.h"
#include "EXTI.h"

static void LockControl();
static void GPIO_LedConfig();
static void GPIO_ButtonInterruptConfig();
static void SPI_Config();
static void SPI_GPIO_Config();
static void GPIO_Config(void);
static void UART_Config(void);

SPI_HandleTypeDef_t SPI_Handle;


int main(void)
{
GPIO_LedConfig();
//GPIO_LockPin(GPIOA, GPIO_PIN_0);
//LockControl();
GPIO_ButtonInterruptConfig();
SPI_GPIO_Config();
SPI_Config();


void EXTI0_IRQHandler()  //EXTI0 LINE INTERRUPT
{
	char messageToSend = "HELLO WORD\n";
	if(EXTI->PR & 0x1) //pending register 1 ile AND işlemine tabi tutulduğunda orada veri var ise interrupt gelmiştir.
	{
		//CLEAR İŞLEMİ
		EXTI->PR |= (0x1U <<0U); // İnterrupt pin0'dan geldiği için 0 bit kaydırarak 1 yazılır. Pin5 ten gelse 5 bit kaydırılırdı.
		//LED YAKMA
		GPIO_WritePin(GPIOD,GPIO_PIN_ALL,GPIO_Pin_Set);
		//ISR FONKSİYONLAR HANDLER MODDA ÇALIŞIR.

		SPI_TransmitData_IT(&SPI_Handle, (uint8_t*)messageToSend, strlen(messageToSend));
	}
}
	for(;;)
	{

		/*if(GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_Pin_Set)
		{
			GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_Pin_Set);
		}
		else
		{
			GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_Pin_Reset);
		}*/
	}
}

static void GPIO_LedConfig()
{
	GPIO_InitTypeDef_t GPIO_InitStruct = { 0 };
	RCC_GPIOA_CLK_ENABLE();
	RCC_GPIOD_CLK_ENABLE();
	RCC_SYSCFG_CLK_ENABLE();


	GPIO_InitStruct.pinNumber = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	GPIO_InitStruct.Otype = GPIO_OTYPE_PP;
	GPIO_InitStruct.PuPd = GPIO_PUPD_NOPULL;

	GPIO_Init(GPIOD, &GPIO_InitStruct);
	memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));

	GPIO_InitStruct.pinNumber = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.PuPd = GPIO_PUPD_PULLDOWN;

	GPIO_Init(GPIOA, &GPIO_InitStruct);


	EXTI_LineConfig(EXTI_PortSource_GPIOC, EXTI_LineSource_7);
}
static void LockControl()
{
	GPIO_InitTypeDef_t GPIO_InitStruct = { 0 };
	GPIO_InitStruct.pinNumber = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT;
	GPIO_InitStruct.PuPd = GPIO_PUPD_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
static void GPIO_ButtonInterruptConfig()
{
	RCC_GPIOA_CLK_ENABLE();
	EXTI_InitTypeDef_t EXTI_InitStruct = {0};
	RCC_SYSCFG_CLK_ENABLE();
	EXTI_LineConfig(EXTI_PortSource_GPIOA, EXTI_LineSource_0);
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_LineNumber = EXTI_LineSource_0;
	EXTI_InitStruct.EXTI_Mode = EXTI_MODE_Interrupt;
	EXTI_InitStruct.TriggerSelection = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
	NVIC_EnableInterrupt(EXTI0_IRQNumber);
}

static void SPI_Config()
{
	RCC_SPI1_CLK_ENABLE();
	SPI_HandleTypeDef_t SPI_Handle = {0};
	SPI_Handle.Instance = SPI1; //SPI1'i konfigüre ediyoruz.
	SPI_Handle.Init.BaudRate = SPI_BAUDRATE_DIV8; //2 MHZ
	SPI_Handle.Init.BusConfig = SPI_BUS_FullDublex;
	SPI_Handle.Init.CPHA = SPI_CPHA_FIRST;
	SPI_Handle.Init.CPOL = SPI_CPOL_LOW;
	SPI_Handle.Init.DFF_Format = SPI_DFF_8BITS;
	SPI_Handle.Init.Mode = SPI_MODE_MASTER;
	SPI_Handle.Init.SSM_Cmd = SPI_SSM_ENABLE;

	SPI_Init(&SPI_Handle);
	SPI_PeriphCmd(&SPI_Handle, ENABLE);
	NVIC_EnableInterrupt(SPI1_IRQNumber);
}
static void SPI_GPIO_Config()
{

	GPIO_InitTypeDef_t GPIO_InitStruct = {0};
	GPIO_InitStruct.pinNumber = GPIO_PIN_5 | GPIO_PIN_7; //PA5 SCK - PA7
	GPIO_InitStruct.Mode  = GPIO_MODE_AF;
	GPIO_InitStruct.Otype  = GPIO_OTYPE_PP;
	GPIO_InitStruct.PuPd  = GPIO_PUPD_NOPULL;
	GPIO_InitStruct.Speed  = GPIO_SPEED_VERY;
	GPIO_InitStruct.Alternate = GPIO_AF5;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

}

void SPI1_IRQHandler()
{
	SPI_InterruptHandler(&SPI_Handle);
}









