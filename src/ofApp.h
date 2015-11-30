#pragma once

#include "ofMain.h"
#include "particles.hpp" 
#include "ofxOpenCv.h"

#define _USE_LIVE_VIDEO

class ofApp : public ofBaseApp{

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
 
    int r;
    int g;
    int b;
    
#ifdef _USE_LIVE_VIDEO
    ofVideoGrabber      vidGrabber;
#endif
    
    ofxCvColorImage     colorImg;
    ofxCvGrayscaleImage     grayImage;
    ofxCvGrayscaleImage     grayBg;
    ofxCvGrayscaleImage     grayDiff;
    
    ofxCvContourFinder      contourFinder;
    
    int                     threshold;
    bool                    bLearnBackground;
    
    float time;
    bool bTimerReached;
    vector<Particle> particles;
    vector<Particle> particles2;
    vector<Particle> particles3; 
  
		
};
