//
//  GameTimer.cpp
//  animationFunction
//
//  Created by Takuya Okamoto on 2014/09/06.
//
//

#include "GameTimer.h"
#include <sstream>
#include <string>
#include "config.h"

#define TIME_LIMIT_SEC 5
#define CAPTURE false


void GameTimer::setup() {
    // フォント設定
    ofTrueTypeFont::setGlobalDpi(700);//72);
    font.setLineHeight(18.0f);
    font.setLetterSpacing(1.037);
}

void GameTimer::start() {
    alpha = 105;
    remainSec = TIME_LIMIT_SEC;
    startClock = ofGetElapsedTimeMillis();
    position.x = DWIDTH + 120;
    position.y = 180;
    scale = 1;
    isLastMode = false;
    lastStep = 0;
    isEndAllAnimation = false;
    font.loadFont("kremlin.ttf", 20, true, true, true);
}

void GameTimer::setLastMode() {
    isLastMode = true;
    font.loadFont("kremlin.ttf", 40, true, true, true);
    position.x = ofGetWidth() / 2;
    position.y = ofGetHeight() / 2;
}

// -------- loop --------

bool GameTimer::update() {
    if (remainSec > 0) {
        
        currentClock = ofGetElapsedTimeMillis();
        timeLimitSec = TIME_LIMIT_SEC;
        unsigned long long msec = currentClock - startClock;
        unsigned long long totalSec = msec / 1000;
        remainSec = timeLimitSec - totalSec;
        unsigned long long sec = remainSec;
        
        //sec string
        std::ostringstream stream_sec;
        stream_sec << std::setfill('0') << std::setw(2) << sec;
        std::string s_str = stream_sec.str();
        text = s_str;
        
        //3.2.1...
        if (remainSec <= 3) {
            if (!isLastMode) setLastMode();
            if (remainSec == 3 && !lastStep) {
                lastStep = 3;
                scale = 0.1;
                alpha = 255;
            }
            if (remainSec == 2 && lastStep == 3) {
                lastStep = 2;
                scale = 0.1;
                alpha = 255;
            }
            if (remainSec == 1 && lastStep == 2) {
                lastStep = 1;
                scale = 0.1;
                alpha = 255;
            }
            if (scale <= 1) {
                scale += 0.05;
            }
            alpha -= 5;
        }

        return true;
    }
    //timeup!
    else if(!isEndAllAnimation) {
        if (lastStep == 1) {
            // Save drawed Image
            lastStep = 0;
            text = "time up!";
            font.loadFont("kremlin.ttf", 13, true, true, true);
            scale = 0.1;
            alpha = 255;
            if(CAPTURE)ofSaveFrame();
        }
        if (scale <= 1) {
            scale += 0.05;
        }
        alpha -= 1.2;
        if (alpha <= 0) {
            isEndAllAnimation = true;
        }
        return true;
    }
    else {
        return false;
    }
}

void GameTimer::draw() {
    if (alpha > 0) {
        ofSetColor(0,0,0, alpha);
        ofPushMatrix();
            ofTranslate(position.x, position.y);
            ofScale(scale, scale, 1);
            ofRotateZ(-90);
            float fontWidth = font.stringWidth(text);
            float fontHeight = font.stringHeight(text);
            font.drawString(text , -fontWidth/2, fontHeight/2);
        ofPopMatrix();
        
    }
}

// -------------------- private ---------------------
string GameTimer::toString(int n) {
    std::ostringstream stream;
    stream << n;
    std::string result = stream.str();
    return result;
}


