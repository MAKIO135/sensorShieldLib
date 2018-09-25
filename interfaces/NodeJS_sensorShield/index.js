const SerialPort = require( 'serialport' )
const Readline = require( '@serialport/parser-readline' )

// check your Serial port name with Arduino IDE
const port = new SerialPort( '/dev/cu.usbserial-ADAQJDL70', {
	baudRate: 9600
} )

const parser = port.pipe( new Readline() )
parser.on( 'data', data => {
	const json = JSON.parse( data );
	console.log( json )
} )