//
//  Group.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 11/3/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__Group__
#define __CSE167_Spring_2015_Starter_Code__Group__

#include <stdio.h>
#include <vector>
#include "Matrix4.h"
#include "UpdateData.h"
#include "Vector3.h"
#include "Node.h"

class Group : public Node
{
public:
    
    Group(void);
    ~Group(void);
    
    void addChild(Node*);
    void removeChild(Node*);
    
    virtual void draw(Matrix4 C);
    virtual void update();
    std::vector<Node*> children;
    
    
    
};

#endif /* defined(__CSE167_Spring_2015_Starter_Code__Group__) */
