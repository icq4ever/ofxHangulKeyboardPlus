/*
 *  ofxSoftKey.cpp
 *  softKeyboardExample
 *
 *  Created by Jeffrey Crouse on 11/9/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *
 */

#include "ofxSoftKey.h"

#pragma mark CONSTRUCTORS

//--------------------------------------------------------------
//ofxSoftKey::ofxSoftKey(int _key, ofBaseApp* _ofApp) {
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
ofxSoftKey::ofxSoftKey(int _key, string _label, ofBaseApp* _ofApp) {
	label = new string();
	hangulLabel = new string();
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
			label->assign("shift");
			setSize(110, 40);
			break;
		case OFXSK_KEY_TAB:
			label->assign("tab");
			setSize(75, 40);
			break;
		case OFXSK_KEY_CAPS:
			label->assign("caps");
			setSize(85, 40);
			break;
		case OFXSK_KEY_DELETE:
			label->assign("delete");
			setSize(75, 40);
			break;
		case OFXSK_KEY_RETURN:
			label->assign("return");
			setSize(82, 40);
			break;
		default:
			label->assign(_label);
//			hangulLabel = string(1, key)
			setSize(40, 40);
			break;
	}
}

ofxSoftKey::~ofxSoftKey(){
	delete label;
	delete labelFont;
	delete hangulLabel;
}


#pragma mark PADDING

//--------------------------------------------------------------
ofxSoftKey& ofxSoftKey::setPadding(int top, int right, int bottom, int left) {
	padding[OFXSK_PADDING_TOP] = top;
	padding[OFXSK_PADDING_RIGHT] = right;
	padding[OFXSK_PADDING_BOTTOM] = bottom;
	padding[OFXSK_PADDING_LEFT] = left;
	return *this;
}

//--------------------------------------------------------------
ofxSoftKey& ofxSoftKey::padLeft(int left) {
	padding[OFXSK_PADDING_LEFT] += left;
	return *this;
}
	
//--------------------------------------------------------------
ofxSoftKey& ofxSoftKey::padRight(int right) {
	padding[OFXSK_PADDING_RIGHT] += right;
	return *this;
}



#pragma mark APP EVENTS



//--------------------------------------------------------------
void ofxSoftKey::draw() {
	
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
		labelFont->drawString(*label, x+10, y+height-10);
	}
	ofPopStyle();
//	ofDrawBitmapString(label, x+10, y+height-10);

}




#pragma mark SETTERS

//--------------------------------------------------------------
ofxSoftKey& ofxSoftKey::setKey(char key) {
	this->key = key;
	return *this;
}

//--------------------------------------------------------------
ofxSoftKey& ofxSoftKey::setTextColor(ofColor c) {
	this->textColor = c;
	return *this;
}

//--------------------------------------------------------------
ofxSoftKey& ofxSoftKey::setTextBGColor(ofColor c) {
	this->textBGColor = c;
	return *this;
}

//--------------------------------------------------------------
ofxSoftKey& ofxSoftKey::setBorderColor(ofColor c) {
	this->borderColor = c;
	return *this;
}

//--------------------------------------------------------------
ofxSoftKey& ofxSoftKey::setHoverColor(ofColor c) {
	this->hoverColor = c;
	return *this;
}

//--------------------------------------------------------------
ofxSoftKey& ofxSoftKey::setClickColor(ofColor c) {
	this->clickColor = c;
	return *this;
}

//--------------------------------------------------------------
ofxSoftKey& ofxSoftKey::setRoundness(float r) {
	this->roundness = r;
	return *this;
}



#pragma mark MOUSE INTERACTION


//--------------------------------------------------------------
void ofxSoftKey::onPress(int x, int y, int button) {
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
void ofxSoftKey::onRelease(int x, int y, int button) {
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
void ofxSoftKey::onReleaseOutside(int x, int y, int button) {

}
