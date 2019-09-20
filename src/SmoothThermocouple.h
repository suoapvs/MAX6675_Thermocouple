/**
  SmoothThermocouple - class-wrapper allows to smooth
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

  v.2.0.1
  - optimized smoothe(*) method;
  - added default constant for the smoothing factor;
  - added default value of constructor parameters;
  - updated documentation.

  v.2.0.2
  - replaced "define" constants with "static const"

  https://github.com/YuriiSalimov/MAX6675_Thermocouple

  Created by Yurii Salimov, May, 2019.
  Released into the public domain.
*/
#ifndef SMOOTH_THERMOCOUPLE_H
#define SMOOTH_THERMOCOUPLE_H

#include "Thermocouple.h"

class SmoothThermocouple final : public Thermocouple {

  private:
    // Minimum smoothing factor.
    static const int MIN_SMOOTHING_FACTOR = 2;

    Thermocouple* origin;
    int smoothingFactor;
    double celsius = 0;
    double kelvin = 0;
    double fahrenheit = 0;

  public:
    /**
      Constructor

      @param origin - origin Thermocouple instance.
      @param smoothingFactor - smoothing factor of a temperature value
    */
    SmoothThermocouple(
      Thermocouple* origin,
      int smoothingFactor = MIN_SMOOTHING_FACTOR
    );

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
      if the input data is 0.
    */
    inline double smoothe(double input, double data);

    /**
      Sets the smoothing factor.
      If the input value is less than THERMOCOUPLE_MIN_SMOOTHING_FACTOR,
      then sets THERMOCOUPLE_MIN_SMOOTHING_FACTOR.

      @param smoothingFactor - new smoothing factor
    */
    inline void setSmoothingFactor(int smoothingFactor);
};

#endif
