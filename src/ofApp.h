#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "HitAnimation.h"
#include "OpeningAnimation.h"
#include "EndingAnimation.h"
#include "GameTimer.h"
#include <list>

class ofApp : public ofBaseApp{

    static const int MAX_ANIMATION = 200;
    
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
        void hit(int score, float x, float y);
        bool isValidFrameROI(ofxCvColorImage*, ofxCvColorImage*);
    
        ofVideoGrabber vidGrabber;
    
    
        ofxCvColorImage colorImg;
        ofxCvColorImage colorBg;
        ofxCvColorImage lastFrame;
        ofxCvGrayscaleImage grayImage;
        ofxCvGrayscaleImage grayBg;
        ofxCvGrayscaleImage grayDiff;
        ofxCvContourFinder contourFinder;
        
        int threshold;
        int roteatedeg;
        bool bLearnBackground;
        bool bUpdateThreshold;
        bool bDisplayHit;
       
        float drawstartx;
        float drawendx;
        float drawstarty;
        float drawendy;
    
        bool bLeftBtnDown;
        bool bGetROI;
        bool bValidFrame;
        bool bFirstFrame;
        
        list<ofPoint> alreadyHit;
        list<ofPoint>::iterator ait;
        int totalScore;
        ofPoint point_center;
        ofImage similator_logo;
    
        // Hit
        HitAnimation hits[MAX_ANIMATION];
        int animationIndex;
        
        // OP
        OpeningAnimation opAnimation;
        void startOpeningAnimation();
        bool isRunningOpeningAnimation;
        
        // ED
        EndingAnimation edAnimation;
        void startEndingAnimation(int totalScore);
        bool isRunningEndingAnimation;
        
        // Timer
        GameTimer timerGraphic;
        void startTimer();
        bool isRunningTimer;
    
        int befor_timer;
    
};
