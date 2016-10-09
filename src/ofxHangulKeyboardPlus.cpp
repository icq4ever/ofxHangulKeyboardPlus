//
//  ofxHangulKeyboardPlus.cpp
//  ofxHangulKeyboardPlus
//
//  Created by icq4ever on 10/10/2016.
//
//

#include "ofxHangulKeyboardPlus.h"

ofxHangulKeyboardPlus::ofxHangulKeyboardPlus(){
	hangulKeyboard = new softHangulKeyboard();
	engKeyboard = new softHangulKeyboard();
	
	hangulKeyboard->activate();
	engKeyboard->deActivate();

}

ofxHangulKeyboardPlus::~ofxHangulKeyboardPlus(){
	delete hangulKeyboard;
	delete engKeyboard;

}

void ofxHangulKeyboardPlus::setup(ofBaseApp *_ofApp, bool hangulMode){
	ofApp = _ofApp;
	hangulKeyboard->setup(ofApp, OFXSK_LAYOUT_KEYBOARD_FULL_KR);
	engKeyboard->setup(ofApp, OFXSK_LAYOUT_KEYBOARD_FULL_EN);
	
	if(hangulMode)	isHangulMode = true;
	else			isHangulMode = false;
}

void ofxHangulKeyboardPlus::sendKey(int _key){
	hangulKeyboard->keyInput(_key);
	engKeyboard->keyInput(_key);
}

void ofxHangulKeyboardPlus::update(){
	tmpBuffer_kr = hangulKeyboard->getBuffer();
	tmpBuffer_en = engKeyboard->getBuffer();
}

void ofxHangulKeyboardPlus::draw(){
	if(hangulKeyboard->isGetActivated())	hangulKeyboard->draw(100, 350);
	if(engKeyboard->isGetActivated())		engKeyboard->draw(100, 350);
}

void ofxHangulKeyboardPlus::toggleKeyboard(){
	hangulKeyboard->toggleInputLanguage();
	engKeyboard->toggleInputLanguage();
	
	// 키보드가 비 활성화 됐을때 fullBuffer에 string을 가져오고, 키보드의 버퍼를 삭제한다.
}

string ofxHangulKeyboardPlus::getBuffer(){
	return mergedBuffer;
}

void ofxHangulKeyboardPlus::clearBuffer(){
	// 버퍼 삭제
	mergedBuffer.clear();
}
