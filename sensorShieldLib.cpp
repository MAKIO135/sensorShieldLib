#include "Arduino.h"
#include "sensorShieldLib.h"

SensorShield::SensorShield(){}

void SensorShield::initialize()
{
	digitalPinMin = 2;
	digitalPinMax = 12;
	analogPinMin = A0;
	analogPinMax = A5;

	analogSensitivity = 1;
	
	nbSensors = 0;

	Serial.begin( 9600 );
	Serial.println( "Hello SensorShield!" );

	pinMode( 13, OUTPUT );
	digitalWrite( 13, HIGH );
	delay( 100 );
	digitalWrite( 13, LOW );
}

void SensorShield::setDigitalPinsRange( int pinMin, int pinMax )
{
	digitalPinMin = pinMin;
	digitalPinMax = pinMax;
}

void SensorShield::setAnalogPinsRange( int pinMin, int pinMax )
{
	analogPinMin = pinMin;
	analogPinMax = pinMax;
}

void SensorShield::setAnalogSensitivity( int sensitivity )
{
	analogSensitivity = sensitivity;
}

void SensorShield::addSensor( String name, int pin, int mode = INPUT )
{
	if( ( pin >= digitalPinMin && pin <= digitalPinMax ) 
		|| ( pin >= analogPinMin && pin <= analogPinMax ) ) {
		sensors[ nbSensors ].name = name;
		sensors[ nbSensors ].pin = pin;
		sensors[ nbSensors ].value = 0;

		if( pin >= digitalPinMin && pin <= digitalPinMax ) {
			sensors[ nbSensors ].isDigital = true;

			if( mode == INPUT_PULLUP) {
				sensors[ nbSensors ].isInputPullUp = true;
			}
			else {	
				sensors[ nbSensors ].isInputPullUp = false;
			}

			pinMode( pin, mode );
		}
		else {
			sensors[ nbSensors ].isDigital = false;
			sensors[ nbSensors ].isInputPullUp = false;
		}
		nbSensors++;
	} 
}

void SensorShield::update()
{
	hasNewValue = false;

	for (int i = 0; i < nbSensors; ++i) {
		if( sensors[ i ].isDigital == true ) {
			int tmpValue;
			if( sensors[ i ].isInputPullUp == true ) {
				tmpValue = 1 - digitalRead( sensors[ i ].pin );
			}
			else {	
				tmpValue = digitalRead( sensors[ i ].pin );
			}

			if( sensors[ i ].value != tmpValue ) {
				sensors[ i ].value = tmpValue;
				hasNewValue = true;
			}
		}
		else {
			int tmpValue = analogRead( sensors[ i ].pin );
			if( abs( sensors[ i ].value - tmpValue ) > analogSensitivity ) {
				sensors[ i ].value = tmpValue;
				hasNewValue = true;
			}
		}
	}
	
	if( hasNewValue == true) sendMessage();
}

void SensorShield::sendMessage()
{
	String json = "{";
	for (int i = 0; i < nbSensors; ++i) {
		if( i != 0) json += ",";
		json += "\"" + sensors[ i ].name + "\":" + sensors[ i ].value;
	}
	json += "}";
	Serial.println( json );

	digitalWrite( 13, HIGH );
	delay( 50 );
	digitalWrite( 13, LOW );
}
