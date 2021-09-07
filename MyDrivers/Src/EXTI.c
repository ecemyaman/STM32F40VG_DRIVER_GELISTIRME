#include "EXTI.h"

// HANGİ PORTTAN VE HANGİ PİNDEN VERİ GELECEĞİNİ KONFİGÜRE EDİYORUZ.

void EXTI_LineConfig(uint8_t PortSource, uint8_t EXTI_LineSource)
{
	uint32_t tempValue;
	// EXTI_LineSource'un 2 birim kaydırılmasıyla uygun register elde edilmiş olur.
	tempValue = SYSCFG->EXTI_CR[EXTI_LineSource >> 2U];
	// geçici değişkenin 4 bitini uygun bit numarası kadar temizliyoruz.
	tempValue &= (0xFU << (EXTI_LineSource & 0x3U)* 4);
	//veri yazma işlemi
	tempValue = (PortSource << (EXTI_LineSource & 0x3U)* 4);
	//Konfigüre edilen değere atama
	SYSCFG->EXTI_CR[EXTI_LineSource >> 2U] = tempValue;
}

void EXTI_Init(EXTI_InitTypeDef_t *EXTI_InitStruct)
{
	uint32_t tempValue =0;
	tempValue = (uint32_t)EXTI_BASE_ADDR; //geçici değişken EXTI base adresini tutar.
	EXTI->IMR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber); // IMR'deki veriyi temizledik
	EXTI->EMR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber); // EMR'deki veriyi temizledik.
	if(EXTI_InitStruct->EXTI_LineCmd != DISABLE)
	{
		tempValue += EXTI_InitStruct->EXTI_Mode; //geçici değişkene mode bilgisi eklendi
		*((__IO uint32_t*)tempValue) |= (0x1U << EXTI_InitStruct->EXTI_LineNumber); // veri yazma işlemi yapıldı.
		tempValue = (uint32_t)EXTI_BASE_ADDR; // temp değeri değişti yeniden eski haline getirilir
		EXTI->RTSR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber); // RTSR üzerinde clear işlemi yapıldı
		EXTI->FTSR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber); // FTSR üzerinde clear işlemi yapıldı
		if(EXTI_InitStruct->TriggerSelection == EXTI_Trigger_RF) //iki durumunda aktif olması isteniyorsa
		{
			EXTI->RTSR |= (0x1U << EXTI_InitStruct->EXTI_LineNumber);
			EXTI->FTSR |= (0x1U << EXTI_InitStruct->EXTI_LineNumber);
		}
		else
		{
			tempValue += EXTI_InitStruct->TriggerSelection;
			*((__IO uint32_t*)tempValue) |= (0x1U << EXTI_InitStruct->EXTI_LineNumber);
		}
	}
	else
	{
		tempValue = (uint32_t)EXTI_BASE_ADDR;
		tempValue += EXTI_InitStruct->EXTI_Mode;
		*((__IO uint32_t*)tempValue) &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);
	}
}

//NVIC KONFİGÜRASYONLARI BURADA YAPILIR
void NVIC_EnableInterrupt(IRQNumber_TypeDef_t IRQNumber){ //register okuma işlemi yapılır. Okuma işleminden sonra veri yazılır
	uint32_t tempValue = 0;
	tempValue = *((IRQNumber >> 5U) + NVIC_ISER0); //registerden veriyi IRQ numarasına göre çektik.
	tempValue &= ~(0x1U << (IRQNumber & 0x1FU)); // IRQ numarasına göre uygun bit numarasını bulup clear işlemi yapıldı.
	tempValue |= (0x1U << (IRQNumber & 0x1FU)); // uygun bite 1 yazdık
	*((IRQNumber >> 5U)+ NVIC_ISER0) = tempValue; // okunan veriyi tempValue'ya atadık
}








