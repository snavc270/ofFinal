#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    ofBackground(0);
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
#ifdef _USE_LIVE_VIDEO
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(ofGetWindowWidth(), ofGetWindowHeight());
#endif
    
    bLearnBackground = true;
    threshold= 20;
    
    time = ofGetElapsedTimef();
    
    
    
    
    for(int i=0; i<50; i++){
        Particle myParticle;
        myParticle.setInitialCondition(ofRandom(0,1000), ofRandom(0,300), 0, 0);
        
        particles.push_back(myParticle);
    }
 
    for(int i=0; i<50; i++){
        Particle myParticle2;
        myParticle2.setInitialCondition(ofRandom(0,1000), ofRandom(0,1000), 0, 0);
        
        particles2.push_back(myParticle2);
    }
    
    for(int i=0; i<50; i++){
        Particle myParticle3;
        myParticle3.setInitialCondition(ofRandom(0,1000), ofRandom(0,1000), 0, 0);
        
        particles3.push_back(myParticle3);
    }
    
}


//--------------------------------------------------------------
void ofApp::update(){
    
    if(time>25){
        r = 0;
        b = 0;
        g = 0; 
    }
  
    if(r <= 99){
        r++;
    }
    if(g <= 5){
        g ++;
    }
    
    if(b <= 5){
        b ++;
    }
    
    if(time>20){
        r --;
        b --;
        g --;
    }

    
   
    
    bool bNewFrame = false;
    
#ifdef _USE_LIVE_VIDEO
    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();
#endif
    
    if (bNewFrame){
#ifdef _USE_LIVE_VIDEO
        colorImg.setFromPixels(vidGrabber.getPixels(), ofGetWindowWidth(), ofGetWindowHeight());
#endif
        
        grayImage = colorImg;
        if (bLearnBackground == true){
            grayBg = grayImage;
            bLearnBackground = false;
        }
        
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
        
        contourFinder.findContours(grayDiff, 20, (ofGetWindowWidth()*ofGetWindowHeight())/3, 10, true);
    }
    
  
    ofFill();
    ofSetHexColor(0xffffff);
    
    for(int i=0; i<particles.size(); i++){
        particles[i].addAttraction(ofRandom(0,600),ofRandom(0,300), 1000, 0.05);
        particles[i].update();
        particles[i].resetForce();
        particles[i].addDampening();
        
        for(int j= 0; j< contourFinder.nBlobs; j++){
            particles[i].addRepulsion(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            if(time> 15){
                particles[i].addAttraction(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            }

        }
        
        
        
        
    }
    
    for(int i=0; i<particles2.size(); i++){
        particles2[i].addAttraction(ofRandom(0, 800),ofRandom(300, 800) , 1000, 0.05);
        particles2[i].update();
        particles2[i].resetForce();
        particles2[i].addDampening();
//        particles2[i].addRepulsion(mouseX, mouseY, 30, 35);
        
        for(int j= 0; j< contourFinder.nBlobs; j++){
            particles2[i].addRepulsion(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            if(time> 10){
                particles2[i].addAttraction(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            }
        }
        
    }
    
    for(int i=0; i<particles3.size(); i++){
        particles3[i].addAttraction(ofRandom(600,ofGetWindowWidth()),ofRandom(0,400) , 1000, 0.05);
        particles3[i].update();
        particles3[i].resetForce();
        particles3[i].addDampening();
//        particles3[i].addRepulsion(mouseX, mouseY, 30, 35);
        
        for(int j= 0; j< contourFinder.nBlobs; j++){
            particles3[i].addRepulsion(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            if(time> 5){
                particles3[i].addAttraction(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            }
        }
        
    }
    
   
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofColor colorOne(r+143, g+211, b+211);
    ofColor colorTwo(r, g, b);
    ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_LINEAR);
    
    
    

//    grayImage.draw(ofGetWindowWidth(), ofGetWindowHeight());
//
//    ofFill();
//    ofSetHexColor(0xffffff);
//    grayDiff.draw(360,280);
//    
//    ofFill();
//    ofSetHexColor(0x333333);
//    
//    contourFinder.draw();
    
    for (int i = 0; i < contourFinder.nBlobs; i++){
        contourFinder.blobs[i].draw(ofGetWindowWidth(), ofGetWindowHeight());
        
        ofSetColor(255);
//        if(contourFinder.blobs[i].hole){
//            ofDrawBitmapString("hole",
//                               contourFinder.blobs[i].boundingRect.getCenter().x + 360,
//                               contourFinder.blobs[i].boundingRect.getCenter().y + 540);
//        }
    }
    
    for(int i=0; i<particles.size(); i++){
        particles[i].draw();
    }
    
    for(int i=0; i<particles2.size(); i++){
        particles2[i].draw();
    }
    
    for(int i=0; i<particles3.size(); i++){
        particles3[i].draw();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
   
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
