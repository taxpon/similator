//
//  GameTimer.h
//  animationFunction
//
//  Created by Takuya Okamoto on 2014/09/06.
//
//

#ifndef __animationFunction__GameTimer__
#define __animationFunction__GameTimer__

#include <iostream>

#endif /* defined(__animationFunction__GameTimer__) */

#pragma once
#include "ofMain.h"


class GameTimer {
    
public:
    void setup();
    void draw();
    bool update();
    void start();
    
    ofVec2f position;
    ofTrueTypeFont font;
    int alpha;
    bool isEnd;

    unsigned long long timeLimitSec;
    unsigned long long remainSec;
    unsigned long long startClock;
    unsigned long long currentClock;
    string text;
    
private:
    string toString(int n);
};