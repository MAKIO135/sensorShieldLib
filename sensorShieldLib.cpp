#include "Arduino.h"
#include "HardwareSerial.h"
#include "sensorShieldLib.h"

SensorShield::SensorShield(){}

/////////////////////////////////////////////////////////////////////
void SensorShield::init()
{
	// default SensorShieldStream to Serial, 9600 baudrate
	Serial.begin( 9600 );
	init( Serial );
}

void SensorShield::init( Stream &stream )
{
	SensorShieldStream = &stream;
	initValues();
}

void SensorShield::initValues()
{
	// default values for Arduino UNO
	digitalPinMin = 2;
	digitalPinMax = 13;
	analogPinMin = A0;
	analogPinMax = A5;
	nbSensors = 0;
	sensitivity = 1;
	analogMin = 0;
	analogMax = 1023;
	indicatorLedPin = NULL;
	turnLightOn = false;
}

/////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////
void SensorShield::addSensor( String sensorID, int pin )
{
	addSensor( sensorID, pin, INPUT );
}

void SensorShield::addSensor( String sensorID, int pin, int pinmode )
{
	if( ( pin >= digitalPinMin && pin <= digitalPinMax ) 
		|| ( pin >= analogPinMin && pin <= analogPinMax ) ) {

		sensors[ nbSensors ].sensorID = sensorID;
		sensors[ nbSensors ].pin = pin;
		sensors[ nbSensors ].value = 0;
		sensors[ nbSensors ].fValue = 0;
		sensors[ nbSensors ].sensitivity = sensitivity;
		sensors[ nbSensors ].type = SIMPLE;

		if( pin >= digitalPinMin && pin <= digitalPinMax ) {
			addDigitalSensor( pin, pinmode );
		}
		else {
			addAnalogSensor();
		}

		nbSensors++;
	} 
}

void SensorShield::addDigitalSensor( int pin, int pinmode )
{
	sensors[ nbSensors ].isDigital = true;

	if( pinmode == INPUT_PULLUP) {
		sensors[ nbSensors ].invertValue = true;
	}
	else {	
		sensors[ nbSensors ].invertValue = false;
	}

	pinMode( pin, pinmode );
}

void SensorShield::addAnalogSensor()
{
	sensors[ nbSensors ].isDigital = false;
	sensors[ nbSensors ].invertValue = false;
	sensors[ nbSensors ].min = analogMin;
	sensors[ nbSensors ].max = analogMax;
}

/////////////////////////////////////////////////////////////////////
void SensorShield::addSensor( String sensorID, int( *custFunction )() )
{
	sensors[ nbSensors ].sensorID = sensorID;
	sensors[ nbSensors ].value = 0;
	sensors[ nbSensors ].sensitivity = sensitivity;
	sensors[ nbSensors ].type = INT_FUNCTION;
	sensors[ nbSensors ].customSensorInt = custFunction;
	nbSensors++;
}

void SensorShield::addSensor( String sensorID, float( *custFunction )() )
{
	sensors[ nbSensors ].sensorID = sensorID;
	sensors[ nbSensors ].fValue = 0;
	sensors[ nbSensors ].sensitivity = sensitivity;
	sensors[ nbSensors ].type = FLOAT_FUNCTION;
	sensors[ nbSensors ].customSensorFloat = custFunction;
	nbSensors++;
}

/////////////////////////////////////////////////////////////////////
void SensorShield::setSensorSensitivity( float _sensitivity )
{
	sensitivity = _sensitivity;
	for (int i = 0; i < nbSensors; ++i) {
		if( sensors[ i ].isDigital == false ) {
			sensors[ i ].sensitivity = _sensitivity;
		}
	}
}

