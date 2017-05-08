#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_SILENT);
	ofSetWindowTitle("ofxHangulKeyboardPlusExample");

	
	textFont = new ofxTrueTypeFontUC();
	textFont->loadFont("AppleSDGothicNeo-Regular.otf", 30, true, true);
	
	lastKeyComboCheckTimer = ofGetElapsedTimeMillis();
	
	keyboard = new ofxHangulKeyboardPlus();
	keyboard->setup(this, OFXVHK_LAYOUT_EN);
	inputMethodType = keyboard->getInputMethod();
}

//--------------------------------------------------------------
void ofApp::update(){
	stringBox.assign(keyboard->getBuffer());
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0x222222);

	// draw keyboard
	keyboard->draw(ofGetWidth()/2-784/2, 350);
	keyboard->displayInputLanguageHUD(ofGetWidth()-90, 30);

	// draw typed string
	ofSetHexColor(0xFFFFFF);
	ofFill();
	
	textFont->drawStringAsShapes(stringBox, 50, 120);
}

void ofApp::exit(){
	delete textFont;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	// shorcut for toggle input language
	if(key == OF_KEY_F12){
		if(ofGetElapsedTimeMillis() - lastKeyComboCheckTimer > 50){
			// toggle input language
			keyboard->toggleKeyboard();
			lastKeyComboCheckTimer = ofGetElapsedTimeMillis();		// prevent change too fast
		}
	}
	
	keyboard->sendKey(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ }
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){ }
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){ }
//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){ }
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){ }
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){ }
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ }
