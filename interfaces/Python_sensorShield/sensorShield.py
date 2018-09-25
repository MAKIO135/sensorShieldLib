import serial
import json

ser = serial.Serial( '/dev/cu.usbserial-ADAQJDL70', 9600 )
pot1 = 0

while True:
	data_string = ser.readline()
	print data_string

	try:
		data = json.loads( data_string )
		pot1 = data[ 'pot1' ]
		print pot1
	except: 
		print 'could not parse data_string'
		pass