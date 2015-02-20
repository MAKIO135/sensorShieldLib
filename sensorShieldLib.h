/*
  sensorShieldLib.h - Library for communicating sensors values in JSON.
  Created by Lionel Radisson @Makio135, February, 2015.
  Released into the public domain.
*/
#pragma once

#include "Arduino.h"

#define MAX_NUMBER_OF_SENSORS 30

struct sensorStruct
{
	String sensorID;
	int pin;
	bool isDigital;
	bool invertValue;
	float analogSensitivity;
	int value;
	float fValue;
	int min;
	int max;
	char hasCustomFunction;
	int (*customInt)(int);
	float (*customFloat)(int);
	int (*customSensorInt)();
	float (*customSensorFloat)();
};

class SensorShield
{
	public:
		SensorShield();

		void init();
		void init( Stream &stream );

		void setDigitalPinsRange( int pinMin, int pinMax );
		void setAnalogPinsRange( int pinMin, int pinMax );

		void addSensor( String sensorID, int pin);
		void addSensor( String sensorID, int pin, int mode );

		void addSensor( String sensorID, int( *custFunction )() );
		void addSensor( String sensorID, float( *custFunction )() );

		void setSensorSensitivity( float sensitivity );
		void setSensorSensitivity( String sensorID, float sensitivity );

		void setSensorLimits( int min, int max );
		void setSensorLimits( String sensorID, int min, int max );

		void invertSensorValue( String sensorID );

		void setSensorFunction( String sensorID, int( *custFunction )( int ) );
		void setSensorFunction( String sensorID, float( *custFunction )( int ) );

		void emitLightOnChange( int ledPin );
		void emitLightOnChange( bool turnLightOn );

		void update();

		int getSensorValue( String sensorID );

		bool hasNewValue;
		String JSONMessage;

	private:
		Stream * SensorShieldStream;

		int digitalPinMin;
		int digitalPinMax;
		int analogPinMin;
		int analogPinMax;
		
		int nbSensors;
		
		int analogSensitivity;
		int analogMin;
		int analogMax;

		int indicatorLedPin;
		bool turnLightOn;

		sensorStruct sensors[ MAX_NUMBER_OF_SENSORS ];

		void initValues();
		void addDigitalSensor( int pin, int mode );
		void addAnalogSensor();
		void lightup();
		void createJSON();
		void sendJSON();
};