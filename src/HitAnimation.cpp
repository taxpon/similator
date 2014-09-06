//
//  HitAnimation.cpp
//  animationFunction
//
//  Created by Takuya Okamoto on 2014/08/26.
//
//

#include "HitAnimation.h"
#include <sstream>
#include <string>

#define SIZE_INCREACE_SPEED 2.5
#define MAX_SIZE 100
#define ENDING_MODE_ALPHA 100

ofImage HitAnimation::hitImageGreen;
ofImage HitAnimation::hitImageYellow;
ofImage HitAnimation::hitImageRed;
ofSoundPlayer HitAnimation::hitSound;
ofTrueTypeFont HitAnimation::scoreFont;

void HitAnimation::loadData(){
    
    // Fonts
    ofTrueTypeFont::setGlobalDpi(700);//72);
	scoreFont.loadFont("kremlin.ttf", 10, true, true, true);
    scoreFont.setLineHeight(18.0f);
    scoreFont.setLetterSpacing(1.037);
    
    // Images
    hitImageGreen.loadImage("green.png");
    hitImageYellow.loadImage("yellow.png");
    hitImageRed.loadImage("red.png");
    hitSound.loadSound("coin.wav");
    
    // Sounds
    hitSound.setMultiPlay(true);
}

HitAnimation::HitAnimation(){
    alpha = 0;
    scoreAlpha = 0;
    scoreScale = 0;
    size = 0;
}

void HitAnimation::start(int score,float x, float y) {
    alpha = 255;
    scoreText = toString(score);
    scoreInt = score;
    position.x = x;
    position.y = y;
    
    // Play sound
    hitSound.play();
}

// -------- loop --------
void HitAnimation::update() {
    if (alpha > 0) {
        if (size <= MAX_SIZE) {
            size += SIZE_INCREACE_SPEED;
        }
        else {
            //            alpha -= 5;f
        }
        if (scoreAlpha <= 255) {
            scoreAlpha += 5;
            scoreScale += 0.02;
        }
    }
}

void HitAnimation::draw() {
    if (alpha > 0) {
        if(scoreInt > 10000){
            ofSetColor(113, 188, 76, scoreAlpha);
        } else if(scoreInt > 5000){
            ofSetColor(243, 219, 57, scoreAlpha);
        } else {
            ofSetColor(236, 66, 61, scoreAlpha);
        }
        if (isEndingMode) ofSetColor(0, 255, 0, ENDING_MODE_ALPHA);
        float scoreX = position.x - 65;
        float scoreY = position.y;
        ofPushMatrix();
            ofTranslate(scoreX, scoreY);
            ofScale(scoreScale, scoreScale, 1);
            ofRotateZ(- 90);
            float fontWidth = scoreFont.stringWidth(scoreText);
            scoreFont.drawString(scoreText, -fontWidth/2, 0);
        ofPopMatrix();
        
        //色の設定
        ofSetColor(255, 255, 255);
        if (isEndingMode) ofSetColor(255, 255, 255, ENDING_MODE_ALPHA);
        float imgX = position.x - ((size + SIZE_INCREACE_SPEED) / 2);
        float imgY = position.y - ((size + SIZE_INCREACE_SPEED) / 2);
        if(scoreInt > 10000){
            HitAnimation::hitImageGreen.draw(imgX, imgY, size*2.0, size*2.0);
        } else if(scoreInt > 6000){
            HitAnimation::hitImageYellow.draw(imgX, imgY, size*1.5, size*1.5);
        } else {
            HitAnimation::hitImageRed.draw(imgX, imgY, size, size);
        }
    }
}

void HitAnimation::del(){
    alpha = 0;
}



// -------------------- private ---------------------
string HitAnimation::toString(int n) {
    std::ostringstream stream;
    stream << n;
    std::string result = stream.str();
    return result;
}
