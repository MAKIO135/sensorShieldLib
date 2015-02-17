/*
 Lionel Radisson @Makio135
 O2/2015
*/

#include <sensorShieldLib.h>

SensorShield board;

void setup()
{
    board.init(); // always needed first, initialises and start Serial with 9600 baudrate

    // you can set digital/analog pins ranges if working with a board different from Arduino UNO configuration
    // example with arduino MEGA:
    // board.setDigitalPinsRange( 2, 53 ); //digital pins 0 & 1 are required for Serial Communication
    // board.setAnalogPinsRange( A0, A15 );

    // add analog/digital sensors, 
    board.addSensor( "btn1", 2 );
    board.addSensor( "btn2", 8, INPUT_PULLUP );
    board.addSensor( "pot1", A0 );

    // set minimal change on analog sensors 
    board.setAnalogSensitivity( 10 );

    // connect a led that will lightup when sending JSON
    board.emitLightOnChange( 13 );
}

void loop()
{
    board.update(); 
    // checks if any sensor changed 
    // if so, sends a JSON with all sensors and their value:
    // {"btn1":1,"btn2":0,"pot1":768}
}
