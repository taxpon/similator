#include "ofApp.h"
#include "config.h"

#define CWIDTH 640
#define CHEIGHT 480
#define COLORCH 3
#define FRAME_DIFFERENCE 50.0
#define DTHRESHOLD 30.0


void ofApp::hit(int score, float x, float y){
    hits[animationIndex].start(score, x, y);
    if (++animationIndex == MAX_ANIMATION) animationIndex = 0;
    totalScore += score;
}

bool ofApp::isValidFrameROI(ofxCvColorImage* prevFrame, ofxCvColorImage* curFrame){
    
    unsigned char* prev_pixels = (*prevFrame).getRoiPixels();
    unsigned char* cur_pixels = (*curFrame).getRoiPixels();
    float diff_sum = 0;

    float roiwidth = drawendx - drawstartx;
    float roiheight = drawendy - drawstarty;
    float pixel_size = roiwidth * roiheight * 3;

    for(int i=0; i < pixel_size; i++){
        float diff_pixel = fabs(prev_pixels[i] - cur_pixels[i]);
        diff_sum += diff_pixel;
    }
    
    diff_sum /= pixel_size;
    //printf("Pixeles: %f, Frame diff: %f\n", pixel_size, diff_sum);
    
    if (diff_sum > FRAME_DIFFERENCE) {
        // Too big difference between two frames
        //printf("Invlid frame: %f\n", diff_sum);
        return false;
    } else {
        // Valid frame
        lastFrame = (*curFrame);
        return true;
    }
}

void ofApp::startOpeningAnimation(){
    opAnimation.start();
    isRunningOpeningAnimation = true;
}

void ofApp::startTimer() {
    timerGraphic.start();
    totalScore = 0;
    isRunningTimer = true;
    bDisplayHit = true;
    printf("Start Timer\n");
}

void ofApp::startEndingAnimation(int totalScore){
    edAnimation.start(totalScore);
    isRunningEndingAnimation = true;
    bDisplayHit = false;
    
    for (int i = 0; i < MAX_ANIMATION; i++) {
        hits[i].isEndingMode = true;
    }
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(255,255,255);
    ofEnableSmoothing();
    animationIndex = 0;
    
    vidGrabber.setVerbose(true);
    vidGrabber.setDeviceID(0);
    vidGrabber.initGrabber(CWIDTH, CHEIGHT);
    
    colorImg.allocate(CWIDTH, CHEIGHT);
    colorBg.allocate(CWIDTH, CHEIGHT);
    lastFrame.allocate(CWIDTH, CHEIGHT);
    grayImage.allocate(CWIDTH, CHEIGHT);
    grayBg.allocate(CWIDTH, CHEIGHT);
    grayDiff.allocate(CWIDTH, CHEIGHT);
    
    bLearnBackground = true;
    bLeftBtnDown = false;
    bGetROI = false;
    bDisplayHit = false;
    bFirstFrame = true;
    threshold = 50;
    roteatedeg = 0;
    
    // module setup
    timerGraphic.setup();
    opAnimation.setup();
    edAnimation.setup();
    
    // Initialization
    HitAnimation::loadData();
}

