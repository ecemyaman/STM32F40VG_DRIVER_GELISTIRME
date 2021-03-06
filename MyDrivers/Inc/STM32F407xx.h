#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_
#include <stdint.h> //veri tiplerini int olarak kullanabilmeyi sağlar.
#include <string.h>
#include <stddef.h>


// MİKRO İŞLEMCİ İLE İLGİLİ KISIM
#define NVIC_ISER0			((uint32_t*)(0xE000E100)) // Bir adresi 1 arttırırsak normalde 1 byte ilerler fakat ISER0 4 Byte ilerler. Pointer gibi davranır çünkü davrandığı pointer 4 byte yer kaplar.

// MCU ÜZERİNDEKİ IRQ NUMARALARI == VECTOR TABLE
typedef enum
{
	EXTI0_IRQNumber = 6,
	EXTI1_IRQNumber = 7,
	EXTI2_IRQNumber = 8,
	EXTI3_IRQNumber = 9,
	SPI1_IRQNumber = 35
}IRQNumber_TypeDef_t;

#define __IO volatile
// HEADER FILE ALANINI YAZARKEN MİKRODENETLEYİCİNİN REFERANS MANUAL'İ KULLANILIR.

#define SET_BIT(REG,BIT)	((REG) |= (BIT)) //ilgili registerdaki biti değiştirmek
#define CLEAR_BIT(REG,BIT)	((REG) &= ~(BIT)) //İlgili registerdaki biti temizlemek
#define READ_BIT(REG,BIT)	((REG) & (BIT))	//ilgili registerdaki biti okumak
#define UNUSED(x) 			((void)(x))

// LINE'A BAĞLI BİR ENUM YAPISI OLUŞTURULUR.

typedef enum
{
	DISABLE = 0x0U,
	ENABLE = !DISABLE
}FunctionalState_t;

/*
 * MEMORY BASE ADRESLERİ TANIMLAMA
 */
//1MB FLASH HAFIZASI TANIMLADIK
//Compile öncesi çalışan komutlardır. uint yerine UL yazılsa da olurdu.
#define FLASH_BASE_ADDR					((uint32)(0x08000000)) //referance manuel'den aldık.

// SRAM TANIMLAMA (DEĞİŞKENLERİN TUTULACAĞI YER)
#define SRAM1_BASE_ADDR							(0x20000000UL) //112 KB'LIK SRAM1
#define SRAM2_BASE_ADDR							(0x2001C000UL) //16 KB'LIK SRAM2

/*
 * ÇEVRESEL BİRİMLERİN ADRESLERİNİN TANIMLAMA (veri hatlarına bağlı kısımlar)
 */
#define PERIPH_BASE_ADDR						 (0x40000000UL) 	  //tüm çevresel birimleriin başladığı base adres
#define APB1_BASE_ADDR							 PERIPH_BASE_ADDR  //APB1 ÇEVRESEL BİRİMİ BU ADRESTEN BAŞLAR.
#define APB2_BASE_ADDR							(PERIPH_BASE_ADDR + 0x00010000UL)     // APB2 40001 ile başlıyordu tanımlama bu şekilde üzerinde eklenerek yapıldı.
#define AHB1_BASE_ADDR							(PERIPH_BASE_ADDR + 0x00020000UL )   //AHB1 4002 ile başlıyordu
#define AHB2_BASE_ADDR							(PERIPH_BASE_ADDR + 0x10000000UL) 	//AHB2 5000 ile başlıyor

/*
 * APB1'IN ÇEVRESEL BİRİMLERİ EKLENİR + OFFSET EKLENİR
 */
#define TIM2_BASE_ADDR 							(APB1_BASE_ADDR + 0x0000UL)
#define TIM3_BASE_ADDR							(APB1_BASE_ADDR + 0x0400UL) //time3 base 4000 0400 olduğu için ekleme yapıldı.
#define TIM4_BASE_ADDR							(APB1_BASE_ADDR + 0x0800UL) //time4 0800
//#define TIM5_BASE_ADDR
//#define TIM6_BASE_ADDR
//#define TIM7_BASE_ADDR

#define SPI2_BASE_ADDR							(APB1_BASE_ADDR + 0x3800UL) //spi2 3800
#define SPI3_BASE_ADDR							(APB1_BASE_ADDR + 0x3C00UL) //spi3 3C00

