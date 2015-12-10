//
//  MatrixTransform.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 11/3/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "MatrixTransform.h"


MatrixTransform::MatrixTransform()
{
    this->M.identity();
}

MatrixTransform::MatrixTransform(Matrix4 C)
{
    this->M = C;
}

MatrixTransform::~MatrixTransform()
{
}

void MatrixTransform::draw(Matrix4 C)
{
    Matrix4 CM = C * M;
    Group::draw(CM);
    //    for(std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
    //        (*it)->draw(CM);
    //    }
}