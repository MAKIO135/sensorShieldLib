import java.net.URI;
import java.net.URISyntaxException;
import org.java_websocket.WebSocketImpl;
import org.java_websocket.client.WebSocketClient;
import org.java_websocket.drafts.Draft;
import org.java_websocket.drafts.Draft_17;
import org.java_websocket.handshake.ServerHandshake;

// Define the URI of your WebSocket server here:
String WebSocketServerURI = "ws://127.0.0.1:3000";

void setup() {
  new WebSocketJSONClient(WebSocketServerURI);
  size(600, 600);
  noStroke();
}

void draw () {
  fill(0, 0, 0, 35);
  rect(0, 0, width, height);
}

public class WebSocketJSONClient {
  private WebSocketClient cc;
  private JSONObject json;
  
  // This function will be called everytime some valid JSON data are received:
  public void onData (JSONObject data) {
    // Do your own stuff here...
    // e.g.: int mySensorValue = data.getInt("mySensorName");
    
    // A bit of visual feedback:
    fill(255, 0, 0);
    rect(0, 0, width, height);
  }
  
  public WebSocketJSONClient( String defaultlocation ) {
    try {
      cc = new WebSocketClient( new URI( defaultlocation ), new Draft_17() ) {
        @Override
        public void onMessage( String message ) {
          try {
            json = JSONObject.parse( message );
            println( "Got: " + message + "\n" );
            onData(json);
          } 
          catch ( Exception ex ) {
            ex.printStackTrace();
          }
        }

        @Override
        public void onOpen( ServerHandshake handshake ) {
          println( "You are connected to server: " + getURI() + "\n" );
        }

        @Override
        public void onClose( int code, String reason, boolean remote ) {
          println( "You have been disconnected from: " + getURI() + "; Code: " + code + " " + reason + "\n" );
        }

        @Override
        public void onError( Exception ex ) {
          println( "Exception occured ...\n" + ex + "\n" );
          ex.printStackTrace();
        }
      };
      cc.connect();
    } catch ( URISyntaxException ex ) {
      println( defaultlocation + " is not a valid WebSocket URI\n" );
    }
  }
}

