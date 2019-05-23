/**
	The class implements a set of methods of the MAX6675_Thermocouple.h
	interface for working with a thermocouple based on the MAX6675
	driver and reading a temperature in Celsius, Fahrenheit and Kelvin.

	https://github.com/YuriiSalimov/MAX6675_Thermocouple

	Created by Yurii Salimov, February, 2018.
	Released into the public domain.
*/
#include "MAX6675_Thermocouple.h"

#define USE_FREERTOS_DELAY 1
static const int spiClk = 4000000UL; 
static const int MAX6675_CONVERSION_TIME = 220;

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

MAX6675_Thermocouple::MAX6675_Thermocouple(
	SPIClass* spi,
	int CS_pin
) 
{
	this->SCK_pin = -1;
	this->CS_pin = CS_pin;
	this->SO_pin = -1;
	setReadingsNumber(1);
	setDelayTime(1);
	_spi = spi;
	init();
}

inline void MAX6675_Thermocouple::init() {
	pinMode(this->CS_pin, OUTPUT);
	digitalWrite(this->CS_pin, HIGH);

	#if USE_HW_SPI == 1
	_spi->begin();
	#else
	pinMode(this->SCK_pin, OUTPUT);
	pinMode(this->SO_pin, INPUT);
	#endif


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

inline double MAX6675_Thermocouple::calcCelsius() {

	int value;

	#if USE_HW_SPI == 1
		value = spiread_hw();
	#else
		digitalWrite(this->CS_pin, LOW);
		delay(1);	
		value = spiread();
		value <<= 8;
		value |= spiread();
		digitalWrite(this->CS_pin, HIGH);
	#endif

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
		delayMicroseconds(1);
		if (digitalRead(this->SO_pin)) {
			value |= (1 << i);
		}
		digitalWrite(this->SCK_pin, HIGH);
		delayMicroseconds(1);
	}
	return value;
}
#if USE_HW_SPI == 1
	int MAX6675_Thermocouple::spiread_hw() {
		int value = 0;
		digitalWrite(this->CS_pin, LOW);
		delayMicroseconds(1);
		digitalWrite(this->CS_pin, HIGH);
		#if USE_FREERTOS_DELAY == 0
			delay(MAX6675_CONVERSION_TIME);
		#else
			vTaskDelay(MAX6675_CONVERSION_TIME);
		#endif
		_spi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
		digitalWrite(this->CS_pin, LOW);
		value = _spi->transfer16(0x00);
		digitalWrite(this->CS_pin, HIGH);
		_spi->endTransaction();
		return value;
	}
#endif
inline void MAX6675_Thermocouple::sleep() {
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

inline double MAX6675_Thermocouple::celsiusToKelvins(const double celsius) {
	return (celsius + 273.15);
}

inline double MAX6675_Thermocouple::celsiusToFahrenheit(const double celsius) {
	return (celsius * 9.0 / 5.0 + 32);
}

void MAX6675_Thermocouple::setReadingsNumber(const int newReadingsNumber) {
	this->readingsNumber = validate(newReadingsNumber, MAX6675_DEFAULT_READINGS_NUMBER);
}

void MAX6675_Thermocouple::setDelayTime(const long newDelayTime) {
	this->delayTime = validate(newDelayTime, MAX6675_DEFAULT_DELAY_TIME);
}

template <typename A, typename B>
A MAX6675_Thermocouple::validate(const A data, const B alternative) {
	return (data > 0) ? data : alternative;
}
