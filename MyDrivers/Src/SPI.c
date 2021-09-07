#include "SPI.h"

static void SPI_CloseISR_TX(SPI_HandleTypeDef_t *SPI_Handle)
{
	SPI_Handle->Instance->CR2 &= ~(0x1U << SPI_CR2_TXEIE);
	SPI_Handle->TxDataSize = 0;
	SPI_Handle->pTxDataAddr = NULL;
	SPI_Handle->busStateTx = SPI_BUS_FREE;
}
//16 BİTE GÖRE VERİ GÖNDERİLİR
static void SPI_TransmitHelper_16Bits(SPI_HandleTypeDef_t *SPI_Handle)
{
	SPI_Handle->Instance->DR = *((uint16_t*)(SPI_Handle->pTxDataAddr)); // VERİ YÜKLEME İŞLEMİ
	SPI_Handle->pTxDataAddr += sizeof(uint16_t); // 2BYTE OLARAK VERİ YÜKLENİR
	SPI_Handle->TxDataSize -= 2;
}
// 8 BİTE GÖRE VERİ GÖNDERİLİR.
static void SPI_TransmitHelper_8Bits(SPI_HandleTypeDef_t *SPI_Handle)
{
	SPI_Handle->Instance->DR = *((uint8_t*)(SPI_Handle->pTxDataAddr));
	SPI_Handle->pTxDataAddr += sizeof(uint8_t);
	SPI_Handle->TxDataSize --;
	if(SPI_Handle->TxDataSize ==0)
	{
		SPI_CloseISR_TX(SPI_Handle);
	}
}

void SPI_Init(SPI_HandleTypeDef_t *SPI_Handle)
{
	uint32_t tempValue = 0;
	tempValue = SPI_Handle->Instance->CR1; //CR1 registerı handle'dan çekildi ve geçici değişkene atandı.
	tempValue |= (SPI_Handle->Init.BaudRate) | (SPI_Handle->Init.CPHA) | (SPI_Handle->Init.DFF_Format)
			| (SPI_Handle->Init.Mode) | (SPI_Handle->Init.FrameFormat) | (SPI_Handle->Init.BusConfig) | (SPI_Handle->Init.SSM_Cmd);
	SPI_Handle->Instance->CR1 = tempValue;
}

void SPI_PeriphCmd(SPI_HandleTypeDef_t *SPI_Handle, FunctionalState_t stateOfSPI)
{
	if(stateOfSPI == ENABLE)
	{
		SPI_Handle->Instance->CR1 |= (0x1U << SPI_CR1_SPE);
	}
	else
	{
		SPI_Handle->Instance->CR1 &= ~(0x1U << SPI_CR1_SPE);
	}
}

void SPI_TransmitData(SPI_HandleTypeDef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData)
{
	if(SPI_Handle->Init.DFF_Format == SPI_DFF_16BITS) // DFF FORMAT 16 BİT İSE
	{
		while(sizeOfData > 0)	// HALA YAZILACAK VERİ VARDIR
		{
			if(SPI_GetFlagStatus(SPI_Handle, SPI_TxE_FLAG)) //VERİ YAZMA TXE FLAG'E GÖRE YAZILIR.
					{
						SPI_Handle->Instance->DR = *((uint16_t*)pData);	// DR registerına ulaşıldı ve uint16 olduğu için 2 byte şekilde yazıldı.
						pData += sizeof(uint16_t); //pDATA 2 byte'lık bir artış göstermelidir
						sizeOfData -= 2; // her defasında 2 azaltılır. Fazladan veri gönderilmesini önlen,r.
					}
		}
	}
	else // 16 BİT DEĞİLSE 8 BİTTİR
	{
		while(sizeOfData > 0)
		{
			if((SPI_Handle->Instance->SR >> 1U) & 0x1U)
			{
				SPI_Handle->Instance->DR = *pData; //pDATA ilk yazılacak mesajın adresini gösterir. İlk byte yazıldı.
				pData += sizeof(uint8_t);
				// ilk veri yollandı, kalan verilerin yazılması işlemi
				sizeOfData--;
			}
		}
	}
	//SON DATANIN BİLGİSİ KARŞI TARAFA DOĞRU GİTMEYEBİLİR.
	while(SPI_GetFlagStatus(SPI_Handle, SPI_Busy_FLAG)); // busy flag 0 olana kadar bekle! (7 bit kaydırılarak bakılır.)
}
SPI_FlagStatus_t SPI_GetFlagStatus(SPI_HandleTypeDef_t *SPI_Handle, uint16_t SPI_Flag)
{
	// SPI HANDLER İÇERİSİNDEKİ SR REGISTERI İLE FLAG AND İŞLEMİNE TABİ TUTULUR.
	//SONUÇ 1 GELİRSE SPI FLAG SET DÖNDÜRÜLÜR, DEĞİLSE RESET DÖNDÜRÜLÜR.
	return (SPI_Handle->Instance->SR & SPI_Flag) ? SPI_FLAG_SET : SPI_FLAG_RESET;

}

void SPI_TransmitData_IT(SPI_HandleTypeDef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData )
{
	//
	SPI_BusStatus_t busState = SPI_Handle->busStateTx;
	if(busState != SPI_BUS_BUSY_RX) // bus state eşit değilse bu döngüye girer.
	{
		SPI_Handle->pTxDataAddr = (uint8_t*)pData; //Verilen parametre pTxDataAddr = pData'nın adresine erişti.
		SPI_Handle->TxDataSize = (uint16_t)sizeOfData; // Datanın boyutuna erişildi.
		SPI_Handle->busStateTx = SPI_BUS_BUSY_RX; // Meşgul konuma alındı, veri yollanana kadar bu döngüye girmez.


		if(SPI_Handle->Instance->CR1 & (0x1U << SPI_CR1_DFF)) //
		{
			SPI_Handle->TxISRFunction = SPI_TransmitHelper_16Bits;
		}
		else
		{
			SPI_Handle->TxISRFunction = SPI_TransmitHelper_8Bits;
		}
		SPI_Handle->Instance->CR2 |= (0x1U << SPI_CR2_TXEIE); // Interrupt enable hale getirilir.
	}

}

// INTERRUPT'IN DOĞRU YERE GELİP GELMEDİĞİ KONTROL EDİLİR.
void SPI_InterruptHandler(SPI_HandleTypeDef_t *SPI_Handle)
{
	uint8_t interruptSource = 0;
	uint8_t interruptFlag = 0;
	interruptSource = SPI_Handle->Instance->CR2 & (0x1U << SPI_CR2_TXEIE); // TXEIE INTERRUPT FLAG' I ENABLE İSE 1 YAP
	interruptFlag = SPI_Handle->Instance->SR & (0x1U << SPI_SR_TxE);
	if((interruptSource != 0) && (interruptFlag != 0 ))
	{
		SPI_Handle->TxISRFunction(SPI_Handle);
	}
}


