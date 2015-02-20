import processing.serial.*;

Serial myPort;
JSONObject json;

void setup() 
{
    size( 200, 200 );

    printArray( Serial.list() );
    String portName = "/dev/ttyUSB0";
    myPort = new Serial( this, portName, 9600 );
}

void draw()
{
    while ( myPort.available() > 0 ) {
        String data = myPort.readStringUntil( '\n' );
        if ( data != null ) {
            println( data );
            try {
                json = JSONObject.parse( data );
                println( json.getInt( "btn" ) );
                
                background( json.getInt( "btn" ) * 255 );
            } 
            catch ( Exception e ) {
                e.printStackTrace();
            }
        }
    }
}