//SERİ HABERLEŞME BİRİMİ --> USART
#define USART2_BASE_ADDR						(APB1_BASE_ADDR + 0x4400UL)
#define USART3_BASE_ADDR						(APB1_BASE_ADDR + 0x4800UL)

//UART SENKRON (CLOCK CYCLE) BİR ŞEKİLDE HABERLEŞMEYİ SAĞLAR.
#define UART4_BASE_ADDR							(APB1_BASE_ADDR + 0x4C00UL)
#define UART5_BASE_ADDR							(APB1_BASE_ADDR + 0x5000UL)

#define I2C1_BASE_ADDR							(APB1_BASE_ADDR + 0x5400UL)
#define I2C2_BASE_ADDR							(APB1_BASE_ADDR + 0x5800UL)
#define I2C3_BASE_ADDR							(APB1_BASE_ADDR + 0x5C00UL)


/*
 * APB2 ÇEVRESEL BİRİMLER TANIMLANIR.
 */
#define TIM1_BASE_ADDR							(APB2_BASE_ADDR + 0x0000UL)
#define TIM8_BASE_ADDR							(APB2_BASE_ADDR + 0x0400UL)

#define USART1_BASE_ADDR						(APB2_BASE_ADDR + 0x1000UL)
#define USART6_BASE_ADDR						(APB2_BASE_ADDR + 0x1400UL)

#define SPI1_BASE_ADDR							(APB2_BASE_ADDR + 0x3000UL)
#define SPI4_BASE_ADDR							(APB2_BASE_ADDR + 0x3400UL)

//Sistem konfigürasyonları ve External Interrupt registerları   -----> INTERRUPT'ta lazım.
#define SYSCFG_BASE_ADDR						(APB2_BASE_ADDR + 0x3800UL)
#define EXTI_BASE_ADDR							(APB2_BASE_ADDR + 0x3C00UL)

/*
 * AHB1 ÇEVRESEL BİRİMLERİN TANIMLANMASI
 */
#define GPIOA_BASE_ADDR							(AHB1_BASE_ADDR + 0x0000UL)
#define GPIOB_BASE_ADDR							(AHB1_BASE_ADDR + 0x0400UL)
#define GPIOC_BASE_ADDR							(AHB1_BASE_ADDR + 0x0800UL)
#define GPIOD_BASE_ADDR							(AHB1_BASE_ADDR + 0x0C00UL)
#define GPIOE_BASE_ADDR							(AHB1_BASE_ADDR + 0x1000UL)

#define RCC_BASE_ADDR							(AHB1_BASE_ADDR + 0x3800UL)


//GPIOA REGISTERLARININ STRUCT'LARI
typedef struct
{
	//32 bitlik registerlar tek tek tanımlanır bu sayede uygun registerlara ulaşılabilecek
	//TÜM ÇEVRESEL BİRİMLERİN REGİSTERLARI VOLATILE OLARAK TANIMLANMAK ZORUNDA. VOLATILE DEMEK OPTİMİZE ETME DEMEK. BEKLENMEDİK BİR ANDA DEĞER DEĞİŞEBİLİR DEMEK
	//ARKA PLANDA KOD DERLENİRKEN DEĞERİ 1 KERE OKUR, OKUNAN DEĞER NE İSE O ŞEKİLDE İŞLENİR BU DA HATADIR.
	//VOLATILE YAZILMAZSA OPTİMİZASYON SIRASINDA KOD DOĞRU ÇALIŞMAZ ANCAK HATA DA VERMEZ.
	// VOLATILE YERİNE IO DA YAZILABİLİR.

	__IO uint32_t MODER;		//GPIO MODE REGİSTER, 						ADRES OFFSET 0x0000
	__IO uint32_t OTYPER;		//GPIO OUTPUT TYPE REGISTER, 				ADRES OFFSET 0x0004
	__IO uint32_t OSPEEDR;		//GPIO OUTPUT SPEED REGISTER, 				ADRES OFFSET 0x0008
	__IO uint32_t PUPDR;		//GPIO PULL UP/PULL DOWN REGISTER, 			ADRES OFFSET 0x000C
	__IO uint32_t IDR;			//GPIO INPUT DATA REGISTER, 				ADRES OFSET 0x0010
	__IO uint32_t ODR;			//GPIO OUTPUT REGISTER, 					ADRES OFSET 0x0014
	__IO uint32_t LCKR;			//GPIO CONFIGURATION LOCK REGISTER, 		ADRES OFSET 0x0001C
	__IO uint32_t BSRR;			//GPIO BIT SET/RESET REGISTER, 				ADRES OFFSET 0x0018
	__IO uint32_t AFR[2];		//GPIO ALTENATE FUNCTION LOW&HIGH REGISTER, ADRES OFFSET 0x0020

}GPIO_TypeDef_t;

