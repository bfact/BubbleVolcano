//
//  Particle.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Sean Wenzel on 12/9/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "Particle.h"
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void Particle::draw() {
    //glEnable(GL_POINT_SPRITE);

    /*
    float attenuation[3] = {0.0f, 1.0f, 0.0f};
    glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, attenuation);
    
    glPointParameterf(GL_POINT_SIZE_MIN, 1.0f);
    glPointParameterf(GL_POINT_SIZE_MAX, 128.0f);
    
    glEnable(GL_POINT_SPRITE); */
    
    
    glBegin(GL_POINTS);
    glPointSize(size);
    glColor4f(color.get(0), color.get(1), color.get(2), color.get(3));
    //glColor3f(1.0, 1.0, 1.0);
    glVertex3f(position.get(0), position.get(1), position.get(2));
    //position.print("position");
    glEnd();
}