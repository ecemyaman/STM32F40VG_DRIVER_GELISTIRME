#ifndef INC_EXTI_H_
#define INC_EXTI_H_
#include "STM32F407xx.h"
//EXTI İLE İLGİLİ FONKSİYONLARIN PROTOTİPLERİ BURADA TUTULUR.

//Hattın konfigürasyon işlemleri yapılır.
//Bize port bilgisi ve pin bilgisi gereklidir.


//Portlar makro olarak tanımlanır.
#define EXTI_PortSource_GPIOA			((uint8_t)(0X0))
#define EXTI_PortSource_GPIOB			((uint8_t)(0X1))
#define EXTI_PortSource_GPIOC			((uint8_t)(0X2))
#define EXTI_PortSource_GPIOD			((uint8_t)(0X3))
#define EXTI_PortSource_GPIOE			((uint8_t)(0X4))
#define EXTI_PortSource_GPIOF			((uint8_t)(0X5))
#define EXTI_PortSource_GPIOG			((uint8_t)(0X6))
#define EXTI_PortSource_GPIOH			((uint8_t)(0X7))

//Pinler makro olarak tanımlanır.
#define EXTI_LineSource_0				((uint8_t)(0x0))
#define EXTI_LineSource_1				((uint8_t)(0x1))
#define EXTI_LineSource_2				((uint8_t)(0x2))
#define EXTI_LineSource_3				((uint8_t)(0x3))
#define EXTI_LineSource_4				((uint8_t)(0x4))
#define EXTI_LineSource_5				((uint8_t)(0x5))
#define EXTI_LineSource_6				((uint8_t)(0x6))
#define EXTI_LineSource_7				((uint8_t)(0x7))
#define EXTI_LineSource_8				((uint8_t)(0x8))
#define EXTI_LineSource_9				((uint8_t)(0x9))
#define EXTI_LineSource_10				((uint8_t)(0xA))
#define EXTI_LineSource_11				((uint8_t)(0xB))
#define EXTI_LineSource_12				((uint8_t)(0xC))
#define EXTI_LineSource_13				((uint8_t)(0xD))
#define EXTI_LineSource_14				((uint8_t)(0xE))
#define EXTI_LineSource_15				((uint8_t)(0xF))

#define EXTI_MODE_Interrupt				(0x00U)
#define EXTI_MODE_Event					(0x04U)
#define EXTI_Trigger_Rising				(0x08U)
#define EXTI_Trigger_Falling			(0x0C)
#define EXTI_Trigger_RF					(0x10U)

// Kullanıcıya sunulması configuration struct tanımlaması yapılır.
typedef struct
{
	FunctionalState_t EXTI_LineCmd; // Hattın aktif/pasif olacağı bilgisini tutar
	uint8_t EXTI_LineNumber; // pin numarası bilgisi tutulur.
	uint8_t TriggerSelection; // falling trigger / rising trigger
	uint8_t EXTI_Mode;	//Interrupt mode / event mode

}EXTI_InitTypeDef_t;

void EXTI_Init(EXTI_InitTypeDef_t *EXTI_InitStruct);
void EXTI_LineConfig(uint8_t PortSource, uint8_t EXTI_LineSource);
void NVIC_EnableInterrupt(IRQNumber_TypeDef_t IRQNumber); //240'a kadar giden IRQ numarası barındırır. (32 x 8)
#endif /* INC_EXTI_H_ */
