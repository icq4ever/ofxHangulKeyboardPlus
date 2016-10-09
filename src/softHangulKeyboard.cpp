/*
 *  softHangulKeyboard.cpp
 *  softKeyboardExample
 *
 *  Created by Jeffrey Crouse on 11/9/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *
 *  Hangul 2-beolsik Keybord System.
 *  Modified by Yi donghoon on 09/10/15
 */

#include "ofMain.h"
#include "softHangulKeyboard.h"
#include <codecvt>


softHangulKeyboard::softHangulKeyboard() {
	initializeHangulKeyMapTable();
	
	lastKeyComboCheckTimer = ofGetElapsedTimeMillis();
	isActivated = false;
}

string softHangulKeyboard::getBuffer(){
	return stringBuffer;
}

int softHangulKeyboard::getLangState(){
	return inputLangState;
}

//--------------------------------------------------------------
softHangulKeyboard::~softHangulKeyboard() {
	for(int i=0; i<keys.size(); i++) {
		delete keys[i];
	}
}

//--------------------------------------------------------------
void softHangulKeyboard::setup( ofBaseApp* _ofApp, int layout ) {
	
	ofapp = _ofApp;
	inputLangState = layout;
	setLayout(inputLangState);
//	cout << inputLangState << endl;
}

void softHangulKeyboard::activate(){
	if(getLangState() == OFXSK_LAYOUT_KEYBOARD_FULL_EN)		cout << "EN KEYBOARD DEACTIVATED" << endl;
	else														cout << "KR kEYBOARD DEACTIVATED" << endl;
	
	isActivated = true;
	
}

void softHangulKeyboard::deActivate(){
	if(getLangState() == OFXSK_LAYOUT_KEYBOARD_FULL_EN)		cout << "EN KEYBOARD ACTIVATED" << endl;
	else														cout << "KR kEYBOARD ACTIVATED" << endl;
	
	isActivated = false;
}

