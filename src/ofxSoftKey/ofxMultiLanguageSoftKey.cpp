/*
 *  ofxMultiLanguageSoftKey.cpp
 *  softKeyboardExample
 *
 *  Created by Jeffrey Crouse on 11/9/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *
 */

#include "ofxMultiLanguageSoftKey.h"

#pragma mark CONSTRUCTORS

//--------------------------------------------------------------
//ofxMultiLanguageSoftKey::ofxMultiLanguageSoftKey(int _key, ofBaseApp* _ofApp) {
//	labelFont = new ofxTrueTypeFontUC();
//	labelFont->loadFont("AppleSDGothicNeo-Regular.otf", 12, true, true);
//	
//	ofapp = _ofApp;
//	key = _key;
//	roundness = 0;
//	
//	textColor = ofColor(0);
//	textBGColor = ofColor(204);
//	borderColor = ofColor(0);
//	hoverColor = ofColor(153);
//	clickColor = ofColor(255, 0, 0);
//	isLastInRow = false;
//	
//	disableAppEvents();
//	enableMouseEvents();
//	
//	padding = new int[4];
//	setPadding(5, 5, 5, 5);
//
//	switch(_key) {
//		case OFXSK_KEY_SHIFT:
//			label = "shift";
//			setSize(110, 40);
//			break;
//		case OFXSK_KEY_TAB:
//			label = "tab";
//			setSize(75, 40);
//			break;
//		case OFXSK_KEY_CAPS:
//			label = "caps";
//			setSize(85, 40);
//			break;
//		case OFXSK_KEY_DELETE:
//			label = "delete";
//			setSize(75, 40);
//			break;
//		case OFXSK_KEY_RETURN:
//			label = "return";
//			setSize(82, 40);
//			break;
//		default:
////			label.assign(_label);
//			label = string(1, key);
//			setSize(40, 40);
//			break;
//
//	}
//}


// initialize with keyCode, label
ofxMultiLanguageSoftKey::ofxMultiLanguageSoftKey(int _key, string _enLabel, string _krLabel, ofBaseApp* _ofApp) {
	enLabel = new string();
	krLabel = new string();
	labelFont = new ofxTrueTypeFontUC();
	labelFont->loadFont("AppleSDGothicNeo-Regular.otf", 12, true, true);

//	keyboard = _keyboard;
	ofapp = _ofApp;
	key = _key;
	roundness = 0;
	
	textColor = ofColor(0);
	textBGColor = ofColor(204);
	borderColor = ofColor(0);
	hoverColor = ofColor(153);
	clickColor = ofColor(255, 0, 0);
	isLastInRow = false;
	
	disableAppEvents();
	enableMouseEvents();
	
	padding = new int[4];
	setPadding(5, 5, 5, 5);
	
	switch(_key) {
		case OFXSK_KEY_SHIFT:
			enLabel->assign("shift");
			krLabel->assign("shift");
			setSize(110, 40);
			break;
		case OFXSK_KEY_TAB:
			enLabel->assign("tab");
			krLabel->assign("tab");
			setSize(75, 40);
			break;
		case OFXSK_KEY_CAPS:
			enLabel->assign("caps");
			krLabel->assign("caps");
			setSize(85, 40);
			break;
		case OFXSK_KEY_DELETE:
			enLabel->assign("delete");
			krLabel->assign("delete");
			setSize(75, 40);
			break;
		case OFXSK_KEY_RETURN:
			enLabel->assign("return");
			krLabel->assign("return");
			setSize(82, 40);
			break;
		default:
			enLabel->assign(_enLabel);
			krLabel->assign(_krLabel);
//			hangulLabel = string(1, key)
			setSize(40, 40);
			break;
	}
}

ofxMultiLanguageSoftKey::~ofxMultiLanguageSoftKey(){
	delete enLabel;
	delete krLabel;
	delete labelFont;
}


#pragma mark PADDING

//--------------------------------------------------------------
ofxMultiLanguageSoftKey& ofxMultiLanguageSoftKey::setPadding(int top, int right, int bottom, int left) {
	padding[OFXSK_PADDING_TOP] = top;
	padding[OFXSK_PADDING_RIGHT] = right;
	padding[OFXSK_PADDING_BOTTOM] = bottom;
	padding[OFXSK_PADDING_LEFT] = left;
	return *this;
}

//--------------------------------------------------------------
ofxMultiLanguageSoftKey& ofxMultiLanguageSoftKey::padLeft(int left) {
	padding[OFXSK_PADDING_LEFT] += left;
	return *this;
}
	