//RCC REGISTERLARIN STRUCTLARI
typedef struct{

	__IO uint32_t CR;			// RCC CLOCK CONTROL REGISTER									ADRES OFFSET= 0x0000
	__IO uint32_t PLLCFGR;		// RCC PLL CONFIGURATION REGISTER								ADRES OFFET = 0X0004
	__IO uint32_t CFGR;			// RCC CLOCK CONFIGURATION REGISTER 							ADRES OFFET = 0X0008
	__IO uint32_t CIR;			// RCC CLOCK INTERRUPT REGISTER 								ADRES OFFET = 0X000C
	__IO uint32_t AHB1RSTR;		// RCC AHB1 PERIPHERAL RESET REGISTER 							ADRES OFFET = 0X0010
	__IO uint32_t AHB2RSTR;		// RCC AHB2 PERIPHERAL RESET REGISTER 							ADRES OFFET = 0X0014
	__IO uint32_t AHB3RSTR;		// RCC AHB3 PERIPHERAL RESET REGISTER 							ADRES OFFET = 0X0018
	__IO uint32_t RESERVED0;	// RESERVED AREA												ADRES OFFET = 0X001C
	__IO uint32_t APB1RSTR;		// RCC APB1 PERIPHERAL RESET REGISTER 							ADRES OFFET = 0X0020
	__IO uint32_t APB2RSTR;		// RCC APB2 PERIPHERAL RESET REGISTER 							ADRES OFFET = 0X0024
	__IO uint32_t RESERVED1[2];	// RESERVED AREA					 							ADRES OFFET = 0X0028
	__IO uint32_t AHB1ENR;		// RCC AHB1 PERIPHERAL CLOCK ENABLE REGISTER 					ADRES OFFET = 0X0030
	__IO uint32_t AHB2ENR;		// RCC AHB2 PERIPHERAL CLOCK ENABLE REGISTER 					ADRES OFFET = 0X0034
	__IO uint32_t AHB3ENR;		// RCC AHB3 PERIPHERAL CLOCK ENABLE REGISTER 					ADRES OFFET = 0X0038
	__IO uint32_t RESERVED2;	// RESERVED AREA												ADRES OFFET = 0X003C
	__IO uint32_t APB1ENR;		// RCC APB1 PERIPHERAL CLOCK ENABLE REGISTER 					ADRES OFFET = 0X0040
	__IO uint32_t APB2ENR;		// RCC APB2 PERIPHERAL CLOCK ENABLE REGISTER 					ADRES OFFET = 0X0044
	__IO uint32_t RESERVED3[2];	// RESERVED AREA							 					ADRES OFFET = 0X0048
	__IO uint32_t AHB1LPENR;	// RCC AHB1 PERIPHERAL CLOCK ENABLE IN LOW POWER MODE REGISTER 	ADRES OFFET = 0X0050
	__IO uint32_t AHB2LPENR;	// RCC AHB2 PERIPHERAL CLOCK ENABLE IN LOW POWER MODE REGISTER 	ADRES OFFET = 0X0054
	__IO uint32_t AHB3LPENR;	// RCC AHB3 PERIPHERAL CLOCK ENABLE IN LOW POWER MODE REGISTER 	ADRES OFFET = 0X0058
	__IO uint32_t RESERVED4;	// RESERVED AREA 												ADRES OFFET = 0X005C
	__IO uint32_t APB1LPENR;	// RCC APB1 PERIPHERAL CLOCK ENABLE IN LOW POWER MODE REGISTER 	ADRES OFFET = 0X0060
	__IO uint32_t APB2LPENR;	// RCC APB2 PERIPHERAL CLOCK ENABLE IN LOW POWER MODE REGISTER 	ADRES OFFET = 0X0064
	__IO uint32_t RESERVED5[2]; // RESERVED AREA 												ADRES OFFET = 0X0068
	__IO uint32_t BDCR;			// RCC BACKUP DOMAIN CONTROL REGISTER 							ADRES OFFET = 0X0070
	__IO uint32_t CSR;			// RCC CLOCK CONTROL & STATUS REGISTER 							ADRES OFFET = 0X0074
	__IO uint32_t RESERVED6[2];	// RESERVED AREA 												ADRES OFFET = 0X0078
	__IO uint32_t SSCGR;		// RCC SPREAD SPECTRUM CLOCK GENERATION REGISTER 				ADRES OFFET = 0X0080
	__IO uint32_t PLLI2SCFGR;	// RCC PLLI2S CONFIFURATION REGISTER 							ADRES OFFET = 0X0084


}RCC_TypeDef_t;