//--------------------------------------------------------------
void softHangulKeyboard::setLayout(int layout) {
	
	reset();
	
	switch(layout) {
			
		case OFXSK_LAYOUT_KEYBOARD_FULL_EN:
			addKey('`', "`"); addKey('1', "1"); addKey('2', "2"); addKey('3', "3"); addKey('4', "4"); addKey('5', "5"); addKey('6', "6"); addKey('7', "7"); addKey('8', "8"); addKey('9', "9"); addKey('0', "0"); addKey('-', "-"); addKey('=', "="); addKey(OFXSK_KEY_DELETE, "delete"); newRow();
			addKey(OFXSK_KEY_TAB, "tab"); addKey('q', "q"); addKey('w', "w"); addKey('e', "e"); addKey('r', "r"); addKey('t', "t"); addKey('y', "y"); addKey('u', "u"); addKey('i', "i"); addKey('o', "o"); addKey('p', "p"); addKey('[', "["); addKey(']', "]"); addKey('\\', "\\"); newRow();
			addKey(OFXSK_KEY_CAPS, "capslock"); addKey('a', "a"); addKey('s', "s"); addKey('d', "d"); addKey('f', "f"); addKey('g', "g"); addKey('h', "h"); addKey('j', "j"); addKey('k', "k"); addKey('l', "l"); addKey(';', ";"); addKey('\'', "\'"); addKey(OFXSK_KEY_RETURN, "return"); newRow();
			addKey(OFXSK_KEY_SHIFT, "shift"); addKey('z', "z"); addKey('x', "x"); addKey('c', "c"); addKey('v', "v"); addKey('b', "b"); addKey('n', "n"); addKey('m', "m"); addKey(',', ","); addKey('.', "."); addKey('/', "/"); addKey(OFXSK_KEY_SHIFT, "shift"); newRow();
			addKey(' ', " ").padLeft(200).setSize(300, 40), addKey(OFXSK_KEY_LANG, "KR/EN").setSize(65, 40);
			break;
			
		case OFXSK_LAYOUT_KEYBOARD_FULL_KR:
			addKey('`', "`"); addKey('1', "1"); addKey('2', "2"); addKey('3', "3"); addKey('4', "4"); addKey('5', "5"); addKey('6', "6"); addKey('7', "7"); addKey('8', "8"); addKey('9', "9"); addKey('0', "0"); addKey('-', "-"); addKey('=', "="); addKey(OFXSK_KEY_DELETE, "delete"); newRow();
			addKey(OFXSK_KEY_TAB, "tab"); addKey('q', "ㅂ"); addKey('w', "ㅈ"); addKey('e', "ㄷ"); addKey('r', "ㄱ"); addKey('t', "ㅅ"); addKey('y', "ㅛ"); addKey('u', "ㅕ"); addKey('i', "ㅑ"); addKey('o', "ㅐ"); addKey('p', "ㅔ"); addKey('[', "["); addKey(']', "]"); addKey('\\', "\\"); newRow();
			addKey(OFXSK_KEY_CAPS, "caps"); addKey('a', "ㅁ"); addKey('s', "ㄴ"); addKey('d', "ㅇ"); addKey('f', "ㄹ"); addKey('g', "ㅎ"); addKey('h', "ㅗ"); addKey('j', "ㅓ"); addKey('k', "ㅏ"); addKey('l', "ㅣ"); addKey(';', ";"); addKey('\'', "\'"); addKey(OFXSK_KEY_RETURN, "return"); newRow();
			addKey(OFXSK_KEY_SHIFT, "shift"); addKey('z', "ㅋ"); addKey('x', "ㅌ"); addKey('c', "ㅊ"); addKey('v', "ㅍ"); addKey('b', "ㅠ"); addKey('n', "ㅜ"); addKey('m', "ㅡ"); addKey(',', ","); addKey('.', "."); addKey('/', "/"); addKey(OFXSK_KEY_SHIFT, "shift"); newRow();
			addKey(' ', " ").padLeft(200).setSize(300, 40), addKey(OFXSK_KEY_LANG, "한/영").setSize(65, 40);
			break;
	}
}

//--------------------------------------------------------------
void softHangulKeyboard::reset() {
//	for(int i=0; i<keys.size(); i++) {
//		delete keys[i];
//	}
	keys.clear();
//	cout << "cleared! key vector length is: " << keys.size() << endl;
}