//--------------------------------------------------------------
ofxMultiLanguageSoftKey& ofxMultiLanguageSoftKey::padRight(int right) {
	padding[OFXSK_PADDING_RIGHT] += right;
	return *this;
}

#pragma mark APP EVENTS



//--------------------------------------------------------------
void ofxMultiLanguageSoftKey::draw(int _langState) {
	
	// Draw the background
	ofPushStyle();
	{
		ofFill();
		if(isMouseOver()) ofSetColor(hoverColor);
		else ofSetColor(textBGColor);
		ofDrawRectRounded(x, y, width, height, roundness);
		
		// Draw the outline.
		ofNoFill();
		ofSetColor(borderColor);
		ofDrawRectRounded(x, y, width, height, roundness);
		
		// Draw the actual letter
		ofSetColor(textColor);
		if(_langState == OFXVHK_LAYOUT_EN)		labelFont->drawString(*enLabel, x+10, y+height-10);
		else									labelFont->drawString(*krLabel, x+10, y+height-10);
	}
	ofPopStyle();
//	ofDrawBitmapString(label, x+10, y+height-10);

}




#pragma mark SETTERS

//--------------------------------------------------------------
ofxMultiLanguageSoftKey& ofxMultiLanguageSoftKey::setKey(char key) {
	this->key = key;
	return *this;
}

//--------------------------------------------------------------
ofxMultiLanguageSoftKey& ofxMultiLanguageSoftKey::setTextColor(ofColor c) {
	this->textColor = c;
	return *this;
}

//--------------------------------------------------------------
ofxMultiLanguageSoftKey& ofxMultiLanguageSoftKey::setTextBGColor(ofColor c) {
	this->textBGColor = c;
	return *this;
}

//--------------------------------------------------------------
ofxMultiLanguageSoftKey& ofxMultiLanguageSoftKey::setBorderColor(ofColor c) {
	this->borderColor = c;
	return *this;
}

//--------------------------------------------------------------
ofxMultiLanguageSoftKey& ofxMultiLanguageSoftKey::setHoverColor(ofColor c) {
	this->hoverColor = c;
	return *this;
}

//--------------------------------------------------------------
ofxMultiLanguageSoftKey& ofxMultiLanguageSoftKey::setClickColor(ofColor c) {
	this->clickColor = c;
	return *this;
}

//--------------------------------------------------------------
ofxMultiLanguageSoftKey& ofxMultiLanguageSoftKey::setRoundness(float r) {
	this->roundness = r;
	return *this;
}



#pragma mark MOUSE INTERACTION


//--------------------------------------------------------------
void ofxMultiLanguageSoftKey::onPress(int x, int y, int button) {
//	cout << "onPress" << " " << ofGetFrameNum() << endl;
	switch(key) {
		case OFXSK_KEY_SHIFT:
			
			break;
		case OFXSK_KEY_TAB: 
			ofapp->keyPressed(OF_KEY_TAB);
			break;
		case OFXSK_KEY_CAPS: 
			
			break;
		case OFXSK_KEY_DELETE: 
			ofapp->keyPressed(OF_KEY_BACKSPACE);
			break;
		case OFXSK_KEY_RETURN: 
			ofapp->keyPressed(OF_KEY_RETURN);
			break;
		case OFXSK_KEY_LANG:
			ofapp->keyPressed(OF_KEY_F12);
			cout << "LANG key Pressed" << endl;
			break;
		default:
			ofapp->keyPressed((int)key);
			break;
	}
	//ofNotifyEvent(ofEvents.keyPressed, (int)key, ofapp);
}

//--------------------------------------------------------------
void ofxMultiLanguageSoftKey::onRelease(int x, int y, int button) {
	switch(key) {
		case OFXSK_KEY_SHIFT:
			
			break;
		case OFXSK_KEY_TAB: 
			ofapp->keyReleased(OF_KEY_TAB);
			break;
		case OFXSK_KEY_CAPS: 
			
			break;
		case OFXSK_KEY_DELETE: 
			ofapp->keyReleased(OF_KEY_BACKSPACE);
			break;
		case OFXSK_KEY_RETURN: 
			ofapp->keyReleased(OF_KEY_RETURN);
			break;
		case OFXSK_KEY_LANG:
			ofapp->keyReleased(OF_KEY_F12);
			break;
		default:
			ofapp->keyReleased((int)key);
			break;
	}
	//ofNotifyEvent(ofEvents.keyReleased, (int)key, ofapp));
}

//--------------------------------------------------------------
void ofxMultiLanguageSoftKey::onReleaseOutside(int x, int y, int button) {

}
