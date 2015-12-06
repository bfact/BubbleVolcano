//
//  ParticleSystem.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Sean Wenzel on 12/5/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "ParticleSystem.h"

#define PARTICLE_VERT_SEAN "/Users/seanwenzel/Github/bubblevolcano/particle.vert"
#define PARTICLE_FRAG_SEAN "/Users/seanwenzel/Github/bubblevolcano/particle.frag"


/*
 * Need to set:
 * ParticleTex: the particle's texture
 * Time: The amount of time that has elapsed since the animation began
 * Gravity: The vector representing one half of the acceleration
 * ParticleLifetime: How long a particle survives after it is created
 */

ParticleSystem::ParticleSystem() {
    //particleShader = new Shader(PARTICLE_VERT_SEAN, PARTICLE_FRAG_SEAN);
    
    /*
    GLint loc = glGetUniformLocation(particleShader->getPid(), "ParticleTex");
    if (loc != -1)
    {
        glUniform1f(loc, 0.432);
    } */
    
}

void ParticleSystem::draw() {
    //particleShader->bind();
    
}

