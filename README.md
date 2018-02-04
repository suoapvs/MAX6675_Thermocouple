# MAX6675 Thermocouple Library

For Arduino boards.

The Library implements a set of methods for working with a thermocouple based on the MAX6675 driver.
Provides a temperature reading in Celsius, Fahrenheit and Kelvin.

## Installation

1. [Download](https://github.com/YuriiSalimov/MAX6675_Thermocouple/releases) the Latest release from gitHub.
2. Unzip and modify the Folder name to "MAX6675_Thermocouple" (Remove the '-version')
3. Paste the modified folder on your Library folder 
(On your `libraries` folder inside Sketchbooks or Arduino software).
4. Restart the Arduino IDE.

## Circuit Diagram

![Circuit Diagram](CircuitDiagram.png)

## Methods

```
    /**
        SCK_PIN - SCK digital port number.
        CS_PIN - CS digital port number.
        SO_PIN - SO digital port number.
    */
    MAX6675_Thermocouple thermocouple(SCK_PIN, CS_PIN, SO_PIN);
    
    // Read a temperature in Celsius.
    thermocouple.readCelsius();
    
    // Read a temperature in Kelvin.
    thermocouple.readKelvin();
	
    // Read a temperature in Fahrenheit.
    thermocouple.readFahrenheit();
    // For older devices.
    thermocouple.readFarenheit();
```

Created by Yurii Salimov.
