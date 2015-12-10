//
//  Particle.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Sean Wenzel on 12/9/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef Particle_h
#define Particle_h

#include <stdio.h>
#include "Vector3.h"
#include "Vector4.h"

class Particle {
public:
    Vector3 position, speed;
    Vector4 color;
    float size, angle, weight;
    float life;

    void draw();
};

#endif /* Particle_h */
