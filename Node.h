//
//  Node.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 11/3/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__Node__
#define __CSE167_Spring_2015_Starter_Code__Node__

#include <stdio.h>
#include "Matrix4.h"
#include "Vector3.h"
#include "UpdateData.h"


class Node
{
    
public:
    
    Node(void);
    ~Node(void);
    
    virtual void draw(Matrix4 C) = 0;
    virtual void update() = 0;
    
    void boundingBox(Matrix4);
    
    Vector3 center;
    float radius;
    
};


#endif /* defined(__CSE167_Spring_2015_Starter_Code__Node__) */
