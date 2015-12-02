//
//  DirectionalLight.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 10/30/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
    diffuseColor = Color(2.0, 2.0, 2.0);
    position = Vector4(1.0, 1.0, 1.0, 0);
}

DirectionalLight::~DirectionalLight()
{
    
}

void DirectionalLight::draw()
{
    
}

