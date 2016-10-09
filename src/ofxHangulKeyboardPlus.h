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
	void update();
	void draw();
	void sendKey(int key);
	void toggleKeyboard();
	string getBuffer();
	void clearBuffer();
	
protected:
	ofBaseApp	*ofApp;
	bool isHangulMode;
	
	string tmpBuffer_kr;
	string tmpBuffer_en;
	string mergedBuffer;
	
	softHangulKeyboard *hangulKeyboard;
	softHangulKeyboard *engKeyboard;
	
	ofVec2f positiion;
	float lastKeyComboCheckTimer;
};