//--------------------------------------------------------------
void ofApp::update(){

    
    bool bNewFrame = false;
    
    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();
    
    if(bGetROI){
        float roiwidth = drawendx - drawstartx;
        float roiheight = drawendy - drawstarty;
        colorImg.setROI(drawstartx, drawstarty, roiwidth, roiheight);
        colorBg.setROI(drawstartx, drawstarty, roiwidth, roiheight);
        lastFrame.setROI(drawstartx, drawstarty, roiwidth, roiheight);
        grayImage.setROI(drawstartx, drawstarty, roiwidth, roiheight);
        grayBg.setROI(drawstartx, drawstarty, roiwidth, roiheight);
        grayDiff.setROI(drawstartx, drawstarty, roiwidth, roiheight);
    }

    if(bNewFrame){
        colorImg.setFromPixels(vidGrabber.getPixels(), CWIDTH, CHEIGHT);
        
        if(bFirstFrame){
            lastFrame = colorImg;
            bFirstFrame = false;
        }
        
        grayImage = colorImg;
        if(bLearnBackground == true){
            colorBg = colorImg;
            grayBg = grayImage;
            bLearnBackground = false;
        }
        
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
        
        contourFinder.findContours(grayDiff, 20, ((CWIDTH+20)*CHEIGHT)/3, 10, true);
    }
    
    // Hit Animation
    for (int i = 0; i < MAX_ANIMATION; i++) {
        hits[i].update();
    }
    
    // Opening Animation
    if (isRunningOpeningAnimation) {
        if (! opAnimation.update()) {
            isRunningOpeningAnimation = false;
            startTimer();
        }
    }
    
    // Timer
    if (isRunningTimer) {
        if (! timerGraphic.update()) {
            isRunningTimer = false;
            startEndingAnimation(totalScore);
        }
    }
    
    // Ending Animation
    if (isRunningEndingAnimation) {
        if (! edAnimation.update()) {
            isRunningEndingAnimation = false;
        }
    }
    
    bValidFrame = isValidFrameROI(&colorBg, &colorImg);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofSetHexColor(0xffffff);
//    colorImg.setROI(ofRect(0, 0, 120, 120));
    //colorImg.setROI(ofRect(0, 0, 120, 120));
       ofPushMatrix();
    //ofTranslate(-(ofGetWidth()/2.0 - CHEIGHT/2.0), -(ofGetHeight()/2.0 - CWIDTH/2.0));
    //ofTranslate(ofGetWidth()/2.0, ofGetHeight()/2.0);
    //ofRotate(roteatedeg);
    //ofTranslate(-CWIDTH/2.0, -CHEIGHT/2.0);
    
    
    if (bGetROI) {
        colorImg.drawROI(0,0);
        //colorImg.drawROI(DWIDTH, 0);
    } else {
        colorImg.draw(0,0);
    }
    
    //
    ofPopMatrix();
    grayBg.draw(0, 480, 240, 180);
    colorBg.draw(180, 480, 240, 180);
    
    //grayImage.draw(360, 20);

    //grayDiff.draw(360, 280);
    
    
    //ofFill();
    //ofSetHexColor(0x333333);
    //ofRect(0, CHEIGHT, CWIDTH, CHEIGHT);
    //ofSetHexColor(0xffffff);
    
    if (!bValidFrame) {
        return;
    }
    
    for (int i = 0; i < contourFinder.nBlobs; i++) {
        contourFinder.blobs[i].draw(0, 0);

        float score_area = contourFinder.blobs[i].area;
        //printf("score_area: %f\n", score_area);
        ofPoint detectPoint = ofPoint(
                                      contourFinder.blobs[i].boundingRect.getCenter().x,
                                      contourFinder.blobs[i].boundingRect.getCenter().y
                                      );
        
        ofSetColor(255);
//        ofDrawBitmapString("(X)",
//                           detectPoint.x,
//                           detectPoint.y);

        
        if (bDisplayHit) {
            if( (int)alreadyHit.size() == 0){
                // No item in list
                alreadyHit.push_back(detectPoint);
                hit(score_area * score_area,
                    detectPoint.x * 1280/(drawendx - drawstartx) + DWIDTH,
                    detectPoint.y * 800/(drawendy - drawstarty));
            } else {
                // At least one item in list
                for (ait = alreadyHit.begin(); ait != alreadyHit.end(); ait++) {
                    
                    if (detectPoint.distance(*ait) < DTHRESHOLD) {
                        break;
                    }
                }
                
                if (ait == alreadyHit.end()) {
                    alreadyHit.push_back(detectPoint);
                    hit(score_area * score_area,
                        detectPoint.x * 1280/(drawendx - drawstartx) + DWIDTH,
                        detectPoint.y * 720/(drawendy - drawstarty));
                }
            }
        }
   }
    
    // Hit Animation
    for (int i = 0; i < MAX_ANIMATION; i++) {
        if (bDisplayHit) {
            hits[i].draw();
        }
    }
    
    // Opening Animation
    if (isRunningOpeningAnimation) {
        opAnimation.draw();
    }
    
    // Timer
    if (isRunningTimer) {
        timerGraphic.draw();
    }
    
    // Ending Animation
    if (isRunningEndingAnimation) {
        edAnimation.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key) {
        case ' ':
            bLearnBackground = true;
            break;
        case '+':
            threshold ++;
            if (threshold > 255) {
                threshold = 255;
            }
            printf("thresould = %d\n", threshold);
            break;
        case '-':
            threshold --;
            if (threshold < 0) {
                threshold == 0;
            }
            printf("thresould = %d\n", threshold);
            break;
        case 't':
            startTimer();
            break;
        case 'r':
            for (int i = 0; i < MAX_ANIMATION; i++) {
                hits[i].del();
            }
            alreadyHit.clear();
            bDisplayHit = false;
            break;
        case 'o':
            startOpeningAnimation();
            break;
        case 'h':
            // Demonstration Mode
            startOpeningAnimation();
            break;
        case 'd':
            // Debug Mode
            bDisplayHit = !bDisplayHit;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    bLeftBtnDown = true;
    drawstartx = x;
    drawstarty = y;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    bLeftBtnDown = false;
    drawendx = x;
    drawendy = y;
    bGetROI = true;
    bLeftBtnDown = true;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
