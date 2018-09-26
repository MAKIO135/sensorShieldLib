// Define your settings here:
const settings = {
	httpPort: 3000,
	serialPort: '/dev/cu.usbserial-ADAQJDL70',
	baudRate: 9600
}

// Setting up the HTTP server:
const express = require( 'express' )
const app = express()
const http = require( 'http' ).Server( app )

app.use( express.static( `${__dirname }/public` ) )

app.get( '/', ( req, res ) => {
	res.sendFile( 'index.html' )
} )

http.listen( settings.httpPort, () => {
	console.log( `Your app is listening on port ${ settings.httpPort }` )
} )

// Setting up websockets with socket.io
const io = require( 'socket.io' )( http )

// Setting up the Serial connection:
const SerialPort = require( 'serialport' )
const Readline = require( '@serialport/parser-readline' )

const port = new SerialPort( settings.serialPort, {
	baudRate: settings.baudRate
} )

const parser = port.pipe( new Readline() )
parser.on( 'data', serialData => {
	try {
		const json = JSON.parse( serialData )
		console.log( 'json received:', json )
		io.emit( 'data', json )
	}
	catch( error ) {
		console.error( { serialData, error } )
	}
} )