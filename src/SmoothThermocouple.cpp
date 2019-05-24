/**
  Created by Yurii Salimov, May, 2019.
  Released into the public domain.
*/
#include "SmoothThermocouple.h"

SmoothThermocouple::SmoothThermocouple(
  Thermocouple* origin,
  const int factor
) {
  this->origin = origin;
  this->factor = factor;
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
  return (this->factor > 1) && (data != 0) ?
    (data * (this->factor - 1) + input) / this->factor :
    input;
}
