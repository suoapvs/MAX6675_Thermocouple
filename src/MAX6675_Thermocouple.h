/**
	MAX6675_Thermocouple - class describes a set of methods
	for working with a thermocouple based on the MAX6675 driver
	and reading a temperature in Celsius, Fahrenheit and Kelvin.

	Instantiation:
		Thermocouple* thermocouple = new MAX6675_Thermocouple(
		SCK_pin, CS_pin, SO_pin
	);

	Read temperature:
	double celsius = thermocouple->readCelsius();
	double kelvin = thermocouple->readKelvin();
	double fahrenheit = thermocouple->readFahrenheit();

	v.1.1.2:
	- optimized calls of private methods.

	v.1.1.3:
	- Fixed bug in setReadingsNumber() method.

	v.1.1.4:
	- Removed deprecated init() method.

	v.2.0.0
	- implemented Thermocouple interface;
	- removed methods for averaging result.

	v.2.0.1
	- optimized celsiusToFahrenheit() method;
	- updated documentation.

	https://github.com/YuriiSalimov/MAX6675_Thermocouple

	Created by Yurii Salimov, February, 2018.
	Released into the public domain.
*/
#ifndef MAX6675_THERMOCOUPLE_H
#define MAX6675_THERMOCOUPLE_H

#include "Thermocouple.h"

class MAX6675_Thermocouple final : public Thermocouple {

	private:
		int SCK_pin;
		int CS_pin;
		int SO_pin;

	public:
		/**
			Constructor

			@param SCK_pin - SCK digital port number
			@param CS_pin - CS digital port number
			@param SO_pin - SO digital port number
		*/
		MAX6675_Thermocouple(
			int SCK_pin,
			int CS_pin,
			int SO_pin
		);

		/**
			Reads a temperature in Celsius from the thermocouple.

			@return temperature in degree Celsius or
			NAN if no thermocouple attached
		*/
		double readCelsius();

		/**
			Reads a temperature in Kelvin from the thermocouple.

			@return temperature in degree Kelvin or
			NAN if no thermocouple attached
		*/
		double readKelvin();

		/**
			Reads a temperature in Fahrenheit from the thermocouple.

			@return temperature in degree Fahrenheit or
			NAN if no thermocouple attached
		*/
		double readFahrenheit();

	private:
		byte spiread();

		/**
			Celsius to Kelvin conversion:
			K = C + 273.15

			@param celsius - temperature in degree Celsius to convert
			@return temperature in degree Kelvin
		*/
		inline double celsiusToKelvins(double celsius);

		/**
			Celsius to Fahrenheit conversion:
			F = C * 1.8 + 32

			@param celsius - temperature in degree Celsius to convert
			@return temperature in degree Fahrenheit
		*/
		inline double celsiusToFahrenheit(double celsius);
};

#endif
