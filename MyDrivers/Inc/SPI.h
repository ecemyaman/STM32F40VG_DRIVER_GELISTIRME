#ifndef INC_SPI_H_
#define INC_SPI_H_
#include "STM32F407xx.h"

//SPI BAUDRATE - İLGİLİ BİTLERDEN HANGİSİNİ 1 YAPMAK İSTİYORSAK BURADA SAYI OLUŞTURDUK
#define SPI_BAUDRATE_DIV2				((uint32_t)(0x00000000))
#define SPI_BAUDRATE_DIV4				((uint32_t)(0x00000008))	//3. BİTİ 1 OLAN SAYI
#define SPI_BAUDRATE_DIV8				((uint32_t)(0x00000010))	//3. BİT 0, 4. BİT 1 OLAN SAYI
#define SPI_BAUDRATE_DIV16				((uint32_t)(0x00000018))	//3. BİT 1, 4. BİT 1 OLAN SAYI
#define SPI_BAUDRATE_DIV32				((uint32_t)(0x00000020))	//5. BİTİ 1 OLAN SAYI
#define SPI_BAUDRATE_DIV64				((uint32_t)(0x00000028))	//3. BİT 1, 5. BİT 1 OLAN SAYI
#define SPI_BAUDRATE_DIV128				((uint32_t)(0x00000030))	//4. BİT 1, 5. BİT 1 OLAN SAYI
#define SPI_BAUDRATE_DIV256				((uint32_t)(0x00000038))	//3-4-5 1 OLAN SAYI

//CPHA
#define SPI_CPHA_FIRST					((uint32_t)(0x00000000))
#define SPI_CPHA_SECOND					((uint32_t)(0x00000001))

//CPOL
#define SPI_CPOL_LOW					((uint32_t)(0x00000000))
#define SPI_CPOL_HIGH					((uint32_t)(0x00000002))

//DFF
#define	SPI_DFF_8BITS					((uint32_t)(0x00000000))
#define SPI_DFF_16BITS					((uint32_t)(0x00000800))

//MODE
#define SPI_MODE_MASTER					((uint32_t)(0x00000000))
#define	SPI_MODE_SLAVE					((uint32_t)(0x00000004))

//FF_VALUES
#define SPI_FRAMEFORMAT_MSB				((uint32_t)(0x00000000))
#define SPI_FRAMEFORMAT_LSB				((uint32_t)(0x00000080))

// BUS CONFIG
#define SPI_BUS_FullDublex				((uint32_t)(0x00000000))
#define SPI_BUS_ReceiveOnly				((uint32_t)(0x00000400))
#define SPI_BUS_HalfDublex_T			((uint32_t)(0x0000C000))
#define SPI_BUS_HalfDublex_R			((uint32_t)(0x00008000))

//SSM_VALUES
#define SPI_SSM_DISABLE					((uint32_t)(0x00000000))
#define SPI_SSM_ENABLE					((uint32_t)(0x00000300))

// ENUM YAPISI İLE VERİ AKTARIMI SIRASINDA MEŞGUL OLUP OLUNMADIĞI DURUMU ONTROL EDİLİR
typedef enum
{
	SPI_BUS_FREE = 0x0U,
	SPI_BUS_BUSY_TX = 0x1U,
	SPI_BUS_BUSY_RX = 0x2U
}SPI_BusStatus_t;

typedef enum
{
	SPI_FLAG_RESET = 0x0U,
	SPI_FLAG_SET = !SPI_FLAG_RESET
}SPI_FlagStatus_t;

typedef struct
{
	uint32_t Mode;
	uint32_t CPHA;
	uint32_t CPOL;
	uint32_t BaudRate;
	uint32_t SSM_Cmd;
	uint32_t DFF_Format;
	uint32_t BusConfig;
	uint32_t FrameFormat;

}SPI_InitTypeDef_t;


//SPI KONFİGÜRASYONLARI BURADA SAĞLANIR.
typedef struct	__SPI_HandleTypeDef_t
{
	SPI_TypeDef_t *Instance; // SPI typedef türünden oluşturulan değişken adres tutar.
							//Tek bir structure aynı zamanda adres de tutacaktır.
	SPI_InitTypeDef_t Init;

	uint8_t *pTxDataAddr;
	uint16_t TxDataSize;
	uint8_t busStateTx;
	void(*TxISRFunction)(struct __SPI_HandleTypeDef_t *SPI_Handle);

}SPI_HandleTypeDef_t;

void SPI_Init(SPI_HandleTypeDef_t *SPI_Handle);
void SPI_PeriphCmd(SPI_HandleTypeDef_t *SPI_Handle, FunctionalState_t stateOfSPI);
void SPI_TransmitData(SPI_HandleTypeDef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData);
void SPI_TransmitData_IT(SPI_HandleTypeDef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData );
SPI_FlagStatus_t SPI_GetFlagStatus(SPI_HandleTypeDef_t *SPI_Handle, uint16_t SPI_Flag);
void SPI_InterruptHandler(SPI_HandleTypeDef_t *SPI_Handle);

#endif /* INC_SPI_H_ */
