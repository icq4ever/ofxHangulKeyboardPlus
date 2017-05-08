//
//  ofxHangulKeyboardPlus.h
//  ofxHangulKeyboardPlus
//
//  Created by icq4ever on 10/10/2016.
//
//

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include "softHangulKeyboard.h"

class ofxHangulKeyboardPlus{

public:
	
	ofxHangulKeyboardPlus();
	~ofxHangulKeyboardPlus();
	
	void setup(ofBaseApp *_ofApp, int inputLang);
	void setPosition(ofVec2f pos);
	void draw(float _x, float _y);
	void draw(ofVec2f pos);
	void sendKey(int key);
	void toggleKeyboard();
	string getBuffer();
	void clearBuffer();
	int getInputMethod();
	void displayInputLanguageHUD(float _x, float _y);
	
protected:
	ofBaseApp			*ofApp;
	ofxTrueTypeFontUC	*hudFont;
	int inputMethod;
	
	string mergedBuffer;
	
	softHangulKeyboard *keyboard;
	
	ofVec2f position;
	float lastKeyComboCheckTimer;
};

