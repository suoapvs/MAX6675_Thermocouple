/**
	MAX6675_Thermocouple.h - The interface describes a set of methods
	for working with a thermocouple based on the MAX6675 driver
	and reading a temperature in Celsius, Fahrenheit and Kelvin.

	Instantiation:
		MAX6675_Thermocouple thermocouple(SCK_pin, CS_pin, SO_pin);
		or
		MAX6675_Thermocouple thermocouple(
			SCK_pin, CS_pin, SO_pin,
			READINGS_NUMBER, DELAY_TIME
		);

		Where,
		READINGS_NUMBER - How many readings are taken
		to determine a mean temperature. The more values,
		the longer a calibration is performed, but the readings
		will be more accurate.

		DELAY_TIME - Delay time between a temperature readings
		from the temperature sensor (ms).

	Read temperature:
		double celsius = thermocouple.readCelsius();
		double kelvin = thermocouple.readKelvin();
		double fahrenheit = thermocouple.readFahrenheit();

	https://github.com/YuriiSalimov/MAX6675_Thermocouple

	Created by Yurii Salimov, February, 2018.
	Released into the public domain.
*/
#ifndef MAX6675_THERMOCOUPLE_H
#define MAX6675_THERMOCOUPLE_H

#if defined(ARDUINO) && (ARDUINO >= 100)
	#include <Arduino.h>
#else
	#include <WProgram.h>
#endif

#define MAX6675_DEFAULT_READINGS_NUMBER	5
#define MAX6675_DEFAULT_DELAY_TIME	5

class MAX6675_Thermocouple final {

	private:
		int SCK_pin = 0;
		int CS_pin = 0;
		int SO_pin = 0;

		volatile int readingsNumber = 0;
		volatile long delayTime = 0;

	public:
		/**
			Constructor.
			@param SCK_pin - SCK digital port number.
			@param CS_pin - CS digital port number.
			@param SO_pin - SO digital port number.
		*/
		MAX6675_Thermocouple(
			const int SCK_pin,
			const int CS_pin,
			const int SO_pin
		);

		/**
			Constructor.
			@param SCK_pin - SCK digital port number.
			@param CS_pin - CS digital port number.
			@param SO_pin - SO digital port number.
			@param readingsNumber - how many readings are
				taken to determine a mean temperature.
			@param delayTime - delay time between
				a temperature readings (ms).
		*/
		MAX6675_Thermocouple(
			const int SCK_pin,
			const int CS_pin,
			const int SO_pin,
			const int readingsNumber,
			const long delayTime
		);

		/**
			Reads and returns a temperature in Celsius
			from the thermocouple.
		*/
		double readCelsius();

		/**
			Returns a temperature in Kelvin.
		*/
		double readKelvin();

		/**
			Returns a temperature in Fahrenheit.
		*/
		double readFahrenheit();

		/**
			Returns a temperature in Fahrenheit.
			(For older devices.)
		*/
		double readFarenheit();

		void setReadingsNumber(const int newReadingsNumber);

		void setDelayTime(const long newDelayTime);

	private:
		/**
			Initialization of module.
		*/
		void init();

		/**
			Calculates a temperature in Celsius.
			@return temperature in Celsius.
		*/
		double calcCelsius();

		/**
			Celsius to Kelvin conversion:
			K = C + 273.15
		*/
		double celsiusToKelvins(const double celsius);

		/**
			Celsius to Fahrenheit conversion:
			F = C * 9 / 5 + 32
		*/
		double celsiusToFahrenheit(const double celsius);

		byte spiread();

		void sleep();

		template <typename A, typename B> A validate(const A data, const B min);
};

#endif
