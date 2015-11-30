//
//  particles.hpp
//  particle_test
//
//  Created by Courtney Snavely on 11/21/15.
//
//

#ifndef particles_hpp
#define particles_hpp

#include <stdio.h>

#endif /* particles_hpp */

#include "ofMain.h"

class Particle{
public:
    
    Particle();
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f force;
    
    void setInitialCondition (float px, float py, float vx, float vy);
    void update();
    void draw();
    
    void addRepulsion(float px, float py, float radius, float strength);
   
    int r, g, b;
    float dist;
    float dampening;
    float angle;
    
    void resetForce();
    void addDampening();
   
    ofPolyline polyline;
    
    void addAttraction(float px, float py, float radius, float strength);
    
  
};
