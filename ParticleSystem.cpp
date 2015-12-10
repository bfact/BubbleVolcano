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
#include "Globals.h"
#include "Window.h"
#include <time.h>
#include <random>

const float delta = 1.0/60.0;

ParticleSystem::ParticleSystem() {
    
}

int LastUsedParticle = 0;
int ParticleSystem::findUnusedParticle(){
    
         for(int i=LastUsedParticle; i<MaxParticles; i++){
                 if (collection[i].life <= 0){
                         LastUsedParticle = i;
                         return i;
                     }
             }
    
         for(int i=0; i<LastUsedParticle; i++){
                 if (collection[i].life <= 0){
                         LastUsedParticle = i;
                         return i;
                     }
             }
    
         return -1; // All particles are taken, override the first one
}

void ParticleSystem::draw() {
   
    
    
    // Generate 10 new particule each millisecond,
    // but limit this to 16 ms (60 fps), or if you have 1 long frame (1sec),
    // newparticles will be huge and the next frame even longer.
    int newparticles = (int)(delta*10000.0);
    if (newparticles > (int)(0.016f*10000.0))
        newparticles = (int)(0.016f*10000.0);
    
    for(int i=0; i<newparticles; i++){
        int particleIndex = findUnusedParticle();
        if (particleIndex == -1) {
            break;
        }
        collection[particleIndex].life = fmod(rand(), 5.0f); // This particle will live 5 seconds.
        collection[particleIndex].position = Vector3(0,2.5+Globals::volcanoHeightDisplacement,0.0f);
        
        float spread = 1.5f;
        Vector3 maindir = Vector3(0.0f, 10.0f, 0.0f);
        // Very bad way to generate a random direction;
        // See for instance http://stackoverflow.com/questions/5408276/python-uniform-spherical-distribution instead,
        // combined with some user-controlled parameters (main direction, spread, etc)
        Vector3 randomdir = Vector3(
                                        (rand()%2000 - 1000.0f)/1000.0f,
                                        (rand()%2000 - 1000.0f)/1000.0f,
                                        (rand()%2000 - 1000.0f)/1000.0f
                                        );
        
        collection[particleIndex].speed = maindir + randomdir*spread;
        
        
        // Very bad way to generate a random color
        collection[particleIndex].color.set(0, rand() % 256);
        collection[particleIndex].color.set(1, rand() % 256);
        collection[particleIndex].color.set(2, rand() % 256);
        collection[particleIndex].color.set(3, (rand() % 256) / 3);
        
        collection[particleIndex].size = (rand()%1000)/2000.0f + 0.1f;
        
}
    
    // Simulate all particles
    // int ParticlesCount = 0;
    for(int i=0; i<MaxParticles; i++){
        
        Particle& p = collection[i]; // shortcut
        //collection[0].position.print("Particle 0 position");
        //std::cout << "life: " << collection[0].life << std::endl;

        if(p.life > 0.0f){
            
            // Decrease life
            p.life -= delta;
            //std::cout << "life after: " << collection[0].life << std::endl;
            if (p.life > 0.0f){
                
                // Simulate simple physics : gravity only, no collisions
                p.speed = p.speed + Vector3(0.0f,-9.81f, 0.0f) * (float)delta * 0.5f;
                p.position = p.position + p.speed * (float)delta;
                //p.cameradistance = glm::length2( p.pos - CameraPosition );
                //ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;
                p.draw();
            }
        }
        //ParticlesCount++;
            
        }
    }
    




