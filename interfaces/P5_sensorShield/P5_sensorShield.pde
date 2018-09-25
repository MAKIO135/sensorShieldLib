import processing.serial.*;

Serial myPort;
JSONObject json;

int pot1 = 0;

void setup() {
    size( 200, 200 );

    printArray( Serial.list() );
    String portName = "/dev/cu.usbserial-ADAQJDL70";
    myPort = new Serial( this, portName, 9600 );
}

void draw() {
    updateSerial();

    background( pot1 / 4 );
}

void updateSerial() {
    while ( myPort.available() > 0 ) {
        String data = myPort.readStringUntil( '\n' );

        if ( data != null ) {
            println( data );
            
            try {
                json = JSONObject.parse( data );
                pot1 = json.getInt( "pot1" );
                println( pot1 );
            } 
            catch ( Exception e ) {
                e.printStackTrace();
            }
        }
    }
}

