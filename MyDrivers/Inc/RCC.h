#ifndef INC_RCC_H_
#define INC_RCC_H_
#include "STM32F407xx.h"

// ****** RCC PERIPHERALS ENABLE CLOCK HATLARI MAKRO TANIMLAMALARI ******

//GPIOA için geçici değişken ile bit aktif edilir ve süre geçmesi için bit okuması yapılır.
#define RCC_GPIOA_CLK_ENABLE() 					do{	uint32_t tempValue = 0;	\
														SET_BIT(RCC->AHB1ENR , RCC_AHB1ENR_GPIOAEN);	\
														tempValue = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);	\
														UNUSED(tempValue);	\
												}while(0)

//GPIOB için geçici değişken ile bit aktif edilir ve süre geçmesi için bit okuması yapılır.

#define RCC_GPIOB_CLK_ENABLE()					do{	uint32_t tempValue = 0;	\
														SET_BIT(RCC->AHB1ENR ,RCC_AHB1ENR_GPIOBEN);	\
														tempValue = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);	\
														UNUSED(tempValue);	\
												}while(0)

//GPIOC için geçici değişken ile bit aktif edilir ve süre geçmesi için bit okuması yapılır.
#define RCC_GPIOC_CLK_ENABLE()					do{	uint32_t tempValue = 0;	\
														SET_BIT(RCC->AHB1ENR ,RCC_AHB1ENR_GPIOCEN);	\
														tempValue = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);	\
														UNUSED(tempValue);	\
												}while(0)

//GPIOD için geçici değişken ile bit aktif edilir ve süre geçmesi için bit okuması yapılır.
#define RCC_GPIOD_CLK_ENABLE()					do{	uint32_t tempValue = 0;	\
														SET_BIT(RCC->AHB1ENR ,RCC_AHB1ENR_GPIODEN);	\
														tempValue = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);	\
														UNUSED(tempValue);	\
												}while(0)
//GPIOE için geçici değişken ile bit aktif edilir ve süre geçmesi için bit okuması yapılır.
#define RCC_GPIOE_CLK_ENABLE()					do{	uint32_t tempValue = 0;	\
														SET_BIT(RCC->AHB1ENR ,RCC_AHB1ENR_GPIOEEN);	\
														tempValue = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);	\
														UNUSED(tempValue);	\
												}while(0)

// EXTI ÇALIŞMASI İÇİN GEREKEN CLOCK HATTI
#define RCC_SYSCFG_CLK_ENABLE()					do{	uint32_t tempValue = 0;	\
														SET_BIT(RCC->APB2ENR ,RCC_APB2ENR_SYSCFGEN);	\
														tempValue = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);	\
														UNUSED(tempValue);	\
												}while(0)

#define RCC_SPI1_CLK_ENABLE()					do{	uint32_t tempValue = 0;	\
														SET_BIT(RCC->APB2ENR ,RCC_APB2ENR_SPI1EN);	\
														tempValue = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);	\
														UNUSED(tempValue);	\
												}while(0)

#define RCC_SPI2_CLK_ENABLE()					do{	uint32_t tempValue = 0;	\
														SET_BIT(RCC->APB1ENR ,RCC_APB1ENR_SPI2EN);	\
														tempValue = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN);	\
														UNUSED(tempValue);	\
												}while(0)


#define RCC_USART2_CLK_ENABLE()					do{	uint32_t tempValue = 0;	\
														SET_BIT(RCC->AHB1ENR ,RCC_APB1ENR_USART2EN);	\
														tempValue = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);	\
														UNUSED(tempValue);	\
												}while(0)

#define RCC_I2C_CLK_ENABLE()					do{	uint32_t tempValue = 0;	\
														SET_BIT(RCC->AHB1ENR ,RCC_APB1ENR_USART2EN);	\
														tempValue = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);	\
														UNUSED(tempValue);	\
												}while(0)

// ****** RCC PERIPHERALS DISABLE CLOCK HATLARI MAKRO TANIMLAMALARI ******

#define RCC_GPIOA_CLK_DISABLE()					CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
#define RCC_GPIOB_CLK_DISABLE()					CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
#define RCC_GPIOC_CLK_DISABLE()					CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);
#define RCC_GPIOD_CLK_DISABLE()					CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);
#define RCC_GPIOE_CLK_DISABLE()					CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);

#define RCC_SPI1_CLK_DISABLE()					CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);
#define RCC_SPI2_CLK_DISABLE()					CLEAR_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN);

#define RCC_USART2_CLK_DISABLE()				CLEAR_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);
#define RCC_I2C_CLK_DISABLE()					CLEAR_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);


uint32_t RCC_GetSystemClock(void); // HANGİ CLOCK KULLANILDIĞINI GÖRÜR.
uint32_t RCC_GetHClock(void);  //
uint32_t RCC_GetPClock1(void);
uint32_t RCC_GetPClock2(void);









#endif /* INC_RCC_H_ */
