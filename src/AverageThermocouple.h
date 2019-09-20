/**
  AverageThermocoupler - class-wrapper allows to average
  the temperature value of origin Thermocouple instance.

  Instantiation:
  Thermocouple* thermocouple = new AverageThermocouple(
    THERMOCOUPLE, READINGS_NUMBER, DELAY_TIME
  );

  Where,
  THERMOCOUPLE - origin Thermocouple instance.

  READINGS_NUMBER - How many readings are taken
  to determine a mean temperature. The more values,
  the longer a calibration is performed, but the readings
  will be more accurate.

  DELAY_TIME - Delay time between a temperature readings
  from the temperature sensor (ms).

  Read temperature:
  double celsius = thermocouple->readCelsius();
  double kelvin = thermocouple->readKelvin();
  double fahrenheit = thermocouple->readFahrenheit();

  v.2.0.0
  - created

  v.2.0.1
  - optimized average(*) method;
  - renamed default constants;
  - added default value of constructor parameters;
  - updated documentation.

  v.2.0.2
  - replaced "define" constants with "static const"

  https://github.com/YuriiSalimov/MAX6675_Thermocouple

  Created by Yurii Salimov, May, 2019.
  Released into the public domain.
*/
#ifndef AVERAGE_THERMOCOUPLE_H
#define AVERAGE_THERMOCOUPLE_H

#include "Thermocouple.h"

class AverageThermocouple final : public Thermocouple {

  private:
    // Default number of average readings.
    static const int DEFAULT_READINGS_NUMBER = 10;
    // Default delay time of average readings.
    static const int DEFAULT_DELAY_TIME = 1;

    Thermocouple* origin;
    int readingsNumber;
    int delayTime;

  public:
    /**
      Constructor

      @param origin - origin Thermocouple instance (not NULL)
      @param readingsNumber - average readings number (default, 10)
      @param delayTimeInMillis - average delay time in milliseconds (default, 1 ms)
    */
    AverageThermocouple(
      Thermocouple* origin,
      int readingsNumber = DEFAULT_READINGS_NUMBER,
      int delayTimeInMillis = DEFAULT_DELAY_TIME
    );

    /**
      Destructor
      Deletes the origin Thermocouple instance.
    */
    ~AverageThermocouple();

    /**
      Reads a temperature in Celsius from the thermocouple.

      @return average temperature in degree Celsius
    */
    double readCelsius() override;

    /**
      Reads a temperature in Kelvin from the thermocouple.

      @return average temperature in degree Kelvin
    */
    double readKelvin() override;

    /**
      Reads a temperature in Fahrenheit from the thermocouple.

      @return average temperature in degree Fahrenheit
    */
    double readFahrenheit() override;

  private:
    /**
      Reads the temperature from the "*read()" method
      "readingsNumber" times with delay "delayTimeInMillis".
      Returns the average value.

      @param *read - origin method that return temperature (not NULL)
      @return average temperature from the input *read() method
    */
    inline double average(double (Thermocouple::*read)());

    /**
      For delay between readings.
    */
    inline void sleep();

    /**
      Validates the input data.

      @param data - value to validate
      @param alternative - alternative value to return
      @returns the data if it is valid (> 0),
      otherwise returns alternative data.
    */
    template <typename A, typename B>
    inline A validate(A data, B alternative);
};

#endif