void softHangulKeyboard::initializeHangulKeyMapTable(){
	m_HangulKeyTable['q']	=   7;	// ㅂ
	m_HangulKeyTable['Q']	=   8;	// ㅃ
	m_HangulKeyTable['w']	=  12;	// ㅈ
	m_HangulKeyTable['W']	=  13;	// ㅉ
	m_HangulKeyTable['e']	=   3;	// ㄷ
	m_HangulKeyTable['E']	=   4;	// ㄸ
	m_HangulKeyTable['r']	=   0;	// ㄱ
	m_HangulKeyTable['R']	=   1;	// ㄲ
	m_HangulKeyTable['t']	=   9;	// ㅅ
	m_HangulKeyTable['T']	=  10;	// ㅆ
	m_HangulKeyTable['y']	=  31;	// ㅛ
	m_HangulKeyTable['Y']	=  31;	// ㅛ
	m_HangulKeyTable['u']	=  25;	// ㅕ
	m_HangulKeyTable['U']	=  25;	// ㅕ
	m_HangulKeyTable['i']	=  21;	// ㅑ
	m_HangulKeyTable['I']	=  21;	// ㅑ
	m_HangulKeyTable['o']	=  20;	// ㅐ
	m_HangulKeyTable['O']	=  22;	// ㅒ
	m_HangulKeyTable['p']	=  24;	// ㅔ
	m_HangulKeyTable['P']	=  26;	// ㅖ
	m_HangulKeyTable['a']	=   6;	// ㅁ
	m_HangulKeyTable['A']	=   6;	// ㅁ
	m_HangulKeyTable['s']	=   2;	// ㄴ
	m_HangulKeyTable['S']	=   2;	// ㄴ
	m_HangulKeyTable['d']	=  11;	// ㅇ
	m_HangulKeyTable['D']	=  11;	// ㅇ
	m_HangulKeyTable['f']	=   5;	// ㄹ
	m_HangulKeyTable['F']	=   5;	// ㄹ
	m_HangulKeyTable['g']	=  18;	// ㅎ
	m_HangulKeyTable['G']	=  18;	// ㅎ
	m_HangulKeyTable['h']	=  27;	// ㅗ
	m_HangulKeyTable['H']	=  27;	// ㅗ
	m_HangulKeyTable['j']	=  23;	// ㅓ
	m_HangulKeyTable['J']	=  23;	// ㅓ
	m_HangulKeyTable['k']	=  19;	// ㅏ
	m_HangulKeyTable['K']	=  19;	// ㅏ
	m_HangulKeyTable['l']	=  39;	// ㅣ
	m_HangulKeyTable['L']	=  39;	// ㅣ
	m_HangulKeyTable['z']	=  15;	// ㅋ
	m_HangulKeyTable['Z']	=  15;	// ㅋ
	m_HangulKeyTable['x']	=  16;	// ㅌ
	m_HangulKeyTable['X']	=  16;	// ㅌ
	m_HangulKeyTable['c']	=  14;	// ㅊ
	m_HangulKeyTable['C']	=  14;	// ㅊ
	m_HangulKeyTable['v']	=  17;	// ㅍ
	m_HangulKeyTable['V']	=  17;	// ㅍ
	m_HangulKeyTable['b']	=  36;	// ㅠ
	m_HangulKeyTable['B']	=  36;	// ㅠ
	m_HangulKeyTable['n']	=  32;	// ㅜ
	m_HangulKeyTable['N']	=  32;	// ㅜ
	m_HangulKeyTable['m']	=  37;	// ㅡ
	m_HangulKeyTable['M']	=  37;	// ㅡ
	
	m_HangulKeyTable['`']	=  68;	// `
	m_HangulKeyTable['1']	=  69;	// 1
	m_HangulKeyTable['2']	=  70;	// 2
	m_HangulKeyTable['3']	=  71;	// 3
	m_HangulKeyTable['4']	=  72;	// 4
	m_HangulKeyTable['5']	=  73;	// 5
	m_HangulKeyTable['6']	=  74;	// 6
	m_HangulKeyTable['7']	=  75;	// 7
	m_HangulKeyTable['8']	=  76;	// 8
	m_HangulKeyTable['9']	=  77;	// 9
	m_HangulKeyTable['0']	=  78;	// 0
	m_HangulKeyTable['-']	=  79;	// -
	m_HangulKeyTable['=']	=  80;	// =
	m_HangulKeyTable['[']	=  81;	// [
	m_HangulKeyTable[']']	=  82;	// ]
	m_HangulKeyTable['\\']	=  83;	//
	m_HangulKeyTable[';']	=  84;	// ;
	m_HangulKeyTable['\'']	=  85;	// '
	m_HangulKeyTable[',']	=  86;	// ,
	m_HangulKeyTable['.']	=  87;	// .
	m_HangulKeyTable['/']	=  88;	// /
	
	m_HangulKeyTable['~']	=  89;	// ~
	m_HangulKeyTable['!']	=  90;	// !
	m_HangulKeyTable['@']	=  91;	// @
	m_HangulKeyTable['#']	=  92;	// #
	m_HangulKeyTable['$']	=  93;	// $
	m_HangulKeyTable['%']	=  94;	// %
	m_HangulKeyTable['^']	=  95;	// ^
	m_HangulKeyTable['&']	=  96;	// &
	m_HangulKeyTable['*']	=  97;	// *
	m_HangulKeyTable['(']	=  98;	// (
	m_HangulKeyTable[')']	=  99;	// )
	m_HangulKeyTable['_']	= 100;	// _
	m_HangulKeyTable['+']	= 101;	// +
	m_HangulKeyTable['{']	= 102;	// {
	m_HangulKeyTable['}']	= 103;	// }
	m_HangulKeyTable['|']	= 104;	// |
	m_HangulKeyTable[':']	= 105;	// :
	m_HangulKeyTable['"']	= 106;	// "
	m_HangulKeyTable['<']	= 107;	// <
	m_HangulKeyTable['>']	= 108;	// >
	m_HangulKeyTable['?']	= 109;	// ?

}

