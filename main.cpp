#include <wiringPi.h>
#include <stdint.h>
#include <iostream>
#include <chrono>
#include <ctime> 

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
	int A = 4;
	int B = 14;
	int C = 15;
	int D = 17;
	uint8_t CurrentDigit = 0;
};

struct DriverTwo {
	int A = 18;
	int B = 27;
	int C = 22;
	int D = 23;
	uint8_t CurrentDigit = 0;
};

struct DriverThree {
	int A = 24;
	int B = 10;
	int C = 9;
	int D = 11;
	uint8_t CurrentDigit = 0;
};

struct DriverFour {
	int A = 8;
	int B = 7;
	int C = 5;
	int D = 6;
	uint8_t CurrentDigit = 0;
};

struct DriverFive {
	int A = 12;
	int B = 13;
	int C = 19;
	int D = 16;
	uint8_t CurrentDigit = 0;
};

struct DriverSix {
	int A = 2;
	int B = 3;
	int C = 20;
	int D = 21;
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
	while (true)
	{
		CycleAllDigits(1000);
	}
}

void CycleFromOffset(unsigned int DelayTime) {
	DriverOne* DriverOne;
	DriverTwo* DriverTwo;
	DriverThree* DriverThree;
	DriverFour* DriverFour;
	DriverFive* DriverFive;
	DriverSix* DriverSix;

	DriverOne->CurrentDigit = 0;
	DriverTwo->CurrentDigit = 1;
	DriverThree->CurrentDigit = 2;
	DriverFour->CurrentDigit = 3;
	DriverFive->CurrentDigit = 4;
	DriverSix->CurrentDigit = 5;

	while (true) {
		if (DriverOne->CurrentDigit > 9) {
			DriverOne->CurrentDigit = 0;
		}
		if (DriverTwo->CurrentDigit > 9) {
			DriverTwo->CurrentDigit = 0;
		}
		if (DriverThree->CurrentDigit > 9) {
			DriverThree->CurrentDigit = 0;
		}
		if (DriverFour->CurrentDigit > 9) {
			DriverFour->CurrentDigit = 0;
		}
		if (DriverFive->CurrentDigit > 9) {
			DriverFive->CurrentDigit = 0;
		}
		if (DriverSix->CurrentDigit > 9) {
			DriverSix->CurrentDigit = 0;
		}

		NixieControl(1, DriverOne->CurrentDigit);
		NixieControl(2, DriverTwo->CurrentDigit);
		NixieControl(3, DriverThree->CurrentDigit);
		NixieControl(4, DriverFour->CurrentDigit);
		NixieControl(5, DriverFive->CurrentDigit);
		NixieControl(6, DriverSix->CurrentDigit);

		DriverOne->CurrentDigit++;
		DriverTwo->CurrentDigit++;
		DriverThree->CurrentDigit++;
		DriverFour->CurrentDigit++;
		DriverFive->CurrentDigit++;
		DriverSix->CurrentDigit++;

		delay(DelayTime);
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

void RTCMode()
{
	while (true) {

		auto start = std::chrono::system_clock::now();
		auto end = std::chrono::system_clock::now();
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);
		std::string CurrentTime = std::ctime(&end_time);
		std::string CopyOfTime = CurrentTime;

		// Remove the year
		CurrentTime = CurrentTime.substr(0, CurrentTime.length() - 5);

		// Get the last 2 digits - Seconds
		std::string Seconds = CurrentTime.substr(CurrentTime.length() - 3, CurrentTime.length());

		// Remove the seconds and semicolon
		CurrentTime = CurrentTime.substr(0, CurrentTime.length() - 3);

		// Get the minutes
		std::string Minutes = CurrentTime.substr(CurrentTime.length() - 3, CurrentTime.length());

		// Remove the minutes and semicolon
		CurrentTime = CurrentTime.substr(0, CurrentTime.length() - 3);

		// Get the seconds
		std::string Hours = CurrentTime.substr(CurrentTime.length() - 3, CurrentTime.length());

		Seconds = Seconds.substr(0, 2);
		Minutes = Minutes.substr(0, 2);
		Hours = Hours.substr(0, 2);

		int Hours0 = std::atoi(Hours.substr(0, 1).c_str());
		int Hours1 = std::atoi(Hours.substr(1, 2).c_str());

		int Minutes0 = std::atoi(Minutes.substr(0, 1).c_str());
		int Minutes1 = std::atoi(Minutes.substr(1, 2).c_str());

		int Seconds0 = std::atoi(Seconds.substr(0, 1).c_str());
		int Seconds1 = std::atoi(Seconds.substr(1, 2).c_str());

		NixieControl(1, Hours0);
		NixieControl(2, Hours1);
		NixieControl(3, Minutes0);
		NixieControl(4, Minutes1);
		NixieControl(5, Seconds0);
		NixieControl(6, Seconds1);
		
		delay(1000);
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
