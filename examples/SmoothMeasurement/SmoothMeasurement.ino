/*
  Smooth MAX6675 Thermocouple

  Reads a temperature from the MAX6675 thermocouple,
  smooth and displays it in the default Serial.

  https://github.com/YuriiSalimov/MAX6675_Thermocouple

  Created by Yurii Salimov, May, 2019.
  Released into the public domain.
*/
#include <Thermocouple.h>
#include <MAX6675_Thermocouple.h>
#include <SmoothThermocouple.h>

#define SCK_PIN 3
#define CS_PIN  4
#define SO_PIN  5

/**
  How many readings are taken to determine a mean temperature.
  The more values, the longer a calibration is performed,
  but the readings will be more accurate.
*/
#define SMOOTH_FACTOR 5

Thermocouple* thermocouple = NULL;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  thermocouple = new SmoothThermocouple(
    new MAX6675_Thermocouple(SCK_PIN, CS_PIN, SO_PIN),
    SMOOTH_FACTOR
  );
}

// the loop function runs over and over again forever
void loop() {
  // Reads temperature
  const double celsius = thermocouple->readCelsius();
  const double kelvin = thermocouple->readKelvin();
  const double fahrenheit = thermocouple->readFahrenheit();

  // Output of information
  Serial.print("Temperature: ");
  Serial.print(celsius);
  Serial.print(" C, ");
  Serial.print(kelvin);
  Serial.print(" K, ");
  Serial.print(fahrenheit);
  Serial.println(" F");

  delay(500); // To delay the output of information.
}
