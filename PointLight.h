//
//  PointLight.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 10/30/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__PointLight__
#define __CSE167_Spring_2015_Starter_Code__PointLight__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include "Drawable.h"
#include "Light.h"
#include "Vector3.h"


class PointLight : public Light {

protected:
//    
//    GLfloat angle;
//    GLfloat position[4];
    
public:

    PointLight(int, GLfloat*, GLfloat*, GLfloat*, GLfloat*);
    
    PointLight();
    ~PointLight();
    
    void enable();
    void disable();
    void setPosition(GLfloat*);
    void setAngle(GLfloat a);
    
    virtual void draw(DrawData&);
    
    GLfloat* getPosition();
    GLfloat getAngle();
    
    
    
};

#endif /* defined(__CSE167_Spring_2015_Starter_Code__PointLight__) */
