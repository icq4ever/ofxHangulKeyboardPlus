/*
 *  ofxMultiLanguageSoftKey.h
 *
 *  original 'softKeyboardExample' code Created by Jeffrey Crouse on 11/9/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *
 *  modified by Yi donghoon on 09/05/17
 *
 */

#ifndef _OFX_SOFTKEY
#define _OFX_SOFTKEY

#define OFXSK_PADDING_TOP		0
#define OFXSK_PADDING_RIGHT		1
#define OFXSK_PADDING_BOTTOM	2
#define OFXSK_PADDING_LEFT		3

#define OFXSK_SPECIAL_KEYS	9999
#define OFXSK_KEY_SHIFT		10000
#define OFXSK_KEY_TAB		10001
#define OFXSK_KEY_CAPS		10002
#define OFXSK_KEY_DELETE	10003
#define OFXSK_KEY_RETURN	10004
#define OFXSK_KEY_LANG		10005
//#define OFXSK_KEY_F12		10006

#include "ofMain.h"
#include "ofxMSAInteractiveObject.h"
#include "ofxTrueTypeFontUC.h"

#define OFXVHK_LAYOUT_EN 1
#define OFXVHK_LAYOUT_KR 2

class ofApp;
class ofxMultiLanguageSoftKey : public ofxMSAInteractiveObject {
public:
	ofxTrueTypeFontUC *labelFont;
	
	bool isLastInRow;
	bool isActivated;
	int* padding;
	
	// 영문, 한글 키보드 라벨을 동시에 추가한다.
	ofxMultiLanguageSoftKey(int key, string _enLabel, string _krLabel, ofBaseApp* ofApp);
	~ofxMultiLanguageSoftKey();

	ofxMultiLanguageSoftKey& setPadding(int top, int right, int bottom, int left);
	ofxMultiLanguageSoftKey& padLeft(int left);
	ofxMultiLanguageSoftKey& padRight(int right);
	
	ofxMultiLanguageSoftKey& setKey(const char key);
	ofxMultiLanguageSoftKey& setTextColor(ofColor c);
	ofxMultiLanguageSoftKey& setTextBGColor(ofColor c);
	ofxMultiLanguageSoftKey& setBorderColor(ofColor c);
	ofxMultiLanguageSoftKey& setHoverColor(ofColor c);
	ofxMultiLanguageSoftKey& setClickColor(ofColor c);
	ofxMultiLanguageSoftKey& setRoundness(float r);
	
	void draw(int _langState);
	
	void onPress(int x, int y, int button);
	void onRelease(int x, int y, int button);
	void onReleaseOutside(int x, int y, int button);
	
	void setEnable(bool _isActivated);
	void setDisable(bool _isActivated);
protected:
	
	ofBaseApp* ofapp;
	
	int key;
	string *enLabel;
	string *krLabel;
	float roundness;
	ofColor textColor, textBGColor, borderColor, hoverColor, clickColor;
};

#endif
