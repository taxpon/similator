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
#include "config.h"

void EndingAnimation::setup() {
    // フォント設定
    ofTrueTypeFont::setGlobalDpi(700);//72);
	font.loadFont("kremlin.ttf", 10, true, true, true);
    ptsFont.loadFont("kremlin.ttf", 5, true, true, true);
    font.setLineHeight(18.0f);
    font.setLetterSpacing(1.037);
        
    bgImg.loadImage("total_score.png");
    drumrollSound.loadSound("dramroll.wav");
    newScoreImg.loadImage("newscore.png");
}

void EndingAnimation::start(int score) {
    drumrollSound.play();
    alpha = 255;
    position.x = DWIDTH + 1280 /2.0;
    position.y = ofGetHeight() / 2;
//    scoreText = toString(score);
    totalScore = score;
    startTime = ofGetElapsedTimeMillis();
    elapsedTime = 0;
}

// -------- loop --------
bool EndingAnimation::update() { //アニメ−ションが終わったらfalseを返す。
    currentTime = ofGetElapsedTimeMillis();
    elapsedTime = currentTime - startTime;

    if (elapsedTime < 2000) {
        randScore = ofRandom(9999);
        scoreText = toString(randScore);
        return true;
    }
    else {
        if (isNewScore) {
            if(int(currentTime / 400) % 2 == 0) newScoreAlpha = 0;
            else newScoreAlpha = 255;
        }
        if(elapsedTime < 6000) {
            scoreText = toString(totalScore);
            return true;
        } else {
            return false;
        }
    }
}

void EndingAnimation::draw() {
    if (alpha > 0) {
        ofSetColor(255, 255, 255, alpha);

        bgImg.draw(1440, 0, 1280, 720);
        
        ofSetColor(0, 0, 0, alpha);
        // total score
        ofPushMatrix();
            ofTranslate(position.x, position.y);
            ofRotateZ(-90);
            font.drawStringCentered(scoreText, 90, 0);
            ptsFont.drawString("pts", 50, 100);
        
        if (isNewScore && elapsedTime > 2000) {
            ofSetColor(255,255,255, newScoreAlpha);
            newScoreImg.draw(-120, 100);
        }
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