//SYSTEM CONFIGURATION REGISTER STRUCTLARI
typedef struct
{
	__IO uint32_t MEMRMP;			//SYSCFG MEMORY REMAP REGISTER						ADDRESS OFFSET = 0x00
	__IO uint32_t PMC;				//SYSCFG PERIPHERAL MODE CONFIGURATION REGISTER		ADDRESS OFFSET = 0x04
	__IO uint32_t EXTI_CR[4];		//SYSCFG EXTERNAL INTERRUPT CONFIGURATION REGISTER	ADDRESS OFFSET = 0x08
	__IO uint32_t CMPCR;			//SYSCFG COMPENSATION CELL CONTROL REGISTER			ADDRESS OFFSET = 0x20

}SYSCFG_TypeDef_t;

// EXTI REGISTERLARI STRUCT YAPILARI
typedef struct
{
	__IO uint32_t IMR;		// INTERRUPT MASK REGISTER 				ADDRESS OFFSET = 0x00
	__IO uint32_t EMR;		// EVENT MASK REGISTER					ADDRESS OFFSET = 0x04
	__IO uint32_t RTSR;		// RISING TRIGGER SELECTION REGISTER	ADDRESS OFFSET = 0x08
	__IO uint32_t FTSR;		// FALLING TRIGGER SELECTION REGISTER	ADDRESS OFFSET = 0x0C
	__IO uint32_t SWIER;	// SOFTWARE INTERRUPT EVENT REGISTER	ADDRESS OFFSET = 0x10
	__IO uint32_t PR;		// PENDING REGISTER						ADDRESS OFFSET = 0x14

}EXTI_TypeDef_t;

//SPI REGISTERLARI STRUCT YAPILARI
typedef struct
{
	__IO uint32_t CR1;		//SPI CONTROL REGISTER					ADDRESS OFFSET = 0x00
	__IO uint32_t CR2;		//SPI CONTROL REGISTER 2				ADDRESS OFFSET = 0x04
	__IO uint32_t SR;		//SPI STATUS REGISTER					ADDRESS OFFSET = 0x08
	__IO uint32_t DR;		//SPI DATA REGISTER						ADDRESS OFFSET = 0x0C
	__IO uint32_t CRCPR;	//SPI CRC POLYNOMİAL REGISTER			ADDRESS OFFSET = 0x10
	__IO uint32_t RXCRCR;	//SPI RX CRC RGISTER					ADDRESS OFFSET = 0x14
	__IO uint32_t TXCRCR;	//SPI TX CRC REGISTER					ADDRESS OFFSET = 0x18
	__IO uint32_t I2SCFGR;	//SPI_I2S CONFIGURATION REGISTER		ADDRESS OFFSET = 0x1C
	__IO uint32_t I2SPR;	//SPI_I2S PRESCALER REGISTER			ADDRESS OFFSET = 0x20

}SPI_TypeDef_t;

//USART REGISTERLARI STRUCT YAPILARI

typedef struct
{
	__IO uint32_t SR;		// USART STATUS REGISTER						ADDRESS OFFSET = 0x00
	__IO uint32_t DR;		// USART DATA REGISTER							ADDRESS OFFSET = 0x04
	__IO uint32_t BRR;		// USART BAUND RATE REGISTER					ADDRESS OFFSET = 0x08
	__IO uint32_t CR1;		// USART CONTROL REGISTER 1						ADDRESS OFFSET = 0x0C
	__IO uint32_t CR2;		// USART CONTROL REGISTER 2						ADDRESS OFFSET = 0x10
	__IO uint32_t CR3;		// USART CONTROL REGISTER 3						ADDRESS OFFSET = 0x14
	__IO uint32_t GTPR;		// USART GUARD TIME AND PRESCALER REGISTER		ADDRESS OFFSET = 0x18

}USART_TypeDef_t;

