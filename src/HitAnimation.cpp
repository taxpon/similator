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
#define HIT_DURATION 0.2

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
    time_zoom = 0;
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
        if (size <= MAX_SIZE && time_zoom <= HIT_DURATION) {
            //size += SIZE_INCREACE_SPEED;
            time_zoom += 0.01;
            size = easeInOut(time_zoom, 0, MAX_SIZE, HIT_DURATION);
            scoreAlpha = easeInOut(time_zoom, 0, 255, HIT_DURATION);
            scoreScale = easeInOut(time_zoom, 0, 1, HIT_DURATION);
        }
    }
}

void HitAnimation::draw() {
    if (alpha > 0) {
        if(scoreInt > 10000){
            ofSetColor(163, 238, 126, scoreAlpha);
        } else if(scoreInt > 5000){
            ofSetColor(255, 255, 107, scoreAlpha);
        } else {
            ofSetColor(255, 116, 101, scoreAlpha);
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
        } else if(scoreInt > 5000){
            HitAnimation::hitImageYellow.draw(imgX, imgY, size*1.5, size*1.5);
        } else {
            HitAnimation::hitImageRed.draw(imgX, imgY, size, size);
        }
    }
}

void HitAnimation::del(){
    alpha = 0;
    time_zoom = 0;
}

// -------------------- private ---------------------
string HitAnimation::toString(int n) {
    std::ostringstream stream;
    stream << n;
    std::string result = stream.str();
    return result;
}

float HitAnimation::easeInOut(float t, float b, float e, float d){
    t /= d/2.0;
    if(t < 1){
        return (e/2.0)*t*t +b;
    } else {
        t = t-1;
        return -e/2.0 * (t*(t-2) - 1) + b;
    }
}

