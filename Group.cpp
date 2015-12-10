//
//  Group.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 11/3/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "Group.h"
#include "Globals.h"

#define deleteVector(__type__, __vect__) do {\
        std::vector<__type__>::iterator iter; \
        std::vector<__type__>::iterator end; \
        iter = __vect__.begin();\
        end = __vect__.end();\
        while(iter != end) delete (*(iter++));\
delete __vect__;\
} while(false)



Group::Group()
{
    
}

Group::~Group()
{
    //Delete any dynamically allocated memory/objects here
    children.clear();
    
}

void Group::addChild(Node* n)
{
    children.push_back(n);
}

void Group::removeChild(Node* n)
{
    children.erase(std::remove(children.begin(), children.end(), n), children.end());
}

//draw method needs to traverse the list of children
//and call each child node's draw function
void Group::draw(Matrix4 C)
{
    
    for(std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
        (*it)->draw(C);
        
//        if (Globals::bounding == true) {
//            glPushMatrix();
//            glMultMatrixf(C.ptr());
//            glColor3f(1.0, 1.0, 1.0);
//            glutWireSphere(radius, 8, 8);
//            glPopMatrix();
//        }
    }
}


void Group::update()
{
    std::cout << "updating" << std::endl;
}