//
//  particles.cpp
//  particle_test
//
//  Created by Courtney Snavely on 11/21/15.
//
//

#include "particles.hpp"
#include "ofMain.h"

Particle::Particle(){
    setInitialCondition(ofGetWindowWidth()/2, ofGetWindowHeight()/2, 0, 0);
    
    dampening= 0.09; 
   
    angle=0;

   
 
}

void Particle::addAttraction(float px, float py, float radius, float strength){
    ofVec2f posOfForce;
    posOfForce.set(px,py);
    
    ofVec2f diff= pos - posOfForce;
    
    if(diff.length() <radius){
        float percent= 1- (diff.length() / radius);
        diff.normalize();
        force.x -= diff.x* percent *strength;
        force.y -= diff.y * percent *strength;
    }
}

void Particle:: setInitialCondition(float px, float py, float vx, float vy){
    pos.set(px, py);
    vel.set(vx, vy);
}

void Particle::update(){
    vel += force;
    pos += 3*vel;
}

void Particle::addRepulsion(float px, float py, float radius, float strength){
    ofVec2f posOfForce;
    posOfForce.set(px, py);
    
    ofVec2f diff = pos - posOfForce;
    
    if(diff.length() <radius){
        float percent= 1- (diff.length() / radius);
        diff.normalize();
        force.x += diff.x *percent * strength;
        force.y += diff.y *percent * strength;
    }
}

void Particle::draw(){
//    ofSetColor(r,g,b);
//    ofCircle(pos.x, pos.y, size);
    polyline.lineTo(pos.x, pos.y);
    polyline.lineTo(pos.x, pos.y);
    
//    for (int i=0; i<polylines.size(); i++) {
//        ofPolyline polyline = polylines[i];
//        polyline.draw();
//        float numPoints = polyline.size();
//        float normalLength = 50;
//        for (int p=0; p<500; p+=1) {
//            ofVec3f point = polyline.getPointAtPercent(p/500.0);
//            float floatIndex = p/100.0 * (numPoints-1);
//            ofVec3f normal = polyline.getNormalAtIndexInterpolated(floatIndex) * normalLength;
//            ofLine(point-normal/2, point+normal/2);
//        }
//    }
    polyline.draw();
    
}

void Particle::resetForce(){
    force.set(0,0);
}

void Particle::addDampening(){
    force.x = force.x - vel.x *dampening;
    force.y = force.y - vel.y *dampening;
}








