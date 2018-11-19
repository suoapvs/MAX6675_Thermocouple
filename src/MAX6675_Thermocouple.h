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

	v.1.1.2:
	- optimized calls of private methods.

	v.1.1.3:
	- Fixed bug in setReadingsNumber() method.

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
		int SCK_pin;
		int CS_pin;
		int SO_pin;
		volatile int readingsNumber;
		volatile long delayTime;

	public:
		/**
			Constructor.
			@param SCK_pin - SCK digital port number.
			@param CS_pin - CS digital port number.
			@param SO_pin - SO digital port number.
		*/
		MAX6675_Thermocouple(
			int SCK_pin,
			int CS_pin,
			int SO_pin
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
			int SCK_pin,
			int CS_pin,
			int SO_pin,
			int readingsNumber,
			long delayTime
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

		void setReadingsNumber(int newReadingsNumber);

		void setDelayTime(long newDelayTime);

	private:
		/**
			Initialization of module.
		*/
		inline void init();

		/**
			Calculates a temperature in Celsius.
			@return temperature in Celsius.
		*/
		inline double calcCelsius();

		/**
			Celsius to Kelvin conversion:
			K = C + 273.15
		*/
		inline double celsiusToKelvins(double celsius);

		/**
			Celsius to Fahrenheit conversion:
			F = C * 9 / 5 + 32
		*/
		inline double celsiusToFahrenheit(double celsius);

		byte spiread();

		inline void sleep();

		/**
			Returns the data if it is valid,
			otherwise returns alternative data.
		*/
		template <typename A, typename B> A validate(A data, B alternative);
};

#endif
