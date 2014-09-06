//
//  OpeningAnimation.cpp
//  animationFunction
//
//  Created by Takuya Okamoto on 2014/08/28.
//
//

#include "OpeningAnimation.h"
#include <sstream>
#include <string>
#include "config.h"


void OpeningAnimation::setup() {
    // フォント設定
    ofTrueTypeFont::setGlobalDpi(700);//72);
	font.loadFont("kremlin.ttf", 10, true, true, true);
    font.setLineHeight(18.0f);
    font.setLetterSpacing(1.037);
}




void OpeningAnimation::start() {
    alpha = 255;
    step = 0;
    textScale = 0;
    position.x = DWIDTH + 1280 /2.0;
    position.y = ofGetHeight() / 2 - 100;
    text = "Ready";
}





// -------- loop --------

bool OpeningAnimation::update() { //アニメ−ションが終わったらfalseを返す。
    if (alpha > 0) {
        alpha -= 2.5;
        textScale += 0.02;
        return true;
    }
    else if (step == 0) {
        step = 1;
        alpha = 255;
        textScale = 0;
        text = "GO!!!";
        return true;
    }
    else {
        return false;
    }
}

void OpeningAnimation::draw() {
    if (alpha > 0) {
        ofSetColor(0,0,0, alpha);
        
        ofPushMatrix();
            ofTranslate(position.x, position.y);
            ofRotateZ(-90);
            ofScale(textScale, textScale, 1);
            font.drawString(text, -font.stringWidth(text)/2, font.getLineHeight());
        ofPopMatrix();
    }
}





// -------------------- private ---------------------
string OpeningAnimation::toString(int n) {
    std::ostringstream stream;
    stream << n;
    std::string result = stream.str();
    return result;
}
