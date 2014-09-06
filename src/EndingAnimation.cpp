//
//  EndingAnimation.cpp
//  animationFunction
//
//  Created by Takuya Okamoto on 2014/08/28.
//
//

#include "EndingAnimation.h"
#include <sstream>
#include <string>


void EndingAnimation::setup() {
    // フォント設定
    ofTrueTypeFont::setGlobalDpi(700);//72);
	font.loadFont("kremlin.ttf", 10, true, true, true);
    ptsFont.loadFont("kremlin.ttf", 5, true, true, true);
    font.setLineHeight(18.0f);
    font.setLetterSpacing(1.037);
        
    bgImg.loadImage("total_score.png");
}




void EndingAnimation::start(int score) {
    alpha = 255;
    position.x = 1440 + 1280 /2.0;
    position.y = ofGetHeight() / 2;
//    scoreText = toString(score);
    totalScore = score;
    startTime = ofGetElapsedTimeMillis();
    elapsedTime = 0;
}





// -------- loop --------

bool EndingAnimation::update() { //アニメ−ションが終わったらfalseを返す。
    if (elapsedTime < 1000) {
        
        currentTime = ofGetElapsedTimeMillis();
        elapsedTime = currentTime - startTime;
        randScore = ofRandom(9999);
        scoreText = toString(randScore);
        
        return true;
    }
    else if(elapsedTime < 6000) {
        scoreText = toString(totalScore);
        return true;
    }
    else {
        return false;//アニメ−ション終了
    }
}

void EndingAnimation::draw() {
    if (alpha > 0) {
        ofSetColor(0,0,0, alpha);

        bgImg.draw(1440, 0, 1280, 720);
        
        // total score
        ofPushMatrix();
            ofTranslate(position.x, position.y);
            ofRotateZ(-90);
            font.drawString(scoreText, (-font.stringWidth(scoreText)/2) - 50, 0);
            ptsFont.drawString("pts", 100, 0);
        ofPopMatrix();
    }
}





// -------------------- private ---------------------
string EndingAnimation::toString(int n) {
    std::ostringstream stream;
    stream << n;
    std::string result = stream.str();
    return result;
}
