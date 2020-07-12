#include <wiringPi.h>
#include <stdint.h>
#include <iostream>
#include <chrono>
#include <ctime>

int Driver1A = 8;
int Driver1B = 9;
int Driver1C = 7;
int Driver1D = 0;

int Driver2A = 2;
int Driver2B = 3;
int Driver2C = 12;
int Driver2D = 13;

int Driver3A = 14;
int Driver3B = 30;
int Driver3C = 21;
int Driver3D = 22;

int Driver4A = 23;
int Driver4B = 24;
int Driver4C = 25;
int Driver4D = 15;

int Driver5A = 16;
int Driver5B = 1;
int Driver5C = 4;
int Driver5D = 5;

int Driver6A = 6;
int Driver6B = 10;
int Driver6C = 11;
int Driver6D = 31;





int CurrentValue = 0;

void nixieWrite(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t value)
{
    //D is most significant bit
    //A is least significant bit
    digitalWrite(d, (value & 0x08) >> 3);
    digitalWrite(c, (value & 0x04) >> 2);
    digitalWrite(b, (value & 0x02) >> 1);
    digitalWrite(a, value & 0x01);
}

int main()
{
    wiringPiSetup();
    pinMode(Driver1A, OUTPUT);
    pinMode(Driver1B, OUTPUT);
    pinMode(Driver1C, OUTPUT);
    pinMode(Driver1D, OUTPUT);

    pinMode(Driver2A, OUTPUT);
    pinMode(Driver2B, OUTPUT);
    pinMode(Driver2C, OUTPUT);
    pinMode(Driver2D, OUTPUT);

    pinMode(Driver3A, OUTPUT);
    pinMode(Driver3B, OUTPUT);
    pinMode(Driver3C, OUTPUT);
    pinMode(Driver3D, OUTPUT);

    pinMode(Driver4A, OUTPUT);
    pinMode(Driver4B, OUTPUT);
    pinMode(Driver4C, OUTPUT);
    pinMode(Driver4D, OUTPUT);


    nixieWrite(Driver1A, Driver1B, Driver1C, Driver1D, 0);
    nixieWrite(Driver2A, Driver2B, Driver2C, Driver2D, 0);
    nixieWrite(Driver3A, Driver3B, Driver3C, Driver3D, 0);
    nixieWrite(Driver4A, Driver4B, Driver4C, Driver4D, 0);

/*

    while (true) {
        for (int i = 0; i < 10; i++)
        {
            nixieWrite(Driver1A, Driver1B, Driver1C, Driver1D, i);
            nixieWrite(Driver2A, Driver2B, Driver2C, Driver2D, i);
            nixieWrite(Driver3A, Driver3B, Driver3C, Driver3D, i);
            nixieWrite(Driver4A, Driver4B, Driver4C, Driver4D, i);
            delay(1000);
        }
    }

*/
    while (true)
    {
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

	// Count up from zero to reach the required digit

        for (int i = 0; i < Hours0 + 1; i++) {
            nixieWrite(Driver1A, Driver1B, Driver1C, Driver1D, i);
            delay(50);
        }

        for (int i = 0; i < Hours1 + 1; i++) {
            nixieWrite(Driver2A, Driver2B, Driver2C, Driver2D, i);
            delay(50);
        }

        for (int i = 0; i < Minutes0 + 1; i++) {
            nixieWrite(Driver3A, Driver3B, Driver3C, Driver3D, i);
            delay(50);
        }

        for (int i = 0; i < Minutes1 + 1; i++) {
            nixieWrite(Driver4A, Driver4B, Driver4C, Driver4D, i);
            delay(50);
        }


        // Drive the letters
        nixieWrite(Driver1A, Driver1B, Driver1C, Driver1D, Hours0);
        nixieWrite(Driver2A, Driver2B, Driver2C, Driver2D, Hours1);

        nixieWrite(Driver3A, Driver3B, Driver3C, Driver3D, Minutes0);
        nixieWrite(Driver4A, Driver4B, Driver4C, Driver4D, Minutes1);

        delay(1000);

	// Count up from digit to 9
	for (int i = Hours0; i < 10; i++) {
            nixieWrite(Driver1A, Driver1B, Driver1C, Driver1D, i);
            delay(50);
        }

        for (int i = Hours1; i < 10; i++) {
            nixieWrite(Driver2A, Driver2B, Driver2C, Driver2D, i);
            delay(50);
        }

        for (int i = Minutes0; i < 10; i++) {
            nixieWrite(Driver3A, Driver3B, Driver3C, Driver3D, i);
            delay(50);
        }

        for (int i = Minutes1; i < 10; i++) {
            nixieWrite(Driver4A, Driver4B, Driver4C, Driver4D, i);
            delay(50);
        }

        delay(150);

        for (int i = 9; i > -1; i--)
        {
            nixieWrite(Driver1A, Driver1B, Driver1C, Driver1D, i);
            nixieWrite(Driver2A, Driver2B, Driver2C, Driver2D, i);
            nixieWrite(Driver3A, Driver3B, Driver3C, Driver3D, i);
            nixieWrite(Driver4A, Driver4B, Driver4C, Driver4D, i);
            delay(50);
        }

        delay(150);

        
    }
}