// I2C REGISTERLARI
typedef struct
{
		__IO uint32_t CR1;		// I2C CONTROL REGISTER 1					ADDRESS OFFSET = 0x00
		__IO uint32_t CR2;		// I2C CONTROL REGISTER 2					ADDRESS OFFSET = 0x04
		__IO uint32_t OAR1;		// I2C OWN ADDRESS REGISTER					ADDRESS OFFSET = 0x08
		__IO uint32_t OAR2;		// I2C OWN ADDRESS REGISTER					ADDRESS OFFSET = 0x0C
		__IO uint32_t DR;		// I2C DATA REGISTER						ADDRESS OFFSET = 0X10
		__IO uint32_t SR1;		// I2C STATUS REGISTER	1					ADDRESS OFFSET = 0X14
		__IO uint32_t SR2;		// I2C STATUS REGISTER	2					ADDRESS OFFSET = 0X18
		__IO uint32_t CCR;		// I2C CLOCK CONTROL REGISTER				ADDRESS OFFSET = 0X1C
		__IO uint32_t TRISE;	// I2C TRISE REGISTER						ADDRESS OFFSET = 0X20
		__IO uint32_t FLTR;		// I2C FLTR REGISTER						ADDRESS OFFSET = 0X24

}I2C_TypeDef_t;
//GPIOA'nın adresi sayesinde struct pointer yapısıyla register üzerinde ilerleyebiliriz.
#define GPIOA 									((GPIO_TypeDef_t *)(GPIOA_BASE_ADDR))
#define GPIOB									((GPIO_TypeDef_t *)(GPIOB_BASE_ADDR))
#define GPIOC 									((GPIO_TypeDef_t *)(GPIOC_BASE_ADDR))
#define GPIOD									((GPIO_TypeDef_t *)(GPIOD_BASE_ADDR))
#define GPIOE 									((GPIO_TypeDef_t *)(GPIOE_BASE_ADDR))

//RCC MAKROSU ÜZERİNDEN REGISTERLARA ULAŞMAK İÇİN;
#define RCC										((RCC_TypeDef_t*)(RCC_BASE_ADDR))

// ***** BIT DEFINITIONS *****

// SYSCONFIG UZERINDEN REGISTERLARA ULAŞMAK İÇİN;
#define SYSCFG 									((SYSCFG_TypeDef_t*)(SYSCFG_BASE_ADDR))

// EXTI UZERINDEN REGISTERLARA ULAŞMAK İÇİN;
#define EXTI									((EXTI_TypeDef_t*)(EXTI_BASE_ADDR))

// SPI REGISTERLARINA ULAŞMAK İÇİN;
#define SPI1									((SPI_TypeDef_t*)(SPI1_BASE_ADDR))
#define SPI2									((SPI_TypeDef_t*)(SPI2_BASE_ADDR))
#define SPI3									((SPI_TypeDef_t*)(SPI3_BASE_ADDR))
#define SPI4									((SPI_TypeDef_t*)(SPI4_BASE_ADDR))

// USART REGISTERLARINA ULAŞMAK İÇİN;
#define USART2									((USART_TypeDef_t*)(USART2_BASE_ADDR))
#define USART3									((USART_TypeDef_t*)(USART3_BASE_ADDR))
#define UART4									((USART_TypeDef_t*)(UART4_BASE_ADDR))
#define UART5									((USART_TypeDef_t*)(UART5_BASE_ADDR))

#define USART1									((USART_TypeDef_t*)(USART1_BASE_ADDR))
#define USART6									((USART_TypeDef_t*)(USART6_BASE_ADDR))

//IC REGISTERLARINA ULAŞMAK İÇİN;
#define I2C1									(I2C_TypeDef_t*)(I2C1_BASE_ADDR)
#define I2C2									(I2C_TypeDef_t*)(I2C2_BASE_ADDR)
#define I2C3									(I2C_TypeDef_t*)(I2C3_BASE_ADDR)

//A portunun 0. bitini aktif etmek için makro tanımlanır.
#define RCC_AHB1ENR_GPIOAEN_POS			(0U)								//RCC'nin AHB1 enable registerındaki bit 0
#define RCC_AHB1ENR_GPIOAEN_MSK			(0X1 << RCC_AHB1ENR_GPIOAEN_POS)	// 0x1'i yukarıdaki bit kadar sola kaydırarak yaz. Bit maskeleme
#define RCC_AHB1ENR_GPIOAEN				RCC_AHB1ENR_GPIOAEN_MSK				// Enable Makro

