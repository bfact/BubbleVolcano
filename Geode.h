//
//  Geode.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 11/3/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__Geode__
#define __CSE167_Spring_2015_Starter_Code__Geode__

#include <stdio.h>
#include "Matrix4.h"
#include "Node.h"


class Geode : public Node
{
    
public:
    //    Matrix4 modelView;
    
    Geode();
    ~Geode();
    
    virtual void render() = 0;
    void draw(Matrix4 C);
    void update();
    
};

#endif /* defined(__CSE167_Spring_2015_Starter_Code__Geode__) */
