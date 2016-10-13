#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_SILENT);
	
	textFont = new ofxTrueTypeFontUC();
	textFont->loadFont("AppleSDGothicNeo-Regular.otf", 30, true, true);
	
	
	lastKeyComboCheckTimer = ofGetElapsedTimeMillis();
	
	keyboard = new ofxHangulKeyboardPlus();
	keyboard->setup(this, true);
	isHangulInputMode = keyboard->getInputMode();
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);

	// draw keyboard
	keyboard->draw();
	

	ofSetHexColor(0xFFFFFF);
	ofFill();
	
	textFont->drawStringAsShapes(stringBox, 50, 120);
}


void ofApp::exit(){
	delete textFont;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == OF_KEY_F12){
		if(ofGetElapsedTimeMillis() - lastKeyComboCheckTimer > 50){
			
			// toggle lang mode
			keyboard->toggleKeyboard();
			
			// 키보드 교체
			lastKeyComboCheckTimer = ofGetElapsedTimeMillis();		// prevent change too fast
			isHangulInputMode =  keyboard->getInputMode();
		}
	}
	
	
	
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
