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
	int analogSensitivity;
	int value;
	int min;
	int max;
	char hasCustomFunction;
	int (*customInt)(int);
	float (*customFloat)(int);
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

		void setAnalogSensitivity( int sensitivity );
		void setAnalogSensitivity( String sensorID, int sensitivity );

		void setAnalogLimits( int min, int max );
		void setAnalogLimits( String sensorID, int min, int max );

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