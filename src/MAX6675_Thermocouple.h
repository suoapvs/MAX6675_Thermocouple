/**
	MAX6675_Thermocouple.h - The interface describes a set of methods 
	for working with a thermocouple based on the MAX6675 driver 
	and reading a temperature in Celsius, Fahrenheit and Kelvin.

	Instantiation:
		MAX6675_Thermocouple thermocouple(3, 4, 5);

	Read temperature:
		thermocouple.readCelsius();
		thermocouple.readKelvin();
		thermocouple.readFahrenheit();

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

/**
	How many readings are taken to determine a mean temperature. 
	The more values, the longer a calibration is performed, 
	but the readings will be more accurate.
*/
#define MAX6675_THERMOCOUPLE_READINGS_NUMBER	5

/**
	Delay time between a temperature readings 
	from the temperature sensor (ms).
*/
#define MAX6675_THERMOCOUPLE_TIME_DELAY	5

/**
	Celsius to Fahrenheit conversion:
	F = C * 9 / 5 + 32
*/
#define CELSIUS_TO_FAHRENHEIT(C) (((C) * 9.0 / 5.0 + 32))

/**
	Celsius to Kelvin conversion:
	K = C + 273.15
*/
#define CELSIUS_TO_KELVINS(C) (((C) + 273.15))

class MAX6675_Thermocouple final {

	private:
		int SCK_pin = 0;
		int CS_pin = 0;
		int SO_pin = 0;

	public:
		/**
			Constructor.
			@param SCK_pin - SCK digital port number.
			@param CS_pin - CS digital port number.
			@param SO_pin - SO digital port number.
		*/
		MAX6675_Thermocouple(const int SCK_pin, const int CS_pin, const int SO_pin);

		/**
			Reads a temperature in Celsius from the thermocouple.
			@return temperature in Celsius.
		*/
		double readCelsius();
		
		/**
			Returns a temperature in Fahrenheit.
			@return temperature in Fahrenheit.
		*/
		double readFahrenheit();
		
		/**
			Returns a temperature in Fahrenheit.
			(For older devices.)
			@return temperature in Fahrenheit.
		*/
		double readFarenheit();
		
		/**
			Returns a temperature in Kelvin.
			@return temperature in Kelvin.
		*/
		double readKelvin();
	
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
	
		byte spiread();
};

#endif
