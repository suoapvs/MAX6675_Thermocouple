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
) : MAX6675_Thermocouple(
		SCK_pin, CS_pin, SO_pin,
		MAX6675_DEFAULT_READINGS_NUMBER,
		MAX6675_DEFAULT_DELAY_TIME
) {
}

MAX6675_Thermocouple::MAX6675_Thermocouple(
	const int SCK_pin,
	const int CS_pin,
	const int SO_pin,
	const int readingsNumber,
	const long delayTime
) {
	this->SCK_pin = SCK_pin;
	this->CS_pin = CS_pin;
	this->SO_pin = SO_pin;
	setReadingsNumber(readingsNumber);
	setDelayTime(delayTime);
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
	Takes a readings number samples in a row,
	with a slight delay time.
	@return average temperature in Celsius.
*/
double MAX6675_Thermocouple::readCelsius() {
	double celsiusSum = 0;
	for (int i = 0; i < this->readingsNumber; i++) {
		celsiusSum += calcCelsius();
		sleep();
	}
	return (celsiusSum / this->readingsNumber);
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

void MAX6675_Thermocouple::sleep() {
	delay(this->delayTime);
}

/**
	Returns a temperature in Kelvin.
	Reads the temperature in Celsius,
	converts in Kelvin and return it.
	@return temperature in Kelvin.
*/
double MAX6675_Thermocouple::readKelvin() {
	return celsiusToKelvins(readCelsius());
}

/**
	Returns a temperature in Fahrenheit.
	Reads a temperature in Celsius,
	converts in Fahrenheit and return it.
	@return temperature in Fahrenheit.
*/
double MAX6675_Thermocouple::readFahrenheit() {
	return celsiusToFahrenheit(readCelsius());
}

double MAX6675_Thermocouple::readFarenheit() {
	return readFahrenheit();
}

void MAX6675_Thermocouple::setReadingsNumber(const int newReadingsNumber) {
	this->readingsNumber = validate(readingsNumber, MAX6675_DEFAULT_READINGS_NUMBER);
}

void MAX6675_Thermocouple::setDelayTime(const long newDelayTime) {
	this->delayTime = validate(newDelayTime, MAX6675_DEFAULT_DELAY_TIME);
}

template <typename A, typename B>
A MAX6675_Thermocouple::validate(const A data, const B min) {
	return (data > 0) ? data : min;
}

double MAX6675_Thermocouple::celsiusToKelvins(const double celsius) {
	return (celsius + 273.15);
}

double MAX6675_Thermocouple::celsiusToFahrenheit(const double celsius) {
	return (celsius * 9.0 / 5.0 + 32);
}
