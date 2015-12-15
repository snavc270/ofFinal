#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    ofBackground(0);
    

    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    myfont.loadFont("always_forever.ttf", 32);
    
    
    potValue = "analog pin:";

    
    ard.connect("/dev/tty.usbmodem1421", 57600);
    
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino	= false;
    
#ifdef _USE_LIVE_VIDEO
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(ofGetWindowWidth(), ofGetWindowHeight());
#endif
    
    bLearnBackground = true;
    threshold= 20;
    
    time = ofGetElapsedTimef();
    
    
    
    
    for(int i=0; i<20; i++){
        Particle myParticle;
        myParticle.setInitialCondition(ofRandom(0,1000), ofRandom(0,300), 0, 0);
        
        particles.push_back(myParticle);
    }
    
 
    for(int i=0; i<20; i++){
        Particle myParticle2;
        myParticle2.setInitialCondition(ofRandom(0,1000), ofRandom(0,1000), 0, 0);
        
        particles2.push_back(myParticle2);
    }
    
    for(int i=0; i<50; i++){
        Particle myParticle3;
        myParticle3.setInitialCondition(ofRandom(0,1000), ofRandom(0,1000), 0, 0);
        
        particles3.push_back(myParticle3);
    }
    
    for(int i=0; i<10; i++){
        Particle myParticle4;
        myParticle4.setInitialCondition(ofRandom(0,1000), ofRandom(0,300), 0, 0);
        
        particles4.push_back(myParticle4);
    }
    
    for(int i=0; i<10; i++){
        Particle myParticle5;
        myParticle5.setInitialCondition(ofRandom(0,1000), ofRandom(0,300), 0, 0);
        
        particles5.push_back(myParticle5);
    }
    
    for(int i=0; i<10; i++){
        Particle myParticle6;
        myParticle6.setInitialCondition(ofRandom(0,1000), ofRandom(0,300), 0, 0);
        
        particles7.push_back(myParticle6);
    }
    
    for(int i=0; i<10; i++){
        Particle myParticle7;
        myParticle7.setInitialCondition(ofRandom(0,1000), ofRandom(0,300), 0, 0);
        
        particles7.push_back(myParticle7);
    }
    
    for(int i=0; i<10; i++){
        Particle myParticle8;
        myParticle8.setInitialCondition(ofRandom(0,1000), ofRandom(0,1000), 0, 0);
        
        particles8.push_back(myParticle8);
    }
    
    for(int i=0; i<10; i++){
        Particle myParticle9;
        myParticle9.setInitialCondition(ofRandom(0,1000), ofRandom(0,1000), 0, 0);
        
        particles9.push_back(myParticle9);
    }
    
    for(int i=0; i<10; i++){
        Particle myParticle10;
        myParticle10.setInitialCondition(ofRandom(0,1000), ofRandom(0,1000), 0, 0);
        
        particles10.push_back(myParticle10);
    }
    
    
    
}