//--------------------------------------------------------------
//ofxSoftKey& softHangulKeyboard::addKey(int c) {
//
//	ofxSoftKey* key = new ofxSoftKey(c, ofapp);
//	key->setPadding(6, 6, 6, 6);
//	keys.push_back( key );
//	return *keys.back();
//}

// keyboard label
ofxSoftKey& softHangulKeyboard::addKey(int c, string label) {
	
	ofxSoftKey* key = new ofxSoftKey(c, label, ofapp);
	key->setPadding(6, 6, 6, 6);
	keys.push_back( key );
	return *keys.back();
}

void softHangulKeyboard::keyInput(int key) {
//	cout << "already ready" << endl;
//		cout << "ready" << endl;
		int code = 0;
		if(key <0)	return;
		
		switch(key){
			case OF_KEY_F1:
			case OF_KEY_F2:
			case OF_KEY_F3:
			case OF_KEY_F4:
			case OF_KEY_F5:
			case OF_KEY_F6:
			case OF_KEY_F7:
			case OF_KEY_F8:
			case OF_KEY_F9:
			case OF_KEY_F10:
			case OF_KEY_F11:
//			case OF_KEY_F12:
			case OF_KEY_ESC:
			case OF_KEY_LEFT_SHIFT:
			case OF_KEY_RIGHT_SHIFT:
			case OF_KEY_SHIFT:
			case OF_KEY_ALT:
			case OF_KEY_LEFT_ALT:
			case OF_KEY_RIGHT_ALT:
			case OF_KEY_COMMAND:
			case OF_KEY_LEFT_COMMAND:
			case OF_KEY_RIGHT_COMMAND:
			case OF_KEY_CONTROL:
			case OF_KEY_LEFT_CONTROL:
			case OF_KEY_RIGHT_CONTROL:
				break;
			case OF_KEY_RETURN:
				automata.SetKeyCode(KEY_CODE_ENTER);
				break;
			case ' ':
				automata.SetKeyCode(KEY_CODE_SPACE);
				break;
			case OF_KEY_BACKSPACE:
				automata.SetKeyCode(KEY_CODE_BACKSPACE);	// KEY_CODE_BACKSPACE
				break;
				
				// disable arrow keys
			case OF_KEY_LEFT:
			case OF_KEY_RIGHT:
			case OF_KEY_UP:
			case OF_KEY_DOWN:
				break;
			case OF_KEY_F12:
				break;
			default:
				if(isActivated){
					if(getLangState() == OFXSK_LAYOUT_KEYBOARD_FULL_EN){	// english
						automata.pushASCII(key);
					} else {
						// ÌÖåÏù¥Î∏îÏóêÏÑú ÌÇ§Î•º Ï∞æÏïÑÏÑú Ìï¥Îãπ ÏΩîÎìúÎ•º Î¶¨ÌÑ¥ÌïúÎã§..
						auto it = m_HangulKeyTable.find(key);
						if(it != m_HangulKeyTable.end()){
							code = it->second;
							automata.SetKeyCode(code);
							hangulMapCode = code;
		//					ss = "key : " + to_string(static_cast<char>(key)) + " >> keyCode is : " + to_string(code);
		//					cout << "key : " << static_cast<char>(key)  << " >> keyCode is : " << code << endl;
		//
		//					cout << "complete string is : \t" << stringBuffer << endl;
		//					cout << "automata.ingWord is : \t";
		//					wcout << automata.ingWord << endl;
		//					cout << "==========================================" << endl;
						}
					}
				}
				break;
		}
		m_wstrText = automata.completeText + automata.ingWord;
		
		std::wstring_convert<std::codecvt_utf8<wchar_t>,wchar_t> convert;
		stringBuffer.assign(convert.to_bytes(m_wstrText));
	//	cout << "wowowowowowo : "  + ofToString(ofGetElapsedTimeMillis()) << endl;
}


