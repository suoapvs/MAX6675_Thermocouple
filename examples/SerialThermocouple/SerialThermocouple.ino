/*
  Thermocouple.

  Reads a temperature from a thermocouple based
  on the MAX6675 driver and displays it in the default Serial.

	https://github.com/YuriiSalimov/MAX6675_Thermocouple

	Created by Yurii Salimov, February, 2018.
	Released into the public domain.
*/
#include <MAX6675_Thermocouple.h>

#define SCK_PIN 3
#define CS_PIN  4
#define SO_PIN  5

MAX6675_Thermocouple* thermocouple = NULL;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  thermocouple = new MAX6675_Thermocouple(SCK_PIN, CS_PIN, SO_PIN);
}

// the loop function runs over and over again forever
void loop() {
  const double celsius = thermocouple->readCelsius();
  const double kelvin = thermocouple->readKelvin();
  const double fahrenheit = thermocouple->readFahrenheit();
  Serial.print("Temperature: ");
  Serial.print(String(celsius) + " C, ");
  Serial.print(String(kelvin) + " K, ");
  Serial.println(String(fahrenheit) + " F");
  delay(500);
}

