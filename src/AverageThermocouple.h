/**
  AverageThermocoupler.h - class-wrapper allows to average
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

  https://github.com/YuriiSalimov/MAX6675_Thermocouple

  Created by Yurii Salimov, May, 2019.
  Released into the public domain.
*/
#ifndef AVERAGE_THERMOCOUPLE_H
#define AVERAGE_THERMOCOUPLE_H

#include "Thermocouple.h"

// Default number of average readings.
#define NTC_AVERAGE_READINGS_NUMBER	10
// Default delay time of average readings.
#define NTC_AVERAGE_DELAY_TIME	1

class AverageThermocouple final : public Thermocouple {

  private:
    Thermocouple* origin;
    int readingsNumber;
    int delayTime;

  public:
    /**
      Constructor

      @param origin - origin Thermocouple instance.
      @param readingsNumber - average readings number
      @param delayTimeInMillis - average delay time (in milliseconds)
    */
    AverageThermocouple(
      Thermocouple* origin,
      int readingsNumber,
      int delayTimeInMillis
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

      @param *read - origin method that return temperature
      @param thermocouple - origin Thermocouple instance
      @return average temperature from the input *read() method
    */
    double average(
      double (Thermocouple::*read)(),
      Thermocouple* thermocouple
    );

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
    template <typename A, typename B> A validate(A data, B alternative);
};

#endif
