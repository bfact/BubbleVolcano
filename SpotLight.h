//
//  SpotLight.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 10/30/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__SpotLight__
#define __CSE167_Spring_2015_Starter_Code__SpotLight__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include "Drawable.h"
#include "Light.h"



class SpotLight : public Light {
    
protected:
    
//    GLfloat angle;
//    GLfloat cosexp;
//    GLfloat cutoff;
//
//    GLfloat position[4];
//    GLfloat direction[3];
    
public:

    SpotLight();
    ~SpotLight();
    virtual void draw(DrawData&);
    
    
};



#endif /* defined(__CSE167_Spring_2015_Starter_Code__SpotLight__) */
