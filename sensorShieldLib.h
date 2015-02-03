/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef SensorShield_h
#define SensorShield_h

#include "Arduino.h"

struct sensorStruct
{
	String name;
	int pin;
	bool isDigital;
	bool isInputPullUp;
	int value;
};

class SensorShield
{
	public:
		SensorShield();

		void initialize();

		void setDigitalPinsRange( int pinMin, int pinMax );
		void setAnalogPinsRange( int pinMin, int pinMax );
		void setAnalogSensitivity( int sensitivity );

		void addSensor( String name, int pin, int mode );

		void update();

	private:
		int digitalPinMin;
		int digitalPinMax;
		int analogPinMin;
		int analogPinMax;

		int nbSensors;
		int analogSensitivity;

		bool hasNewValue;

		sensorStruct sensors[30];

		void sendMessage();
};

#endif