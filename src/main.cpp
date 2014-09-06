#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
	//ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
    
    
    ofAppGLFWWindow window;
    window.setMultiDisplayFullscreen(true);
    //ofSetupOpenGL(&window,1440+1280,768,OF_FULLSCREEN);
    
//    ofAppGLFWWindow win;
//	win.setMultiDisplayFullscreen(true);
//    
	ofSetupOpenGL(&window, 1440+1280,800, OF_WINDOW);
	ofRunApp(new ofApp());

}
