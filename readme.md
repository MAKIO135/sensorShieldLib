#SensorShieldLib  
This lib tends to communicate sensors values from your custom boards in JSON format.  
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
- a SensorShield class: `SensorShield board;`

- simple initialisation: `board.init();`
- support initialisation with different Stream: `Serial.begin( 115200 ); board.init( Serial );`

- set your digital/analog pins ranges ( lib is configured by default for UNO ): `board.setDigitalPinsRange( 5, 10 );`

- easy sensor attach with auto recognition for analog/digital read: `board.addSensor( "btn1", 2 ); board.addSensor( "pot1", A0 );`
- support INPUT\_PULLUP pinMode for digital sensors: `board.addSensor( "btn2", 8, INPUT\_PULLUP );`

- set analog sensitivity (ie minimun change on analog captor for sending JSON) for a particular sensor: `board.setSensorSensitivity( "pot1", 10 );`
- set limit values of interest for a particular sensor: `board.setSensorLimits( "pot1", 150, 850 );`

- reads all digital/analog sensors on update and automatically send JSON on changes: `board.update();`

- possibility to add a visual signal when sending JSON with a led: `board.emitlightOnChange( 13 );`

- public access to boolean hasNewValue: `if( board.hasNewValue == true ) { ...... }`
- public access to String JSONMessage: `String s = board.JSONMessage;`

___
###Coming soon
- example with addSensor(sensorID, sensorFunction);
- proprer documentation