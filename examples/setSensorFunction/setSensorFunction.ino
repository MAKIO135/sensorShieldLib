/*
 SensorShieldlib
 Lionel Radisson - @Makio135
 ***************************

 Example for setSensorProcess method
 ************************************
 void SensorShield::setSensorProcess( String sensorID, int( *custFunction )( int ) );
 void SensorShield::setSensorProcess( String sensorID, float( *custFunction )( int ) );

 .setSensorProcess allows to compute sensors value instead of only reading pin value
 .setSensorProcess takes two parameters: a sensorID (a String), and a custom function (a pointer to a function)
 .the custom function must:
     return a float or an int,
     have an int as parameter that is the value of the sensor read from its pin (0-1 for digital pins / 0-1023 for analog pins)
*/

#include <sensorShieldLib.h>

SensorShield board;

float convertToCelsius( int value ){ //value parameter is the value of the sensor read from its pin
    float voltage = ( value / 1023.0 ) * 5.0;
    float temperature = ( voltage - 0.5 ) * 100.0;
    return temperature;
}

void setup() {
  board.init(); // initialize sensorShield

  board.addSensor("tmp36", A0); // add a sensor
  board.setSensorProcess( "tmp36", convertToCelsius ); // set a custom function for "tmp36" sensor
  board.setSensorSensitivity( "tmp36", 0.6 ); // sensitivity will be applied to computed temperature in Celsius
}

void loop() {
    board.update(); // {"tmp36":23.45}
}