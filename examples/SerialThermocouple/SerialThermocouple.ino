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

void setup() {
  Serial.begin(9600);
  thermocouple = new MAX6675_Thermocouple(SCK_PIN, CS_PIN, SO_PIN);
}

void loop() {
  Serial.print("Temperature: ");
  Serial.print(String(thermocouple->readCelsius()) + " C, ");
  Serial.print(String(thermocouple->readFahrenheit()) + " F, ");
  Serial.println(String(thermocouple->readKelvin()) + " K");
  delay(1000);
}

