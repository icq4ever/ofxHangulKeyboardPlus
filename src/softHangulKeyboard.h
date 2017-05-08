/*
 *  softHangulKeyboard.h
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
#include "ofxMultiLanguageSoftKey.h"
#include "HangulAutomata.h"



//class ofApp;
class softHangulKeyboard   {
public:
	softHangulKeyboard();
	~softHangulKeyboard();

	void setup( ofBaseApp* ofApp, int layout);
	void setLayout(int layout);
	void addPadding(int top, int right, int bottom, int left);
	void reset();
	
	void draw(ofVec2f _position);
	void draw(float x, float y);
	void draw();

	// 소프트키
	ofxMultiLanguageSoftKey& addKey(int c, string enLabel, string krLabel);
	void newRow();

	void setPadding(int top, int right, int bottom, int left);
	void setTextColor(ofColor c);
	void setTextBGColor(ofColor c);
	void setBorderColor(ofColor c);
	void setHoverColor(ofColor c);
	void setClickColor(ofColor c);
	void setRoundness(float r);
	
	void activate();
	void deActivate();
	
	void initializeHangulKeyMapTable();
	void toggleInputLanguage();
	
	int	getLangState();
	
	void keyInput(int key);
	string getBuffer();
	
	int getHangulMapCode();
	void setPosition(float x, float y);
	void setPosition(ofVec2f pos);
	
	bool isGetActivated();
	void clearBuffer();
	void popFromBufferEnd();
	
	
protected:
	ofBaseApp* ofapp;
	vector<ofxMultiLanguageSoftKey*> keys;
	ofVec2f position;
	
	HangulAutomata automata;
	int hangulMapCode;
	wchar_t completedWord;
	wstring m_wstrText = L"";
	string stringBuffer = "";
	
	// 한글 키코드 테이블.
	map<char, int> m_HangulKeyTable;
	int inputLangState;
	int lastKeyComboCheckTimer;
	
	bool isActivated;
};

#endif
