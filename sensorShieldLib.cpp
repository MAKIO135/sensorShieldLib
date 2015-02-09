#include "Arduino.h"
#include "HardwareSerial.h"
#include "sensorShieldLib.h"

SensorShield::SensorShield(){}

void SensorShield::initialize(int ledPin )
{
	Serial.begin( 9600 );
	SensorShieldStream = &Serial;
	SensorShieldStream->println( "{\"hello\":\"Hello SensorShield!\"}" );
	
	indicatorLedPin = ledPin;

	initValues();
}

void SensorShield::initialize(Stream &stream, int ledPin )
{
	SensorShieldStream = &stream;
	SensorShieldStream->println( "{\"hello\":\"Hello SensorShield!\"}" );
	
	indicatorLedPin = ledPin;

	initValues();
}

void SensorShield::initValues(){
	digitalPinMin = 2;
	digitalPinMax = 12;
	analogPinMin = A0;
	analogPinMax = A5;
	
	nbSensors = 0;

	pinMode( indicatorLedPin, OUTPUT );
	digitalWrite( indicatorLedPin, HIGH );
	delay( 100 );
	digitalWrite( indicatorLedPin, LOW );
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
	for (int i = 0; i < nbSensors; ++i) {
		if( sensors[ i ].isDigital == false ) {
			sensors[ i ].analogSensitivity = sensitivity;
		}
	}
}

void SensorShield::setAnalogSensitivity( String sensorName, int sensitivity )
{
	for (int i = 0; i < nbSensors; ++i) {
		if( sensors[ i ].name == sensorName ) {
			sensors[ i ].analogSensitivity = sensitivity;
			return;
		}
	}
}

void SensorShield::setAnalogLimits( int min, int max )
{
	for (int i = 0; i < nbSensors; ++i) {
		if( sensors[ i ].isDigital == false ) {
			sensors[ i ].min = min;
			sensors[ i ].max = max;
		}
	}
}

void SensorShield::setAnalogLimits( String sensorName, int min, int max )
{
	for (int i = 0; i < nbSensors; ++i) {
		if( sensors[ i ].name == sensorName ) {
			sensors[ i ].min = min;
			sensors[ i ].max = max;
			return;
		}
	}
}

void SensorShield::addSensor( String name, int pin )
{
	if( ( pin >= digitalPinMin && pin <= digitalPinMax ) 
		|| ( pin >= analogPinMin && pin <= analogPinMax ) ) {

		sensors[ nbSensors ].name = name;
		sensors[ nbSensors ].pin = pin;
		sensors[ nbSensors ].value = 0;

		if( pin >= digitalPinMin && pin <= digitalPinMax ) {
			addDigitalSensor( pin, INPUT );
		}
		else {
			addAnalogSensor();
		}

		nbSensors++;
	} 
}

void SensorShield::addSensor( String name, int pin, int mode )
{
	if( ( pin >= digitalPinMin && pin <= digitalPinMax ) 
		|| ( pin >= analogPinMin && pin <= analogPinMax ) ) {

		sensors[ nbSensors ].name = name;
		sensors[ nbSensors ].pin = pin;
		sensors[ nbSensors ].value = 0;

		if( pin >= digitalPinMin && pin <= digitalPinMax ) {
			addDigitalSensor( pin, mode );
		}
		else {
			addAnalogSensor();
		}
		nbSensors++;
	} 
}

void SensorShield::addDigitalSensor( int pin, int mode )
{
	sensors[ nbSensors ].isDigital = true;

	if( mode == INPUT_PULLUP) {
		sensors[ nbSensors ].isInputPullUp = true;
	}
	else {	
		sensors[ nbSensors ].isInputPullUp = false;
	}

	pinMode( pin, mode );
}

void SensorShield::addAnalogSensor()
{
	sensors[ nbSensors ].isDigital = false;
	sensors[ nbSensors ].isInputPullUp = false;
	sensors[ nbSensors ].analogSensitivity = 1;
	sensors[ nbSensors ].min = 0;
	sensors[ nbSensors ].max = 1023;
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
			if( abs( sensors[ i ].value - tmpValue ) > sensors[ i ].analogSensitivity ) {
				sensors[ i ].value = tmpValue;
				
				if( sensors[ i ].value >= sensors[ i ].min && sensors[ i ].value <= sensors[ i ].max ){
					hasNewValue = true;
				}
			}
		}
	}
	
	if( hasNewValue == true){
		sendMessage();
	}
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

	digitalWrite( indicatorLedPin, HIGH );
	delay( 50 );
	digitalWrite( indicatorLedPin, LOW );
}