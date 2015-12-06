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

class ParticleSystem {
private:
    Shader* particleShader;
    
public:
    
    ParticleSystem();
    void draw();

};

#endif /* ParticleSystem_h */
