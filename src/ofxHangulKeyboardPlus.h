//
//  ofxHangulKeyboardPlus.h
//  ofxHangulKeyboardPlus
//
//  Created by icq4ever on 10/10/2016.
//
//

#include "ofMain.h"
#include "softHangulKeyboard.h"

class ofxHangulKeyboardPlus{

public:
	
	ofxHangulKeyboardPlus();
	~ofxHangulKeyboardPlus();
	
	void setup(ofBaseApp *_ofApp, bool hangulMode);
	void setPosition(ofVec2f pos);
	void draw();
	void sendKey(int key);
	void toggleKeyboard();
	string getBuffer();
	void clearBuffer();
	bool getInputMode();
	
protected:
	ofBaseApp	*ofApp;
	bool isHangulMode;
	
	string mergedBuffer;
	
	softHangulKeyboard *keyboard;
	
	ofVec2f position;
	float lastKeyComboCheckTimer;
};

