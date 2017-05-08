/*
 *  softHangulKeyboard.cpp
 *  softKeyboardExample
 *
 *  
 *	original created by Jeffrey Crouse on 11/9/10.
 *  Modified by Yi donghoon
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
	clearBuffer();
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
	isActivated = true;
}

void softHangulKeyboard::deActivate(){
	isActivated = false;
}

//--------------------------------------------------------------
void softHangulKeyboard::setLayout(int layout) {

	// 1st line
	addKey('`', "`", "`"); addKey('1', "1", "1"); addKey('2', "2", "2"); addKey('3', "3", "3"); addKey('4', "4", "4"); addKey('5', "5", "5"); addKey('6', "6", "6"); addKey('7', "7", "7"); addKey('8', "8", "8"); addKey('9', "9", "9"); addKey('0', "0", "0"); addKey('-', "-", "-"); addKey('=', "=", "="); addKey(OFXSK_KEY_DELETE, "delete", "delete"); newRow();
	
	// 2nd line
	addKey(OFXSK_KEY_TAB, "tab", "tab"); addKey('q', "q", "ㅂ"); addKey('w', "w", "ㅈ"); addKey('e', "e", "ㄷ"); addKey('r', "r", "ㄱ"); addKey('t', "t", "ㅅ"); addKey('y', "y", "ㅛ"); addKey('u', "u", "ㅕ"); addKey('i', "i", "ㅑ"); addKey('o', "o", "ㅐ"); addKey('p', "p", "ㅔ"); addKey('[', "[", "["); addKey(']', "]", "]"); addKey('\\', "\\", "\\"); newRow();
	
	// 3rd line
	addKey(OFXSK_KEY_CAPS, "capslock", "capslock"); addKey('a', "a", "ㅁ"); addKey('s', "s", "ㄴ"); addKey('d', "d", "ㅇ"); addKey('f', "f", "ㄹ"); addKey('g', "g", "ㅎ"); addKey('h', "h", "ㅗ"); addKey('j', "j", "ㅓ"); addKey('k', "k", "ㅏ"); addKey('l', "l", "ㅣ"); addKey(';', ";", ";"); addKey('\'', "\'", "\'"); addKey(OFXSK_KEY_RETURN, "return", "return"); newRow();
	
	// 4th line
	addKey(OFXSK_KEY_SHIFT, "shift", "shift"); addKey('z', "z", "ㅋ"); addKey('x', "x", "ㅋ"); addKey('c', "c", "ㅊ"); addKey('v', "v", "ㅍ"); addKey('b', "b", "ㅠ"); addKey('n', "n", "ㅜ"); addKey('m', "m", "ㅡ"); addKey(',', ",", ","); addKey('.', ".", "."); addKey('/', "/", "/"); addKey(OFXSK_KEY_SHIFT, "shift", "shift"); newRow();
	
	// 5th line
	addKey(' ', " ", " ").padLeft(200).setSize(300, 40), addKey(OFXSK_KEY_LANG, "KR/EN", "한/영").setSize(65, 40);
}

//--------------------------------------------------------------
void softHangulKeyboard::reset() {
	keys.clear();
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

// keyboard label
MultiLanguageSoftKey& softHangulKeyboard::addKey(int c, string enLabel, string krLabel) {
	MultiLanguageSoftKey* key = new MultiLanguageSoftKey(c, enLabel, krLabel, ofapp);
	key->setPadding(6, 6, 6, 6);
	keys.push_back( key );
	return *keys.back();
}

void softHangulKeyboard::keyInput(int key) {
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
				if(getLangState() == OFXVHK_LAYOUT_EN){	// english
					automata.pushASCII(key);
					
				} else {
					// 테이블에서 키를 찾아 해당 코드로 리턴한다.
					auto it = m_HangulKeyTable.find(key);
					if(it != m_HangulKeyTable.end()){
						code = it->second;
						automata.SetKeyCode(code);
						hangulMapCode = code;
					}
				}
			}
			break;
	}


	m_wstrText = automata.completeText + automata.ingWord;
	std::wstring_convert<std::codecvt_utf8<wchar_t>,wchar_t> convert;
	stringBuffer.assign(convert.to_bytes(m_wstrText));
}


void softHangulKeyboard::popFromBufferEnd(){
	stringBuffer.pop_back();
	m_wstrText.clear();
//	m_wstrText.pop_back();
}

//--------------------------------------------------------------
void softHangulKeyboard::newRow() {
	keys.back()->isLastInRow = true;
}

void softHangulKeyboard::toggleInputLanguage(){
	if(inputLangState == OFXVHK_LAYOUT_EN)		inputLangState = OFXVHK_LAYOUT_KR;
	else										inputLangState = OFXVHK_LAYOUT_EN;
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
	int xpos = position.x;
	int ypos = position.y;
	
	// total key size is 55
	for(int i=0; i<keys.size(); i++){
		xpos += keys[i]->padding[OFXSK_PADDING_LEFT];
		
		keys[i]->setPosition(xpos, ypos);
		keys[i]->setRoundness(2);
		keys[i]->draw(getLangState());
		
		if(keys[i]->isLastInRow) {
			xpos  = position.x;
			ypos += keys[i]->height + keys[i]->padding[OFXSK_PADDING_BOTTOM];
		} else {
			xpos += keys[i]->width + keys[i]->padding[OFXSK_PADDING_RIGHT];
		}
	}

	ofNoFill();
	ofSetHexColor(0xFFFFFF);
	ofDrawRectangle(position.x -10, position.y-15, 785, 255);
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

void softHangulKeyboard::clearBuffer(){
	m_wstrText.clear();
	stringBuffer.clear();
	automata.clearBuffer();
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