//--------------------------------------------------------------
void softHangulKeyboard::newRow() {
	keys.back()->isLastInRow = true;
}

void softHangulKeyboard::toggleInputLanguage(){
//	if(inputLangState == OFXSK_LAYOUT_KEYBOARD_FULL_EN)		inputLangState = OFXSK_LAYOUT_KEYBOARD_FULL_KR;
//	else														inputLangState = OFXSK_LAYOUT_KEYBOARD_FULL_EN;
	isActivated = !isActivated;
}

//--------------------------------------------------------------

void softHangulKeyboard::draw(ofVec2f _position){
	draw(_position.x, _position.y);
}

void softHangulKeyboard::draw(float x, float y){
	setPosition(x, y);
	draw();
}

bool softHangulKeyboard::isGetActivated(){
	return isActivated;
}

void softHangulKeyboard::draw() {
//	if(isActivated){
		int xpos = position.x;
		int ypos = position.y;
		//	cout << ofToString(ofGetElapsedTimef());
		for(int i=0; i<keys.size(); i++){
			xpos += keys[i]->padding[OFXSK_PADDING_LEFT];
			
			keys[i]->setPosition(xpos, ypos);
			keys[i]->setRoundness(2);
			keys[i]->draw();
			
			if(keys[i]->isLastInRow) {
				
				xpos  = position.x;
				ypos += keys[i]->height + keys[i]->padding[OFXSK_PADDING_BOTTOM];
				
			} else {
				xpos += keys[i]->width + keys[i]->padding[OFXSK_PADDING_RIGHT];
			}
		}
//	}
}

int softHangulKeyboard::getHangulMapCode(){
	return hangulMapCode;
}

void softHangulKeyboard::setPosition(ofVec2f _pos){
	setPosition(_pos.x, _pos.y);
}

void softHangulKeyboard::setPosition(float _x, float _y){
	position.x = _x;
	position.y = _y;
	//	cout << "position is : " << position.x << " , " << position.y << endl;
}

//--------------------------------------------------------------
void softHangulKeyboard::setPadding(int top, int right, int bottom, int left) {
	for(auto &key: keys){
		key->setPadding(top, right, bottom, left);
	}
}

//--------------------------------------------------------------

void softHangulKeyboard::setTextColor(ofColor c){
	for(auto &key: keys){
		key->setTextColor( c );
	}
}

//--------------------------------------------------------------
void softHangulKeyboard::setTextBGColor(ofColor c){
	for(auto &key: keys){
		key->setTextBGColor( c );
	}
}

//--------------------------------------------------------------
void softHangulKeyboard::setBorderColor(ofColor c){
	for(auto &key: keys){
		key->setBorderColor( c );
	}
}

//--------------------------------------------------------------
void softHangulKeyboard::setHoverColor(ofColor c){
	for(auto &key: keys){
		key->setHoverColor( c );
	}
}

//--------------------------------------------------------------
void softHangulKeyboard::setClickColor(ofColor c){
	for(auto &key: keys){
		key->setClickColor( c );
	}
}

void softHangulKeyboard::setRoundness(float r){
	for(auto &key: keys){
		key->setRoundness(r);
	}
}
