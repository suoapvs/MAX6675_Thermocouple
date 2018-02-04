/**
	The class implements a set of methods of the MAX6675_Thermocouple.h 
	interface for working with a thermocouple based on the MAX6675 
	driver and reading a temperature in Celsius, Fahrenheit and Kelvin.
	
	https://github.com/YuriiSalimov/MAX6675_Thermocouple
	
	Created by Yurii Salimov, February, 2018.
	Released into the public domain.
*/
#include "MAX6675_Thermocouple.h"

MAX6675_Thermocouple::MAX6675_Thermocouple(
	const int SCK_pin,
	const int CS_pin,
	const int SO_pin
) {
	this->SCK_pin = SCK_pin;
	this->CS_pin = CS_pin;
	this->SO_pin = SO_pin;
	init();
}

void MAX6675_Thermocouple::init() {
	pinMode(this->SCK_pin, OUTPUT); 
	pinMode(this->CS_pin, OUTPUT);
	pinMode(this->SO_pin, INPUT);
	digitalWrite(this->CS_pin, HIGH);	
}

/**
	Reads a temperature from the thermocouple.
	Takes THERMOCOUPLE_READINGS_NUMBER samples in a row, 
	with a slight delay THERMOCOUPLE_TIME_DELAY.
	@return average temperature in Celsius.
*/
double MAX6675_Thermocouple::readCelsius() {
	double celsius = 0;
	for (int i = 0; i < MAX6675_THERMOCOUPLE_READINGS_NUMBER; i++) {
		celsius += calcCelsius();
		delay(MAX6675_THERMOCOUPLE_TIME_DELAY);
	}
	return (celsius / MAX6675_THERMOCOUPLE_READINGS_NUMBER);
}

/**
	Returns a temperature in Fahrenheit.
	Reads a temperature in Celsius, 
	converts in Fahrenheit and return it.
	@return temperature in Fahrenheit.
*/
double MAX6675_Thermocouple::readFahrenheit() {
	const double celsius = readCelsius();
	return CELSIUS_TO_FAHRENHEIT(celsius);
}

double MAX6675_Thermocouple::readFarenheit() {
	return readFahrenheit();
}

/**
	Returns a temperature in Kelvin.
	Reads the temperature in Celsius, 
	converts in Kelvin and return it.
	@return temperature in Kelvin.
*/
double MAX6675_Thermocouple::readKelvin() {
	const double celsius = readCelsius();
	return CELSIUS_TO_KELVINS(celsius);
}

double MAX6675_Thermocouple::calcCelsius() {
	int value;
	digitalWrite(this->CS_pin, LOW);
	delay(1);
	value = spiread();
	value <<= 8;
	value |= spiread();
	digitalWrite(this->CS_pin, HIGH);
	if (value & 0x4) {
		return NAN; 
	}
	value >>= 3;
	return (value * 0.25);
}

byte MAX6675_Thermocouple::spiread() { 
	byte value = 0;
	for (int i = 7; i >= 0; i--) {
		digitalWrite(this->SCK_pin, LOW);
		delay(1);
		if (digitalRead(this->SO_pin)) {
			value |= (1 << i);
		}
		digitalWrite(this->SCK_pin, HIGH);
		delay(1);
	}
	return value;
}
