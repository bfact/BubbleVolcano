//
//  ParticleSystem.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Sean Wenzel on 12/5/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef ParticleSystem_h
#define ParticleSystem_h

#include <stdio.h>
#include "Shader.h"
#include "Vector3.h"
#include "Color.h"
#include "Particle.h"
#include <vector>

class ParticleSystem {
    
private:
    static const int MaxParticles = 1000000;
    Particle collection[MaxParticles];
public:
    ParticleSystem();
    int findUnusedParticle();
    void draw();
};

#endif /* ParticleSystem_h */