//--------------------------------------------------------------
void ofApp::update(){
    updateArduino();
    
    
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
            if(time> 60){
                particles[i].addAttraction(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            }

        }
      
    }
    
    for(int i=0; i<particles2.size(); i++){
        particles2[i].addAttraction(ofRandom(0, 800),ofRandom(300, 800) , 1000, 0.05);
        particles2[i].update();
        particles2[i].resetForce();
        particles2[i].addDampening();

        
        for(int j= 0; j< contourFinder.nBlobs; j++){
            particles2[i].addRepulsion(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            if(time> 60){
                particles2[i].addAttraction(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            }
        }
        
    }
    
    for(int i=0; i<particles3.size(); i++){
        particles3[i].addAttraction(ofRandom(600,ofGetWindowWidth()),ofRandom(0,400) , 1000, 0.05);
        particles3[i].update();
        particles3[i].resetForce();
        particles3[i].addDampening();
        
        
        for(int j= 0; j< contourFinder.nBlobs; j++){
            particles3[i].addRepulsion(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            if(time> 60){
                particles3[i].addAttraction(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            }
        }
        
    }

    
    for(int i=0; i<particles4.size(); i++){
        particles4[i].addAttraction(ofRandom(0,600),ofRandom(0,300) , 1000, 0.05);
        particles4[i].update();
        particles4[i].resetForce();
        particles4[i].addDampening();
        
        
        for(int j= 0; j< contourFinder.nBlobs; j++){
            particles4[i].addRepulsion(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            if(time> 60){
                particles3[i].addAttraction(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            }
        }
        
    }
    
    
    for(int i=0; i<particles5.size(); i++){
        particles5[i].addAttraction(ofRandom(0, 800),ofRandom(300,800) , 1000, 0.05);
        particles5[i].update();
        particles5[i].resetForce();
        particles5[i].addDampening();

        
        for(int j= 0; j< contourFinder.nBlobs; j++){
            particles5[i].addRepulsion(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            if(time> 60){
                particles5[i].addAttraction(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            }
        }
        
    }
    

    
    
    for(int i=0; i<particles6.size(); i++){
        particles6[i].addAttraction(ofRandom(0, 600),ofRandom(0,300) , 1000, 0.05);
        particles6[i].update();
        particles6[i].resetForce();
        particles6[i].addDampening();
        
        
        for(int j= 0; j< contourFinder.nBlobs; j++){
            particles6[i].addRepulsion(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            if(time> 60){
                particles6[i].addAttraction(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            }
        }
    }
    
    for(int i=0; i<particles7.size(); i++){
        particles7[i].addAttraction(ofRandom(0, 600),ofRandom(0,300) , 1000, 0.05);
        particles7[i].update();
        particles7[i].resetForce();
        particles7[i].addDampening();
        
        
        for(int j= 0; j< contourFinder.nBlobs; j++){
            particles7[i].addRepulsion(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            if(time> 60){
                particles7[i].addAttraction(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            }
        }
    }
    
    for(int i=0; i<particles8.size(); i++){
        particles8[i].addAttraction(ofRandom(0,800),ofRandom(300,800), 1000, 0.05);
        particles8[i].update();
        particles8[i].resetForce();
        particles[i].addDampening();
        
        for(int j= 0; j< contourFinder.nBlobs; j++){
            particles8[i].addRepulsion(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            if(time> 60){
                particles8[i].addAttraction(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            }
            
        }
        
    }
    
    for(int i=0; i<particles9.size(); i++){
        particles[i].addAttraction(ofRandom(600,ofGetWindowWidth()),ofRandom(0,400), 1000, 0.05);
        particles9[i].update();
        particles9[i].resetForce();
        particles9[i].addDampening();
        
        for(int j= 0; j< contourFinder.nBlobs; j++){
            particles9[i].addRepulsion(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            if(time> 60){
                particles9[i].addAttraction(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            }
            
        }
        
    }
    
    for(int i=0; i<particles10.size(); i++){
        particles[i].addAttraction(ofRandom(600, ofGetWindowWidth()),ofRandom(0,400), 1000, 0.05);
        particles10[i].update();
        particles10[i].resetForce();
        particles10[i].addDampening();
        
        for(int j= 0; j< contourFinder.nBlobs; j++){
            particles10[i].addRepulsion(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            if(time> 60){
                particles10[i].addAttraction(contourFinder.blobs[j].boundingRect.getCenter().x, contourFinder.blobs[j].boundingRect.getCenter().y, 30, 35);
            }
            
        }
        
    }
   
}

void ofApp::setupArduino(const int &version){
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino = true;
    
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();

    ard.sendAnalogPinReporting(0, ARD_ANALOG);
    ard.sendDigitalPinMode(13, ARD_OUTPUT);
    
    ofAddListener(ard.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

void ofApp::updateArduino(){
    ard.update();
    
    if (bSetupArduino) {
        // fade the led connected to pin D11
        ard.sendPwm(11, (int)(128 + 128 * sin(ofGetElapsedTimef())));   // pwm...
    }
}

void ofApp::analogPinChanged(const int & pinNum) {
   
    potValue = "analog pin: " + ofToString(pinNum) + " = " + ofToString(ard.getAnalog(pinNum));
    lightsensor= ard.getAnalog(pinNum);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(lightsensor>600 && r<213 && g<143 && b<139){
        r++;
        g++;
        b++;
        

    }
    
    if(lightsensor<599 && lightsensor>251 && r>94 && g>0 && b>25){
        r--;
        g--;
        b--;
    }
    
    if(lightsensor<599 && lightsensor>251 && r<1 && g<1 && b<1){
        r++;
        g++;
        b++;
    }
    
    if(lightsensor<250 && r>0 && g>0 && b>0){
        r--;
        g--;
        b--;
    }
    
    ofColor colorOne(r+109, g, b+25);
    ofColor colorTwo(r, g, b);
    ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_LINEAR);
    
    ofSetColor(255, 255, 255);
    if (!bSetupArduino){
        myfont.drawString("arduino not ready...\n", 515, 40);
    } else {
        myfont.drawString(potValue + "\n" +  ofToString((int)(128 + 128 * sin(ofGetElapsedTimef()))), 515, 40);
    }

//    grayImage.draw(ofGetWindowWidth(), ofGetWindowHeight());
//
//    ofFill();
//    ofSetHexColor(0xffffff);
//    grayDiff.draw(360,280);
//    
    ofFill();
    ofSetHexColor(0x333333);

    ofSetColor(0);
//
    
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
        if(lightsensor>900){
            particles[i].clear();
            particles[i].setInitialCondition(ofRandom(0,1000), ofRandom(0,300), 0, 0);
            particles[i].pr --;
            particles[i].pg --;
            particles[i].pb --;
            
            
        }
    }
    
    for(int i=0; i<particles2.size(); i++){
        particles2[i].draw();
        if(lightsensor>250){
            particles2[i].clear();
            particles2[i].setInitialCondition(ofRandom(0,1000), ofRandom(0,1000), 0, 0);
            
        }
    }
    
    
    for(int i=0; i<particles3.size(); i++){
        particles3[i].draw();
        if(lightsensor>730){
            particles3[i].clear();
            particles3[i].setInitialCondition(ofRandom(0,1000), ofRandom(0,1000), 0, 0);
            
        }
    }
    
    for(int i=0; i<particles4.size(); i++){
        particles4[i].draw();
        if(lightsensor>700){
            particles4[i].clear();
            particles4[i].setInitialCondition(ofRandom(0,1000), ofRandom(0,300), 0, 0);
         }
    }
    
    for(int i=0; i<particles5.size(); i++){
        particles5[i].draw();
        if(lightsensor>750){
            particles5[i].clear();
            particles5[i].setInitialCondition(ofRandom(0,1000), ofRandom(0,300), 0, 0);
        }
    }

    for(int i=0; i<particles6.size(); i++){
        particles6[i].draw();
        if(lightsensor>850){
            particles6[i].clear();
            particles6[i].setInitialCondition(ofRandom(0,1000), ofRandom(0,1000), 0, 0);
        }
    }
    
 
    
    for(int i=0; i<particles7.size(); i++){
        particles7[i].draw();
        if(lightsensor>500){
            particles7[i].clear();
            particles7[i].setInitialCondition(ofRandom(0,1000), ofRandom(0,1000), 0, 0);
            
        }
    }

    for(int i=0; i<particles8.size(); i++){
        particles8[i].draw();
        if(lightsensor>350){
            particles8[i].clear();
            particles8[i].setInitialCondition(ofRandom(0,1000), ofRandom(0,1000), 0, 0);
            
        }
    }
    
    for(int i=0; i<particles9.size(); i++){
        particles9[i].draw();
        if(lightsensor>200){
            particles9[i].clear();
            particles9[i].setInitialCondition(ofRandom(0,1000), ofRandom(0,1000), 0, 0);
            }
    }
    
    for(int i=0; i<particles10.size(); i++){
        particles10[i].draw();
        if(lightsensor>100){
            particles10[i].clear();
            particles10[i].setInitialCondition(ofRandom(0,1000), ofRandom(0,1000), 0, 0);
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    switch (key){
        case 'f':
    ofToggleFullscreen();
    break;
    }
    
    switch(key){
            case 'd':
            contourFinder.draw();
    }
    
   
    switch(key){
        case 'c':
            ofSetColor(50);
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
        ard.sendDigital(13, ARD_LOW);
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
