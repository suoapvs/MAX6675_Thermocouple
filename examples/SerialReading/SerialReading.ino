/*
  Average Thermocouple

  Reads a temperature from a thermocouple based
  on the MAX6675 driver and displays it in the default Serial.

  https://github.com/YuriiSalimov/MAX6675_Thermocouple

  Created by Yurii Salimov, May, 2019.
  Released into the public domain.
*/
#include <Thermocouple.h>
#include <MAX6675_Thermocouple.h>

#define SCK_PIN 3
#define CS_PIN 4
#define SO_PIN 5

Thermocouple* thermocouple;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  thermocouple = new MAX6675_Thermocouple(SCK_PIN, CS_PIN, SO_PIN);
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

  delay(500); // optionally, only to delay the output of information in the example.
}
