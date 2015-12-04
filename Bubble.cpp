//
//  Bubble.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Sean Wenzel on 12/2/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Bubble.h"
#include "Globals.h"
#include <math.h>

// Generate random bubble of random radius and texture
Bubble::Bubble() {
    this->radius = fmod(((float)rand()),3.0);
    this->slices = 30;
    this->stacks = 30;
    if (Globals::textures.size() != 0)
        this->texture = Globals::textures.at( rand() % Globals::textures.size());
    
}

Bubble::Bubble(double radius, int slices, int stacks, Texture texture)
{
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
    this->texture = texture;
}


void Bubble::draw() {
    //material.apply();
    /*
    Material sphere = Material(Color(0.0, 0.0, 0.0, 0.1),
                               Color::diffuseMaterialDefault(),
                               Color::specularMaterialDefault(),
                               Color::emissionMaterialDefault(),
                               Color(0,1,1), 5.0); */
    
    //sphere.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    glutSolidSphere(radius, slices, stacks);
    
    glPopMatrix();

}

void Bubble::update() {
    Matrix4 m;
    m.makeTranslate(0, .1, 0);
    toWorld = m.multiply(toWorld);
}