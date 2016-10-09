#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_SILENT);
	
	textFont = new ofxTrueTypeFontUC();
	textFont->loadFont("AppleSDGothicNeo-Regular.otf", 30, true, true);
	
	keyboard = new ofxSoftHangulKeyboard();
	keyboard->setup(this, OFXSK_LAYOUT_KEYBOARD_FULL_EN);
}

//--------------------------------------------------------------
void ofApp::update(){
	stringBox = keyboard->getBuffer();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	keyboard->draw(100, 350);

	ofSetHexColor(0xFFFFFF);
	ofFill();
	textFont->drawStringAsShapes(stringBox, 50, 120);
}


void ofApp::exit(){
	delete textFont;
	delete keyboard;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	keyboard->keyInput(key);
	
	if(keyboard->getLangState() == OFXSK_LAYOUT_KEYBOARD_FULL_EN)	debugMessage = "[KO] key : " + to_string(char(key)) + " >> keyCode is : " + to_string(keyboard->getHangulMapCode());
	else															debugMessage = "[EN]";
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
