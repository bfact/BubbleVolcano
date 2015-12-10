//
//  LSystem.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 12/7/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__LSystem__
#define __CSE167_Spring_2015_Starter_Code__LSystem__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include "Texture.h"
#include "Window.h"
#include "Drawable.h"
#include "String.h"
#include <vector>

using namespace std;

class LSystem
{
    
public:
    
    LSystem(float);
    ~LSystem();
    
    // Angle of branches, and depth of tree
    float ANGLE = 10, depth = 3;
    float length = 0.20;
    
    float lineWidth;
    float incr = 1;
    
    string axiom = "X";
    vector<string> *system = new vector<string>();
    
    void pushMatrix(void);
    void popMatrix(void);
    void rotateLeft(void);
    void rotateRight(void);
    void drawLine(void);
    
    void structure(void);
    void drawTree(void);
    
    void structure1(void);
    void drawTree1(void);
    
    void structure2(void);
    void drawTree2(void);
    
    void structure3(void);
    void drawTree3(void);
    
    void drawLeaf(void);
    void drawMoreLeafeses(void);
    
    void drawSystem(void);
    
};


#endif /* defined(__CSE167_Spring_2015_Starter_Code__LSystem__) */
