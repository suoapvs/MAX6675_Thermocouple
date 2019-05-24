/**
  SmoothThermocouple.h - class-wrapper allows to smooth
  the temperature value of origin Thermocouple instance.

  Instantiation:
  Thermocouple* thermocouple = new SmoothThermocouple(
    THERMOCOUPLE, SMOOTH_FACTOR
  );

  Where,
  THERMOCOUPLE - origin Thermocouple instance.
  SMOOTH_FACTOR - smoothing factor of a temperature value.

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
#ifndef SMOOTH_THERMOCOUPLE_H
#define SMOOTH_THERMOCOUPLE_H

#include "Thermocouple.h"

class SmoothThermocouple final : public Thermocouple {

  private:
    Thermocouple* origin;
    int factor;
    double celsius = 0;
    double kelvin = 0;
    double fahrenheit = 0;

  public:
    /**
      Constructor

      @param origin - origin Thermocouple instance.
      @param factor - smoothing factor of a temperature value
    */
    SmoothThermocouple(Thermocouple* origin, int factor);

    /**
      Destructor
      Deletes the origin Thermocouple instance.
    */
    ~SmoothThermocouple();

    /**
      Reads a temperature in Celsius from the thermocouple.

      @return average temperature in degree Celsius
    */
    double readCelsius() override;

    /**
      Reads a temperature in Kelvin from the thermocouple.

      @return smoothed temperature in degree Kelvin
    */
    double readKelvin() override;

    /**
      Reads a temperature in Fahrenheit from the thermocouple.

      @return smoothed temperature in degree Fahrenheit
    */
    double readFahrenheit() override;

  private:
    /**
      Perform smoothing of the input value.

      @param input - the value to smooth
      @param data - the data for smoothing of the input value
      @return smoothed value or the input value
      if the smooth factor is less than 1 or the input data is 0.
    */
    double smoothe(double input, double data);
};

#endif
