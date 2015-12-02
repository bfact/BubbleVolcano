//
//  BezierCurve.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 11/10/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__BezierCurve__
#define __CSE167_Spring_2015_Starter_Code__BezierCurve__
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <stdio.h>
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Texture.h"

class BezierCurve
{
    
private:
    
    Vector4 controls[16];
    Vector4 vertices[100][100];
    Vector3 normals[100][100];
    
    Texture logo;
    
public:
    
    BezierCurve();
    ~BezierCurve();
    
    void draw();
    void createPatch();
    float Bernstein(float, float, float);
    float factorial(float);
    void initTextures(void);
    void evalNormals(float, float, int, int);
    Vector4 evalBezier(Matrix4, float);
    Matrix4 createMatrix(Vector4, Vector4, Vector4, Vector4);

};

#endif /* defined(__CSE167_Spring_2015_Starter_Code__BezierCurve__) */

