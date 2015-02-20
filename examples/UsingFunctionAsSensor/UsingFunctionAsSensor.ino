/*
 SensorShieldlib
 Lionel Radisson - @Makio135
 ***************************

 Example for using Function as Sensor
 ************************************
 void SensorShield::addSensor( String sensorID, int( *custFunction )() );
 void SensorShield::addSensor( String sensorID, float( *custFunction )() );

 .you can use a custom function as a sensor
 .the custom function must return a float or an int
*/

#include <sensorShieldLib.h>

SensorShield board;

int secondsPassed() {
  return millis() / 1000 ;
}

void setup() {
  board.init();
  board.addSensor("seconds", secondsPassed);
}

void loop() {
  board.update(); // {"seconds":15}
}