#include "RCC.h" // Bu eklenmezse her mainin altına gelip (#include "") şekilde tanımlama yapılması gerekir.

// B portunun 0. bitini aktif etmek için makro tanımlanır.

#define RCC_AHB1ENR_GPIOBEN_POS			(1U)
#define RCC_AHB1ENR_GPIOBEN_MSK			(0X1 << RCC_AHB1ENR_GPIOBEN_POS)
#define RCC_AHB1ENR_GPIOBEN				RCC_AHB1ENR_GPIOBEN_MSK

// C portunun 0. bitini aktif etmek için makro tanımlanır.

#define RCC_AHB1ENR_GPIOCEN_POS			(2U)
#define RCC_AHB1ENR_GPIOCEN_MSK			(0X1 << RCC_AHB1ENR_GPIOCEN_POS)
#define RCC_AHB1ENR_GPIOCEN				RCC_AHB1ENR_GPIOCEN_MSK

// D portunun 0. bitini aktif etmek için makro tanımlanır.

#define RCC_AHB1ENR_GPIODEN_POS			(3U)
#define RCC_AHB1ENR_GPIODEN_MSK			(0X1 << RCC_AHB1ENR_GPIODEN_POS)
#define RCC_AHB1ENR_GPIODEN				RCC_AHB1ENR_GPIODEN_MSK

// E portunun 0. bitini aktif etmek için makro tanımlanır.

#define RCC_AHB1ENR_GPIOEEN_POS			(4U)
#define RCC_AHB1ENR_GPIOEEN_MSK			(0X1 << RCC_AHB1ENR_GPIOEEN_POS)
#define RCC_AHB1ENR_GPIOEEN				RCC_AHB1ENR_GPIOEEN_MSK

#include "EXTI.h"

#define RCC_APB2ENR_SYSCFGEN_Pos		(14U)
#define RCC_APB2ENR_SYSCFGEN_Msk		(0x1U << RCC_APB2ENR_SYSCFGEN_Pos)
#define RCC_APB2ENR_SYSCFGEN			RCC_APB2ENR_SYSCFGEN_Msk

#define RCC_APB2ENR_SPI1_Pos			(12U)
#define RCC_APB2ENR_SPI1EN_Msk			(0x1U << RCC_APB2ENR_SPI1_Pos)
#define RCC_APB2ENR_SPI1EN				RCC_APB2ENR_SPI1EN_Msk

#define RCC_APB1ENR_SPI2_Pos			(14U)
#define RCC_APB1ENR_SPI2EN_Msk			(0x1U << RCC_APB1ENR_SPI2_Pos)
#define RCC_APB1ENR_SPI2EN				RCC_APB2ENR_SPI2EN_Msk

#include "SPI.h"
#define SPI_CR1_SPE						(6U)
#define SPI_SR_TxE						(1U)
#define SPI_SR_Busy						(7U)
#define SPI_SR_RxNE						(0U)
#define SPI_CR2_TXEIE					(7U)
#define SPI_CR1_DFF						(11U)
#define USART_SR_RxNE					(5U)

//FLAG DEFINITION
#define	SPI_TxE_FLAG					(0x1U << SPI_SR_TxE)
#define	SPI_Busy_FLAG					(0x1U << SPI_SR_Busy)


#include "USART.h"

#define RCC_APB1ENR_USART2EN_POS		(17U)
#define	RCC_APB1ENR_USART2EN_Msk		(0x1U << RCC_APB1ENR_USART2EN_Pos)
#define RCC_APB1ENR_USART2EN			RCC_APB1ENR_USART2EN_Msk

#define USART_CR1_UE					(13U)
#define UART_CR2_STOP					(12U)
#define USART_SR_TxE					(7U)
#define USART_CR1_TxEIE					(7U)
#define USART_CR1_RxNEIE				(5U)
#define USART_SR_TC						(6U)
#define USART_TxE_FLAG					(0x1U << USART_SR_TxE)
#define USART_TC_FLAG					(0x1U << USART_SR_TC)
#define USART_RxNE_FLAG					(0X1U << USART_SR_RxNE)

#include "I2C.h"
#define RCC_APB1ENR_I2C1EN_Pos			(21U)
#define RCC_APB1ENR_I2C1EN_Msk			(0X1U << RCC_APB1ENR_I2C1EN_Pos)
#define RCC_APB1ENR_I2C1EN				(RCC_APB1ENR_I2C1EN_Msk)


#endif /* INC_STM32F407XX_H_ */

