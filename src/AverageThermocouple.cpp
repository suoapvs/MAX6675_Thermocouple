/**
  Created by Yurii Salimov, May, 2019.
  Released into the public domain.
*/
#include "AverageThermocouple.h"

AverageThermocouple::AverageThermocouple(
  Thermocouple* origin,
  const int readingsNumber,
  const int delayTimeInMillis
) {
  this->origin = origin;
  this->readingsNumber = validate(readingsNumber, DEFAULT_READINGS_NUMBER);
  this->delayTime = validate(delayTimeInMillis, DEFAULT_DELAY_TIME);
}

AverageThermocouple::~AverageThermocouple() {
  delete this->origin;
}

double AverageThermocouple::readCelsius() {
  return average(&Thermocouple::readCelsius);
}

double AverageThermocouple::readKelvin() {
return average(&Thermocouple::readKelvin);
}

double AverageThermocouple::readFahrenheit() {
  return average(&Thermocouple::readFahrenheit);
}

inline double AverageThermocouple::average(double (Thermocouple::*read)()) {
  double sum = 0;
  for (int i = 0; i < this->readingsNumber; ++i) {
    sum += (this->origin->*read)();
    sleep();
  }
  return (sum / this->readingsNumber);
}

inline void AverageThermocouple::sleep() {
  delay(this->delayTime);
}

template <typename A, typename B>
inline A AverageThermocouple::validate(A data, B alternative) {
  return (data > 0) ? data : alternative;
}
