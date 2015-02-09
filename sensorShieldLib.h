/*
  sensorShield.h - Library for communicating sensors values in JSON.
  Created by Lionel Radisson @Makio135, February, 2015.
  Released into the public domain.
*/
#pragma once
// #ifndef SensorShield_h
// #define SensorShield_h

#include "Arduino.h"

struct sensorStruct
{
	String name;
	int pin;
	bool isDigital;
	bool isInputPullUp;
	int analogSensitivity;
	int value;
	int min;
	int max;
};

class SensorShield
{
	public:
		SensorShield();

		void initialize( int ledPin );
		void initialize( Stream &stream, int ledPin );
		void setDigitalPinsRange( int pinMin, int pinMax );
		void setAnalogPinsRange( int pinMin, int pinMax );
		void setAnalogSensitivity( int sensitivity );
		void setAnalogSensitivity( String sensor, int sensitivity );
		void addSensor( String name, int pin);
		void addSensor( String name, int pin, int mode );
		void update();

	private:
		Stream * SensorShieldStream;
		int indicatorLedPin;
		int digitalPinMin;
		int digitalPinMax;
		int analogPinMin;
		int analogPinMax;
		int nbSensors;
		bool hasNewValue;

		// vector<sensorStruct> sensors;
		sensorStruct sensors[30];

		void initValues();
		void sendMessage();
};

// #endif