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
    
    ofSetColor(pr, pg, pb);

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
  
    
    
    vertices = polyline.getVertices();  // If you haven't seen a vector < >, before
            for (int p=0; p<100; p+=10) {
                point = polyline.getPointAtPercent(p/100.0);  // Returns a point at a percentage along the polyline
                ofCircle(point, 4);
            }
    polyline.lineTo(pos.x, pos.y);
    

    polyline.draw();
    
}

void Particle::resetForce(){
    force.set(0,0);
}

void Particle::addDampening(){
    force.x = force.x - vel.x *dampening;
    force.y = force.y - vel.y *dampening;
}


void Particle::clear(){
    points= polyline.getVertices();
    points.clear();
    polyline.clear();
    
    
}







