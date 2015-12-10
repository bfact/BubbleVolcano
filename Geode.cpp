//
//  Geode.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 11/3/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "Geode.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Window.h"
#include "Globals.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Geode::Geode() : Node()
{
    //    this->modelView.identity();
}


Geode::~Geode()
{
    
}

void Geode::draw(Matrix4 C)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(C.ptr());
    render();
    glPopMatrix();
}

void Geode::update()
{
    
}