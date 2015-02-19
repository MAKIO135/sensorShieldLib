/*
 Lionel Radisson @Makio135
 O2/2015
*/

#include <sensorShieldLib.h>

SensorShield board;

// sensor functions can be of type int or float and takes one parameter: the value read on sensor's pin (here A0)
// it does not modify the value of the sensor, but replaces it in output JSON
float computeTemp( int sensorValue ){
    float voltage = ( sensorValue / 1023.0 ) * 5.0;
    float temp = voltage * 100.0;
    return temp;
}

void setup(){
    board.init();

    board.addSensor( "LM35", A0 );
    board.setSensorSensitivity( 3 );
    board.setSensorFunction( "LM35", computeTemp );
}

void loop(){
    board.update(); // {"LM35":22.93}
}