//
//  SpotLight.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 10/30/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "SpotLight.h"
#include "Globals.h"
#include "Sphere.h"

SpotLight::SpotLight() : Light()
{
    specularColor = Color(1.0, 1.0, 1.0, 1.0);
    direction = Vector4(0.0, 0.0, -1.0, 1.0);
    diffuseColor  = Color(1.0, 1.0, 1.0, 1.0);
    position = Vector4(1.0, 1.0, 1.0, 1.0);
    
    angle = 30.0;
    exp = 0.0; // how concentrated the light is
}

SpotLight::~SpotLight()
{
    
}

void SpotLight::draw(DrawData& data)
{
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(1, 15, 15);
    bind(3);
    
    glPopMatrix();
}