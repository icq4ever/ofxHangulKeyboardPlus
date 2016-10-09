//
//  ofxHangulKeyboardPlus.h
//  ofxHangulKeyboardPlusExample
//
//  Created by icq4ever on 10/10/2016.
//
//

#ifndef __ofxHangulKeyboardPlusExample__ofxHangulKeyboardPlus__
#define __ofxHangulKeyboardPlusExample__ofxHangulKeyboardPlus__

#include "ofMain.h"

class ofxHangulKeyboardPlus{

public:
	
	static ofxHangulKeyboardPlus& one(){
		static ofxHangulKeyboardPlus instance; // Instantiated on first use.
		return instance;
	}

	ofxHangulKeyboardPlus();
	
protected:

};

#endif /* defined(__ofxHangulKeyboardPlusExample__ofxHangulKeyboardPlus__) */
