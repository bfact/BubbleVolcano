//
//  PointLight.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 10/30/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "PointLight.h"
#include "Sphere.h"
#include "Globals.h"

PointLight::PointLight() : Light()
{
    position = Vector4(1.0, 1.0, 1.0, 1.0);
    specularColor = Color(1.0, 1.0, 1.0, 1.0);
    diffuseColor  = Color(1.0, 1.0, 1.0, 1.0);
}

PointLight::~PointLight()
{
    
}

void PointLight::draw(DrawData& data)
{
    std::cout << "Drawing Point Light" << std::endl;
    
//    glPushMatrix();.
//    glLoadIdentity();
//    glColor3f(10.0, 10.0, 10.0);
//    glColor3f(0.0, 0.8, 0.8);
//    glutSolidSphere(0.5, 15, 15);
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(1, 15, 15);
    bind(2);
    
    glPopMatrix();
    

}


