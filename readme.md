#SensorShieldLib  
A simple library for your custom sensorShields
___

![SensorShield](SensorShield.jpg)

This lib tends to communicate sensors values from your board in JSON format.  
___
###Features
- a SensorShield class ```SensorShield board;```
- simple initialisation ```board.init()```
- suport different Stream ```Serial.begin(9600); board.init(Serial);```
- set your digital/analog pins ranges ( lib is configured by default for UNO )
- easy sensor attach with auto recognition for analog/digital read ```board.addSensor("btn1", 2); board.addSensor("pot1", A0);```
- support INPUT\_PULLUP pinMode ```board.addSensor("btn2", 8, INPUT\_PULLUP)```
- set analog sensitivity ie minimun change on analog captor for sending JSON for all analog sensors ```board.setAnalogSensititvity(5)```
- or set analog sensitivity for a particular analog sensor ```board.setAnalogSensitivity("pot1", 10);```
- reads all digital/analog sensors on update and automatically send JSON on changes ```board.update()```

___
###Example:

![Example](SensorShieldLib.png)

```
#include <sensorShieldLib.h>

SensorShield board;

void setup()
{
	board.initialize();
	
	//board.setDigitalPinsRange( 2, 12 );
	//board.setAnalogPinsRange( A0, A5 );
 
	//board.setAnalogSensitivity(2);
 	
	board.addSensor( "btn1", 2 );

	board.addSensor( "btn2", 8, INPUT_PULLUP );

	board.addSensor( "pot1", A0 );
}

void loop()
{
	board.update();
}
```

Serial will print JSON like `{"btn1":1,"btn2":0,"pot1":768}`

___
###Coming soon
- Support for ethernetShield compatibility
- examples
