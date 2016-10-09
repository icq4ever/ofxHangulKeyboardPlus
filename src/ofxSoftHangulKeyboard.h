/*
 *  ofxSoftHangulKeyboard.h
 *  softKeyboardExample
 *
 *  Created by Jeffrey Crouse on 11/9/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *
 *  Hangul 2-beolsik Keybord System.
 *  Modified by Yi donghoon on 09/10/15
 */


#ifndef _OFX_SOFTKEYBOARD
#define _OFX_SOFTKEYBOARD

#include "ofMain.h"
#include "ofxSoftKey.h"
#include "HangulAutomata.h"

#define OFXSK_LAYOUT_KEYBOARD_FULL_EN 1
#define OFXSK_LAYOUT_KEYBOARD_FULL_KR 2

class ofApp;
class ofxSoftHangulKeyboard   {
public:
	ofxSoftHangulKeyboard();
	~ofxSoftHangulKeyboard();

	void setup( ofBaseApp* ofApp, int layout);
	void setLayout(int layout);
	void addPadding(int top, int right, int bottom, int left);
	void reset();
	void draw(ofVec2f _position);
	void draw(float x, float y);
	void draw();
//	ofxSoftKey& addKey(int c);
	ofxSoftKey& addKey(int c, string label);
	void newRow();

	void setPadding(int top, int right, int bottom, int left);
	void setTextColor(ofColor c);
	void setTextBGColor(ofColor c);
	void setBorderColor(ofColor c);
	void setHoverColor(ofColor c);
	void setClickColor(ofColor c);
	void setRoundness(float r);
	
	void initializeHangulKeyMapTable();
	void toggleInputLanguage();
	int	getLangState();
	void keyInput(int key);
	string getBuffer();
	int getHangulMapCode();
	void setPosition(float x, float y);
	void setPosition(ofVec2f pos);
	
//	bool shiftOn;
	
protected:
	ofBaseApp* ofapp;
	vector<ofxSoftKey*> keys;
	ofVec2f position;
	
	HangulAutomata automata;
	int hangulMapCode;
	wstring m_wstrText = L"";
//	string m_strText = "";
	string stringBuffer = "";
	
	// 영문-한글 매핑 테이블 
	map<char, int> m_HangulKeyTable;
	int inputLangState;
	int lastKeyComboCheckTimer;
};

#endif
