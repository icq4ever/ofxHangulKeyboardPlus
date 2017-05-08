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

void ofxHangulKeyboardPlus::setup(ofBaseApp* _ofApp, int inputLang){
	ofApp = _ofApp;
	inputMethod = inputLang;
	keyboard->setup(ofApp, inputLang);
	
	keyboard->activate();
}

void ofxHangulKeyboardPlus::setPosition(ofVec2f pos){
	position = pos;
}

void ofxHangulKeyboardPlus::sendKey(int _key){
		keyboard->keyInput(_key);
		mergedBuffer = keyboard->getBuffer();
}

void ofxHangulKeyboardPlus::draw(){
	keyboard->draw(position);
}

void ofxHangulKeyboardPlus::toggleKeyboard(){
	keyboard->toggleInputLanguage();
	inputMethod = (inputMethod+1)%2;
}

string ofxHangulKeyboardPlus::getBuffer(){
	return mergedBuffer;
}

void ofxHangulKeyboardPlus::clearBuffer(){
	mergedBuffer.clear();
}

int ofxHangulKeyboardPlus::getInputMethod(){
	return inputMethod;
}
