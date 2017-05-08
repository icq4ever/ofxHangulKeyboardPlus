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
	
	hudFont = new ofxTrueTypeFontUC();
	hudFont->loadFont("AppleSDGothicNeo-Regular.otf", 16, true, true);
}

ofxHangulKeyboardPlus::~ofxHangulKeyboardPlus(){
	delete keyboard;
	delete hudFont;
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

void ofxHangulKeyboardPlus::draw(float _x, float _y){
	keyboard->draw(ofVec2f(_x, _y));
}

void ofxHangulKeyboardPlus::draw(ofVec2f pos){
	keyboard->draw(pos);
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

// 언어 설정 HUD 출력
void ofxHangulKeyboardPlus::displayInputLanguageHUD(float _x, float _y){
	ofPushMatrix();
	ofPushStyle();
	{
		ofTranslate(_x,	_y);
		ofSetHexColor(0x333333);
		ofFill();
		ofDrawRectRounded(0, 0, 60, 60, 5);
		
		ofSetHexColor(0xFFFFFF);
		if(inputMethod == OFXVHK_LAYOUT_EN){
			hudFont->drawStringAsShapes("EN", 17, 38);
		} else {
			hudFont->drawStringAsShapes("한글", 12, 38);
		}
	}
	ofPopStyle();
	ofPopMatrix();
}
