//
//  OpeningAnimation.h
//  animationFunction
//
//  Created by Takuya Okamoto on 2014/08/28.
//
//

#ifndef __animationFunction__OpeningAnimation__
#define __animationFunction__OpeningAnimation__
#include <iostream>
#endif /* defined(__animationFunction__OpeningAnimation__) */
#pragma once
#include "ofMain.h"


class OpeningAnimation {
    
public:
    void setup();
    void draw();
    bool update();
    void start();
    
    ofVec2f position;
    ofTrueTypeFont font;
    int alpha;
    bool isEnd;
    
    float textScale;
    string text;
    
private:
    string toString(int n);
    int step;
};