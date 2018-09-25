#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    int baud = 9600;
    serial.setup( "/dev/cu.usbserial-ADAQJDL70", baud );
    json = "";
    pot1 = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    if( serial.available() ){
        //cout << "\tavailable: " << ofToString( serial.available() ) << endl;
        while( serial.available() ){
            lastChar = char( serial.readByte() );
            json += ofToString( lastChar );
        }

        if(lastChar == '\n'){
            bool parsingSuccessful = jsonEl.parse( json );
            std::cout << json << std::endl;
            std::cout << "parsingSuccessful: " << ofToString( parsingSuccessful ) << std::endl;

            if( parsingSuccessful ){
                pot1 = jsonEl[ "pot1" ].asInt();
                ofLog() << "pot1: " << pot1 << std::endl;
            }
            json = "";
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground( pot1 / 4 );
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
