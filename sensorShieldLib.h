/*
  sensorShieldLib.h - Library for communicating sensors values in JSON.
  Created by Lionel Radisson @Makio135, February, 2015.
  Released into the public domain.
*/
#pragma once

#include "Arduino.h"

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

		void emitLightOnChange( int ledPin );
		void emitLightOnChange( bool turnLightOn );

		void update();

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

		sensorStruct sensors[ 30 ];

		void initValues();
		void addDigitalSensor( int pin, int mode );
		void addAnalogSensor();
		void lightup();
		void createJSON();
		void sendJSON();
};