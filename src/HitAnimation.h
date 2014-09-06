//
//  HitAnimation.h
//  animationFunction
//
//  Created by Takuya Okamoto on 2014/08/26.
//
//

#ifndef __animationFunction__HitAnimation__
#define __animationFunction__HitAnimation__
#include <iostream>
#endif /* defined(__animationFunction__HitAnimation__) */
#pragma once
#include "ofMain.h"


class HitAnimation {
    
public:
    void setup();
    void draw();
    void update();
    void del();
    void start(int score,float x, float y);
    static void loadData();

    bool isEndingMode;
    
    string scoreText;
    int scoreInt;
    ofVec2f position;
    int alpha;
    int scoreAlpha;
    bool isEnd;
    float size;
    
    static ofTrueTypeFont scoreFont;    
    static ofImage hitImageGreen;
    static ofImage hitImageYellow;
    static ofImage hitImageRed;
    static ofSoundPlayer hitSound;
    
    HitAnimation();

private:
    string toString(int n);
    float scoreScale;
};