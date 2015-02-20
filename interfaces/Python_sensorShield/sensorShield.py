import serial
import json

ser = serial.Serial( '/dev/ttyUSB0', 9600 )

while True:
	data_string = ser.readline()
	print data_string

	try:
		data = json.loads( data_string )
		print data['btn']
	except: 
		print "could not parse data_string"
		pass