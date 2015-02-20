#SensorShieldLib  
Easilly communicate sensors value in JSON.  
___
![SensorShield](SensorShield.jpg)

___
###Example:

![Example](examples/SensorShield101/SensorShieldLib.png)

```
#include <sensorShieldLib.h>

SensorShield board;

void setup()
{
	board.init(); // initialises and starts Serial

	board.addSensor( "btn1", 2 );
	board.addSensor( "btn2", 8, INPUT_PULLUP );
	board.addSensor( "pot1", A0 );
}

void loop()
{
	board.update();
}
```
On `board.update();`, the lib checks sensors values and if any changed from previous `loop`, outputs JSON on Serial 9600 bds: `{"btn1":1,"btn2":0,"pot1":768}`

___
###Features
- A SensorShield class:
```
SensorShield board;
```
- Simple initialisation:
```
	board.init();
```
- Support initialisation with different Stream:
```
	Serial.begin( 115200 );
	board.init( Serial );
```
- Set your digital/analog pins ranges ( lib is configured by default for UNO ):
```
	board.setDigitalPinsRange( 2, 53 );
	board.setAnalogPinsRange( A0, A15 );
```
- Easy sensor attach with auto recognition for analog/digital read:
```
	board.addSensor( "btn1", 2 );
	board.addSensor( "pot1", A0 );
```
- Support INPUT\_PULLUP pinMode for digital sensors:
```
	board.addSensor( "btn2", 8, INPUT\_PULLUP );
```
- Use an int or float function as a sensor:
```
int secondsPassed(){
	return millis()/1000 ;
}
	...
	board.addSensor("seconds", secondsPassed);
```
- Link a function with a sensor to compute its value instead of only reading its pin:
```
float multBy2( int value ){
	return value * 2;
}
...
	board.setSensorFunction( "pot1", multBy2 );
```
- Set minimun change needed on sensor value before updating its value and sending JSON:
```
	board.setSensorSensitivity( "pot1", 10 );
```
- Set limit values of interest for a particular sensor:
```
	board.setSensorLimits( "pot1", 150, 850 );
```
- Possibility to add a visual signal when sending JSON with a led:
```
	board.emitlightOnChange( 13 );
```
- Reads all digital/analog sensors on update and automatically send JSON on changes:
```
void loop(){
	board.update();
}
```
- Public access to boolean hasNewValue:
```
	if( board.hasNewValue == true ) { ...... }
```
- Public access to String JSONMessage:
```
	String s = board.JSONMessage;
```
