//
//  MatrixTransform.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 11/3/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__MatrixTransform__
#define __CSE167_Spring_2015_Starter_Code__MatrixTransform__

#include <stdio.h>
#include "Group.h"

class MatrixTransform : public Group
{
    
public:
    
    Matrix4 M;
    
    MatrixTransform(void);
    MatrixTransform(Matrix4);
    ~MatrixTransform(void);
    
    void draw(Matrix4 C);
    
    
};


#endif /* defined(__CSE167_Spring_2015_Starter_Code__MatrixTransform__) */
