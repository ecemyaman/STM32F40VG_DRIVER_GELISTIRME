#include "GPIO.h"

void GPIO_Init(GPIO_TypeDef_t *GPIOx, GPIO_InitTypeDef_t *GPIO_ConfigStruct)
{
	//her bir pin numarası üzerinde gezinmesi gerekir.
	uint32_t position;
	uint32_t fakePosition =0;
	uint32_t lastPosition=0;
	for(position = 0; position < 16; position++)
	{
		fakePosition = (0x1 << position);	// 0000 0000 0000 0001 oluşturuldu
		lastPosition = (uint32_t)(GPIO_ConfigStruct->pinNumber) & fakePosition; // yukarıdaki sayi ile pin numarasını AND işlemine aldık
		if(fakePosition == lastPosition) //iki değer eşitse pin girilmiş demektir ve kullanıcı tarafından konfigüre edilmeye ihtiyacı vardır.
		{
			// MODE CONFIG
			uint32_t tempValue = GPIOx -> MODER; // GPIOx, mod register okundu
			tempValue &= ~(0x3U << (position*2)); //bitwise nor kullanarak  ilgili pinin  clear işlemi sağlandı.
			tempValue |= (GPIO_ConfigStruct -> Mode << (position * 2)); // struct yapısındaki mode bilgisine göre konfigürasyon sağlandı.
			GPIOx -> MODER = tempValue;

			if (GPIO_ConfigStruct -> Mode == GPIO_MODE_INPUT || GPIO_ConfigStruct -> Mode == GPIO_MODE_ANALOG)
			{
				// OUTPUT TYPE CONFIG
				tempValue = GPIOx -> OTYPER;
				tempValue &= ~(0x1U << position);
				tempValue |= (GPIO_ConfigStruct ->Otype << position);
				GPIOx->OTYPER = tempValue;

				//OSPEED REGİSTER
				tempValue = GPIOx -> OSPEEDR;
				tempValue &= ~(0x3U << (position *2));
				tempValue |= (GPIO_ConfigStruct->Speed << (position *2));
				GPIOx->OSPEEDR = tempValue;
			}

			//PUPDR REGISTER
			tempValue = GPIOx->PUPDR;
			tempValue &= ~(0x3U << (position *2));
			tempValue |= (GPIO_ConfigStruct->PuPd << (position *2));
			GPIOx->PUPDR = tempValue;

			// ALTERNATE FUNCTION
			if(GPIO_ConfigStruct->Mode == GPIO_MODE_AF)
			{
				tempValue = GPIOx->AFR[position >> 3U]; // 3 bit sağa kaydırmak 8 'e bölmek demektir. 0 olursa low, 1 olursa high
				tempValue &=  ~(0xFU << ((position & 0x7U)*4)); // 8'e göre mod alma işlemi yapılır, ilgili yer temizlenir.
				tempValue |= (GPIO_ConfigStruct->Alternate << ((position & 0x7U) *4));
				GPIOx->AFR[position >> 3U] >> tempValue; //registera konfigüre edilen değer verilir.
			}
		}

	}
}

void GPIO_WritePin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber, GPIO_PinState_t pinState) // function declaration
{
	if(pinState == GPIO_Pin_Set) // kulanıcının verdiği pinstate == set ise
	{
		GPIOx->BSRR = pinNumber;
	}
	else
	{
		GPIOx->BSRR = (pinNumber << 16U); //pin numarasını 16 bit kaydırarak yazar. Reset durumuna getirir.
	}

}
GPIO_PinState_t GPIO_ReadPin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber)
{
	GPIO_PinState_t bitStatus = GPIO_Pin_Reset; // Pin durumunu reset ettik
	if(GPIOx->IDR & pinNumber ) // Bir yerdeki veriyi okumak için, oradaki input data registerıyla pin numarası AND işlemine tabi tutulur.
	{
		bitStatus = GPIO_Pin_Set;
	}
	return bitStatus;
}

void GPIO_LockPin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber)
{
//Kilitleme için uygun bir veri türü oluşturulacaktır. Her seferinde 16. biti 1 yapmak zorunda kalmıyoruz.
	uint32_t tempValue = (0x1U << 16U) | pinNumber; //16. biti 1 olan Kalan 15 bit veri olan sayı oluşturduk VEYA ile 0-15 kısımlarını pin numarasına çevirdik.
	GPIOx->LCKR = tempValue;
	GPIOx->LCKR = pinNumber;
	GPIOx->LCKR = tempValue;
	tempValue = GPIOx->LCKR;
}
void GPIO_Toggle_Pin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber)
{
	uint32_t tempODRRegister = GPIOx->ODR;	//geçici değişken ile ODR'daki değeri okuyabildik.
	// ODR ile pin number AND işlemi yapıldığında orada veri varsa 1 olduğu algılanır. (BSRR ilk 16 bit set eder sonrası reset)
	//  ... || tempregisterın tersiyle pin numarasını AND'leyince 0 ları bulduk.
	GPIOx->BSRR = ((tempODRRegister & pinNumber) << 16U) || (~tempODRRegister & pinNumber);
}

















