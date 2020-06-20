#include <wiringPi.h>
#include <stdint.h>

/* RPI 3B+ pinout (USB ports facing downward)
3.3v		5v
(SDA) 2		5V
(SCL) 3		GND
4			14 (UART0 TXD)
GND			15 (UART0 RXD)
17			18 (UART0 CLK)
27			GND
22			23
3.3v		24
(MOSI) 10	GND
(MISO) 9	25
(CLK) 11	8 (CE0_N)
GND			7 (CE1_N)
(I2C) DNC	DNC (I2C)
5			GND
6			12
13			GND
19			16
26			20
GND			21
*/

// update the Property Pages - Build Events - Remote Post-Build Event command 
// which uses gpio export for setup for wiringPiSetupSys

struct DriverOne {
	int A = 17;
	int B = 27;
	int C = 22;
	int D = 18;
	uint8_t CurrentDigit = 0;
};

struct DriverTwo {
	int A = 5;
	int B = 6;
	int C = 13;
	int D = 19;
	uint8_t CurrentDigit = 0;
};

struct DriverThree {
	int A = 12;
	int B = 16;
	int C = 20;
	int D = 21;
	uint8_t CurrentDigit = 0;
};

struct DriverFour {
	int A = 0;
	int B = 0;
	int C = 0;
	int D = 0;
	uint8_t CurrentDigit = 0;
};

struct DriverFive {
	int A = 0;
	int B = 0;
	int C = 0;
	int D = 0;
	uint8_t CurrentDigit = 0;
};

struct DriverSix {
	int A = 0;
	int B = 0;
	int C = 0;
	int D = 0;
	uint8_t CurrentDigit = 0;
};

void NixieControl(int WhichDriver, uint8_t value) {

	DriverOne* DriverOne;
	DriverTwo* DriverTwo;
	DriverThree* DriverThree;
	DriverFour* DriverFour;
	DriverFive* DriverFive;
	DriverSix* DriverSix;

	switch (WhichDriver)
	{
	case 1:
		digitalWrite(DriverOne->D, (value & 0x08) >> 3);
		digitalWrite(DriverOne->C, (value & 0x04) >> 2);
		digitalWrite(DriverOne->B, (value & 0x02) >> 1);
		digitalWrite(DriverOne->A, value & 0x01);
		break;
	case 2:
		digitalWrite(DriverTwo->D, (value & 0x08) >> 3);
		digitalWrite(DriverTwo->C, (value & 0x04) >> 2);
		digitalWrite(DriverTwo->B, (value & 0x02) >> 1);
		digitalWrite(DriverTwo->A, value & 0x01);
		break;
	case 3:
		digitalWrite(DriverThree->D, (value & 0x08) >> 3);
		digitalWrite(DriverThree->C, (value & 0x04) >> 2);
		digitalWrite(DriverThree->B, (value & 0x02) >> 1);
		digitalWrite(DriverThree->A, value & 0x01);
		break;
	case 4:
		digitalWrite(DriverFour->D, (value & 0x08) >> 3);
		digitalWrite(DriverFour->C, (value & 0x04) >> 2);
		digitalWrite(DriverFour->B, (value & 0x02) >> 1);
		digitalWrite(DriverFour->A, value & 0x01);
		break;
	case 5:
		digitalWrite(DriverFive->D, (value & 0x08) >> 3);
		digitalWrite(DriverFive->C, (value & 0x04) >> 2);
		digitalWrite(DriverFive->B, (value & 0x02) >> 1);
		digitalWrite(DriverFive->A, value & 0x01);
		break;
	case 6:
		digitalWrite(DriverSix->D, (value & 0x08) >> 3);
		digitalWrite(DriverSix->C, (value & 0x04) >> 2);
		digitalWrite(DriverSix->B, (value & 0x02) >> 1);
		digitalWrite(DriverSix->A, value & 0x01);
		break;
	default:
		break;
	}

}

void CycleFromZero() {
	DriverOne* DriverOne;
	DriverTwo* DriverTwo;
	while (true)
	{
		CycleAllDigits(1000);
	}
}

// For keeping cathode poisoning down
// Also useful for cycling from 0.
void CycleAllDigits(unsigned int DelayTime)
{

	for (uint8_t i = 0; i < 10; i++) {
		NixieControl(1, i);
		NixieControl(2, i);
		NixieControl(3, i);
		NixieControl(4, i);
		NixieControl(5, i);
		NixieControl(6, i);
		delay(DelayTime);
	}
}

int main(void)
{
	// Declare driver object(s)
	DriverOne* DriverOne;
	DriverTwo* DriverTwo;
	DriverThree* DriverThree;
	DriverFour* DriverFour;
	DriverFive* DriverFive;
	DriverSix* DriverSix;

	// Wiring pi setup for sys usage
	wiringPiSetupSys();

	// Declare output pins
	pinMode(DriverOne->A, OUTPUT);
	pinMode(DriverOne->B, OUTPUT);
	pinMode(DriverOne->C, OUTPUT);
	pinMode(DriverOne->D, OUTPUT);

	pinMode(DriverTwo->A, OUTPUT);
	pinMode(DriverTwo->B, OUTPUT);
	pinMode(DriverTwo->C, OUTPUT);
	pinMode(DriverTwo->D, OUTPUT);

	pinMode(DriverThree->A, OUTPUT);
	pinMode(DriverThree->B, OUTPUT);
	pinMode(DriverThree->C, OUTPUT);
	pinMode(DriverThree->D, OUTPUT);

	pinMode(DriverFour->A, OUTPUT);
	pinMode(DriverFour->B, OUTPUT);
	pinMode(DriverFour->C, OUTPUT);
	pinMode(DriverFour->D, OUTPUT);

	pinMode(DriverFive->A, OUTPUT);
	pinMode(DriverFive->B, OUTPUT);
	pinMode(DriverFive->C, OUTPUT);
	pinMode(DriverFive->D, OUTPUT);

	pinMode(DriverSix->A, OUTPUT);
	pinMode(DriverSix->B, OUTPUT);
	pinMode(DriverSix->C, OUTPUT);
	pinMode(DriverSix->D, OUTPUT);

	// Set all digits to 0
	NixieControl(1, DriverOne->CurrentDigit);
	NixieControl(2, DriverTwo->CurrentDigit);
	NixieControl(3, DriverTwo->CurrentDigit);
	NixieControl(4, DriverTwo->CurrentDigit);
	NixieControl(5, DriverTwo->CurrentDigit);
	NixieControl(6, DriverTwo->CurrentDigit);

	// Cycle digits from 0 to 9 forever
	CycleFromZero();

	return 0;
}