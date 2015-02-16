/*
 Based on Web Server Tutorial
 http://arduino.cc/en/Tutorial/WebServer
 
 and Sam Fentress' Web Server returning data as JSON-P,
 https://gist.github.com/sfentress/2126328
 
 Modified by Lionel Radisson @Makio135
 O2/2015
*/

#include <SPI.h>
#include <Ethernet.h>

#include <sensorShieldLib.h>

// Enter a MAC address and IP address for your controller below.
byte mac[] = { 
    0x90, 0xA2, 0xDA, 0x0D, 0x19, 0x93
};
// The IP address will be dependent on your local network:
IPAddress ip( 192, 168, 0, 135 );

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

SensorShield board;

void setup(){
    // start the Ethernet connection and the server:
    Ethernet.begin( mac, ip );
    server.begin();

    board.init();
    board.addSensor( "btn", 2 );
    board.addSensor( "pot", A0 );
    board.setAnalogSensitivity( "pot", 2 );
    board.emitLightOnChange(8);

    Serial.print( "server is at " );
    Serial.println( Ethernet.localIP() );
}


void loop(){
    board.update();

    // listen for incoming clients
    EthernetClient client = server.available();
    if ( client ) {
        // an http request ends with a blank line
        boolean currentLineIsBlank = true;
        while ( client.connected() ) {
            if ( client.available() ) {
                char c = client.read();
                // if you've gotten to the end of the line (received a newline
                // character) and the line is blank, the http request has ended,
                // so you can send a reply
                if ( c == '\n' && currentLineIsBlank ) {
                    // send a standard http response header
                    client.println( "HTTP/1.1 200 OK" );
                    client.println( "Content-Type: application/json" );
                    client.println();
                    
                    client.print( board.JSONMessage );
                    
                    break;
                }
                if ( c == '\n' ) {
                    // you're starting a new line
                    currentLineIsBlank = true;
                } 
                else if ( c != '\r' ) {
                    // you've gotten a character on the current line
                    currentLineIsBlank = false;
                }
            }
        }
        // give the web browser time to receive the data
        delay( 1 );
        // close the connection:
        client.stop();
    }
}