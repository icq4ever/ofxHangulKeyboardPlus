//
//  ofxHangulKeyboardPlus.cpp
//  ofxHangulKeyboardPlus
//
//  Created by icq4ever on 10/10/2016.
//
//

#include "ofxHangulKeyboardPlus.h"

ofxHangulKeyboardPlus::ofxHangulKeyboardPlus(){
	keyboard = new softHangulKeyboard();
	
	position = ofVec2f(100, 350);
}

ofxHangulKeyboardPlus::~ofxHangulKeyboardPlus(){
	delete keyboard;
}

void ofxHangulKeyboardPlus::setup(ofBaseApp* _ofApp, bool hangulMode){
	ofApp = _ofApp;
	keyboard->setup(ofApp, OFXVHK_LAYOUT_KR);
	
	if(hangulMode)	{
		isHangulMode = true;
		keyboard->activate();
	}
}

void ofxHangulKeyboardPlus::setPosition(ofVec2f pos){
	position = pos;
}

void ofxHangulKeyboardPlus::sendKey(int _key){
	if(_key == OF_KEY_BACKSPACE){			// if backspace key is pressed, remove end of char from mergedBuffer
		if(mergedBuffer.length() > 0)			mergedBuffer.pop_back();
	} else {
		
			keyboard->keyInput(_key);
			mergedBuffer = keyboard->getBuffer();	// --> error occured
			keyboard->clearBuffer();
	}

}

void ofxHangulKeyboardPlus::draw(){
	keyboard->draw(position);
}

void ofxHangulKeyboardPlus::toggleKeyboard(){
	keyboard->toggleInputLanguage();
	isHangulMode = !isHangulMode;
}

string ofxHangulKeyboardPlus::getBuffer(){
	return mergedBuffer;
}

void ofxHangulKeyboardPlus::clearBuffer(){
	mergedBuffer.clear();
}

bool ofxHangulKeyboardPlus::getInputMode(){
	return isHangulMode;
}
