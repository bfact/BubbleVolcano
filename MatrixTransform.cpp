//
//  MatrixTransform.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 11/3/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "MatrixTransform.h"


MatrixTransform::MatrixTransform(Matrix4 C)
{
    this->M = C;
}


MatrixTransform::~MatrixTransform()
{
    children.clear();

}

void MatrixTransform::draw(Matrix4 C)
{
    M = C * M;
    for(std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
        (*it)->draw(C);
    }
}