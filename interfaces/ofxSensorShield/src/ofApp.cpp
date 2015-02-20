#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    int baud = 9600;
    serial.setup("/dev/ttyUSB0", baud);
}

//--------------------------------------------------------------
void ofApp::update(){

    if( serial.available() ){
        //cout << "\tavailable: " << ofToString( serial.available() ) << endl;
        json = "";
        while( serial.available() ){
            json += ofToString( char( serial.readByte() ) );
        }
        std::cout << json << std::endl;
        bool parsingSuccessful = jsonEl.parse( json );
        std::cout << "parsingSuccessful: " << ofToString( parsingSuccessful ) << std::endl;

        if( parsingSuccessful ){
            ofLog() << "btn: " + ofToString( jsonEl[ "btn" ] );
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
