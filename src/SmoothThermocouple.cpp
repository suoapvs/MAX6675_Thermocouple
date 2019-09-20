/**
  Created by Yurii Salimov, May, 2019.
  Released into the public domain.
*/
#include "SmoothThermocouple.h"

SmoothThermocouple::SmoothThermocouple(
  Thermocouple* origin,
  const int smoothingFactor
) {
  this->origin = origin;
  setSmoothingFactor(smoothingFactor);
}

SmoothThermocouple::~SmoothThermocouple() {
  delete this->origin;
}

double SmoothThermocouple::readCelsius() {
  return this->celsius = smoothe(
    this->origin->readCelsius(),
    this->celsius
  );
}

double SmoothThermocouple::readKelvin() {
  return this->kelvin = smoothe(
    this->origin->readKelvin(),
    this->kelvin
  );
}

double SmoothThermocouple::readFahrenheit() {
  return this->fahrenheit = smoothe(
    this->origin->readFahrenheit(),
    this->fahrenheit
  );
}

double SmoothThermocouple::smoothe(
  const double input, const double data
) {
  return (data == 0) ? input :
    ((data * (this->smoothingFactor - 1) + input) / this->smoothingFactor);
}

/**
  See about the max(*) function:
  https://www.arduino.cc/reference/en/language/functions/math/max/
*/
inline void SmoothThermocouple::setSmoothingFactor(const int smoothingFactor) {
  this->smoothingFactor = max(smoothingFactor, MIN_SMOOTHING_FACTOR);
}
