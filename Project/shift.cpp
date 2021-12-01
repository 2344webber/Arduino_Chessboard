#include <Arduino.h>

class shift165
{
private:
	uint8_t shift_load;
	uint8_t output;
	uint8_t clock;
	uint8_t amount;

public:
	shift165(int _shift_load, int _output, int _clock)
	{
		shift_load = _shift_load;
		output = _output;
		clock = _clock;
		pinMode(shift_load, OUTPUT);
		pinMode(output, INPUT);
		pinMode(clock, OUTPUT);
	}
	shift165(int _shift_load, int _output, int _clock, int _amount)
	{
		shift_load = _shift_load;
		output = _output;
		clock = _clock;
		amount = _amount;
		pinMode(shift_load, OUTPUT);
		pinMode(output, INPUT);
		pinMode(clock, OUTPUT);
	}
	bool read(uint8_t pin)
	{
		digitalWrite(clock, 0);
		digitalWrite(shift_load, 0);
		delayMicroseconds(3);
		digitalWrite(shift_load, 1);
		for (int i = amount * 8 - 1; i > pin; i--)
		{
			digitalWrite(clock, 1);
			delayMicroseconds(3);
			digitalWrite(clock, 0);
		}
		return digitalRead(output);
	}
};