void SensorShield::setSensorSensitivity( String sensorID, float _sensitivity )
{
	for (int i = 0; i < nbSensors; ++i) {
		if( sensors[ i ].sensorID == sensorID ) {
			sensors[ i ].sensitivity = _sensitivity;
			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////
void SensorShield::invertSensorValue( String sensorID )
{
	for (int i = 0; i < nbSensors; ++i) {
		if( sensors[ i ].sensorID == sensorID ) {
			sensors[ i ].invertValue = true;
			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////
void SensorShield::setSensorLimits( int min, int max )
{
	analogMin = min;
	analogMax = max;
	for (int i = 0; i < nbSensors; ++i) {
		if( sensors[ i ].isDigital == false ) {
			sensors[ i ].min = min;
			sensors[ i ].max = max;
		}
	}
}

void SensorShield::setSensorLimits( String sensorID, int min, int max )
{
	for (int i = 0; i < nbSensors; ++i) {
		if( sensors[ i ].sensorID == sensorID ) {
			sensors[ i ].min = min;
			sensors[ i ].max = max;
			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////
void SensorShield::setSensorProcess( String sensorID, int( *custFunction )( int ) )
{
	for (int i = 0; i < nbSensors; ++i) {
		if( sensors[ i ].sensorID == sensorID ) {
			sensors[ i ].type = INT_PROCESS_VALUE;
			sensors[ i ].customInt = custFunction;
			return;
		}
	}
}

void SensorShield::setSensorProcess( String sensorID, float( *custFunction )( int ) )
{
	for (int i = 0; i < nbSensors; ++i) {
		if( sensors[ i ].sensorID == sensorID ) {
			sensors[ i ].type = FLOAT_PROCESS_VALUE;
			sensors[ i ].customFloat = custFunction;
			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////
void SensorShield::emitLightOnChange( int ledPin )
{
	indicatorLedPin = ledPin;
	pinMode( indicatorLedPin, OUTPUT );
	turnLightOn = true;
	lightup();
}

void SensorShield::emitLightOnChange( bool _turnLightOn )
{
	turnLightOn = _turnLightOn;
}

void SensorShield::lightup()
{
	digitalWrite( indicatorLedPin, HIGH );
	delay( 50 );
	digitalWrite( indicatorLedPin, LOW );
}

/////////////////////////////////////////////////////////////////////
void SensorShield::update()
{
	hasNewValue = false;
	int tmpValue;
	float fTmpValue;

	for (int i = 0; i < nbSensors; ++i) {
		switch( sensors[ i ].type ){
			case SIMPLE :
				if( sensors[ i ].isDigital == true ) {
					if( sensors[ i ].invertValue == true ) {
						tmpValue = 1 - digitalRead( sensors[ i ].pin );
					}
					else {
						tmpValue = digitalRead( sensors[ i ].pin );
					}

					if( abs( sensors[ i ].value - tmpValue ) >= sensors[ i ].sensitivity ) {
						sensors[ i ].value = tmpValue;
						hasNewValue = true;
					}
				}
				else {
					if( sensors[ i ].invertValue == true ) {
						tmpValue = 1023 - analogRead( sensors[ i ].pin );
					}
					else {	
						tmpValue = analogRead( sensors[ i ].pin );
					}

					if( abs( sensors[ i ].value - tmpValue ) >= sensors[ i ].sensitivity ) {
						sensors[ i ].value = tmpValue;
						
						if( sensors[ i ].value >= sensors[ i ].min && sensors[ i ].value <= sensors[ i ].max ) {
							hasNewValue = true;
						}
					}
				}
				break;

			case INT_PROCESS_VALUE :
				if( sensors[ i ].isDigital == true ) {
					tmpValue = digitalRead( sensors[ i ].pin );
					tmpValue = ( *(sensors[i].customInt) )( tmpValue );

					if( abs( sensors[ i ].value - tmpValue ) >= sensors[ i ].sensitivity ) {
						sensors[ i ].value = tmpValue;
						hasNewValue = true;
					}
				}
				else {
					tmpValue = analogRead( sensors[ i ].pin );
					tmpValue = ( *(sensors[i].customInt) )( tmpValue );

					if( abs( sensors[ i ].value - tmpValue ) >= sensors[ i ].sensitivity ) {
						sensors[ i ].value = tmpValue;
						
						if( sensors[ i ].value >= sensors[ i ].min && sensors[ i ].value <= sensors[ i ].max ) {
							hasNewValue = true;
						}
					}
				}
				break;

			case FLOAT_PROCESS_VALUE :
				if( sensors[ i ].isDigital == true ) {
					tmpValue = digitalRead( sensors[ i ].pin );
					fTmpValue = ( *(sensors[i].customFloat) )( tmpValue );

					if( abs( sensors[ i ].fValue - fTmpValue ) >= sensors[ i ].sensitivity ) {
						sensors[ i ].fValue = fTmpValue;
						hasNewValue = true;
					}
				}
				else {
					tmpValue = analogRead( sensors[ i ].pin );
					fTmpValue = ( *(sensors[i].customFloat) )( tmpValue );

					if( abs( sensors[ i ].fValue - fTmpValue ) >= sensors[ i ].sensitivity ) {
						sensors[ i ].fValue = fTmpValue;
						
						if( sensors[ i ].fValue >= sensors[ i ].min && sensors[ i ].fValue <= sensors[ i ].max ) {
							hasNewValue = true;
						}
					}
				}
				break;

			case INT_FUNCTION :
				tmpValue = ( *(sensors[i].customSensorInt) )();

				if( abs( sensors[ i ].value - tmpValue ) >= sensors[ i ].sensitivity ) {
					sensors[ i ].value = tmpValue;
					
					hasNewValue = true;
				}
				break;

			case FLOAT_FUNCTION :
				fTmpValue = ( *(sensors[i].customSensorFloat) )() ;

				if( abs( sensors[ i ].fValue - fTmpValue ) >= sensors[ i ].sensitivity ) {
					sensors[ i ].fValue = fTmpValue;
					
					hasNewValue = true;
				}
				break;
		}
	}
	
	if( hasNewValue ) {
		sendJSON();
	}
}

void SensorShield::createJSON()
{
	JSONMessage = "{";
	for ( int i = 0; i < nbSensors; ++i ) {
		if( i != 0) JSONMessage += ",";
		
		JSONMessage += "\"" + sensors[ i ].sensorID + "\":";

		if( sensors[ i ].type == 0
			|| sensors[ i ].type == 1
			|| sensors[ i ].type == 3 ){
			JSONMessage += String( sensors[ i ].value );
		}
		else if( sensors[ i ].type == 2
			|| sensors[ i ].type == 4 ){
			JSONMessage += String( sensors[ i ].fValue );
		}
	}
	JSONMessage += "}";
}

void SensorShield::sendJSON()
{
	createJSON();

	SensorShieldStream->println( JSONMessage );

	if( turnLightOn && indicatorLedPin != NULL) lightup();
}

/////////////////////////////////////////////////////////////////////
int SensorShield::getSensorValue( String sensorID )
{
	for (int i = 0; i < nbSensors; ++i) {
		if( sensors[ i ].sensorID == sensorID ) {
			return sensors[ i ].value;
		}
	}
}
float SensorShield::getSensorFValue( String sensorID )
{
	for (int i = 0; i < nbSensors; ++i) {
		if( sensors[ i ].sensorID == sensorID ) {
			return sensors[ i ].fValue;
		}
	}
}
