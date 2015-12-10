//
//  LSystem.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 12/7/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include <string>
#include "LSystem.h"
#include "Matrix4.h"
#include "Globals.h"

#define deleteVector(__type__, __vect__) do {\
std::vector<__type__>::iterator iter; \
std::vector<__type__>::iterator end; \
iter = __vect__->begin();\
end = __vect__->end();\
while(iter != end) delete ((iter++));\
delete __vect__;\
} while(false)

#define PI 3.14159265

float c = PI/180.0;
int frame = 0;
int elapsedTime;
int timebase = 0;

using namespace std;

LSystem::LSystem(float width)
{
    lineWidth = width;
}

LSystem::~LSystem()
{
    
}

// references: http://www.cse.chalmers.se/~uffe/xjobb/climbingplants.pdf
// http://algorithmicbotany.org/papers/abop/abop-ch1.pdf
// variables : X F
// constants : + - [ ]
// F → FFF-[-F+X]+[+F-F-X]
// X → FF
void LSystem::structure()
{
    string ch = "";
    
    for (int i = 0; i < axiom.length(); i++){
        ch = axiom.at(i);
        
        if (ch.compare("F") == 0){
            axiom.replace(i, 1, "FFF-[-F+X]+[+F-F-X]");
            i = i + 19;
        } else if (ch.compare("X") == 0){
            axiom.replace(i,1,"FF");
            i = i + 1;
        }
        
    }
    
    system->push_back(axiom);
}

void LSystem::drawTree()
{
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            string ch = "";
            string LSystem = system->at(depth);
            
            for (int i = 0; i < LSystem.length(); i++) {
                glColor3f(0.5, 0.3, 0.2);
                ch = LSystem.at(i);
                
                if (ch.compare("F") == 0) {
                    drawLine();
                    if (i > 350) {
                        glColor3f(0.3, 1, 0.5);
                        glutSolidSphere(0.05, 10, 10);
                        glutSolidCone(0.05, 0.2, 10, 10);
                    }
                }
                
                else if (ch.compare("[") == 0)
                    pushMatrix();
                
                else if (ch.compare("]") == 0)
                    popMatrix();
                
                else if (ch.compare("+") == 0)
                    rotateRight();
                
                else if (ch.compare("-") == 0)
                    rotateLeft();
            }
        }
    }
}


// rules : (X → F[+X]F[-X]+X), (F → FF)
void LSystem::structure1()
{
    string ch = "";
    
    for (int i = 0; i < axiom.length(); i++) {
        ch = axiom.at(i);
        
        if (ch.compare("X") == 0) {
            axiom.replace(i, 1, "F-[-F+X]+[+F-F-X]");
            i = i + 19;
        } else if (ch.compare("F") == 0) {
            axiom.replace(i,1,"FF");
            i = i + 1;
        }
    }
    
    system->push_back(axiom);
}

void LSystem::drawTree1()
{
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            string ch = "";
            string LSystem = system->at(depth);
            
            for (int i = 0; i < LSystem.length(); i++){
                ch = LSystem.at(i);
                
                if (ch.compare("F") == 0) {
                    //glColor3f(0.847059, 0.847059, 0.74902);
                    glColor3f( 0.91 , 0.76 , 0.65);
                    drawLine();
                }
                else if (ch.compare("[") == 0)
                    pushMatrix();
                
                else if (ch.compare("]") == 0)
                    popMatrix();
                
                else if (ch.compare("+") == 0) {
                    rotateLeft();
                    drawMoreLeafeses();
                }
                
                else if (ch.compare("-") == 0) {
                    rotateRight();
                    drawMoreLeafeses();
                }
            }
        }
    }
}

// start     : X
// rules     : (X -> F-[[X]+X]+F[+FX]-X), (F -> FF)
// angle     : 25°
void LSystem::structure2()
{
    string ch = "";
    
    for (int i = 0; i < axiom.length(); i++) {
        ch = axiom.at(i);
        
        if (ch.compare("X") == 0) {
            axiom.replace(i, 1, "FFF-[-F+X]+[+F-F-X]");
            i = i + 19;
        } else if (ch.compare("F") == 0) {
            axiom.replace(i,1,"FF");
            i = i + 1;
        }
    }
    
    system->push_back(axiom);
}

void LSystem::drawTree2()
{
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            string ch = "";
            string LSystem = system->at(depth);
            
            for (int i = 0; i < LSystem.length(); i++) {
                glColor3f(0.5, 0.3, 0.2);
                ch = LSystem.at(i);
                
                if (ch.compare("F") == 0) {
                    glColor3f(0.5, 1.0, 0.0);
                    drawLine();
                    if (i > 400) {
                        glColor3f(0.3, 1, 0.5);
                        glutSolidSphere(0.05, 10, 10);
                        glutSolidCone(0.05, 0.2, 10, 10);
                        drawLeaf();
                    }
                }
                
                else if (ch.compare("[") == 0)
                    pushMatrix();
                
                else if (ch.compare("]") == 0)
                    popMatrix();
                
                else if (ch.compare("+") == 0) {
                    rotateRight();
                    glColor3f(0.3, 1, 0.5);
                    glutSolidSphere(0.05, 10, 10);
                    glutSolidCone(0.05, 0.2, 10, 10);
                }
                
                else if (ch.compare("-") == 0) {
                    rotateLeft();
                    glColor3f(0.3, 1, 0.5);
                    glutSolidSphere(0.05, 10, 10);
                    glutSolidCone(0.05, 0.2, 10, 10);
                }
            }
        }
    }
}

void LSystem::structure3()
{
    string ch = "";
    
    for (int i = 0; i < axiom.length(); i++) {
        ch = axiom.at(i);
        
        if (ch.compare("X") == 0) {
            axiom.replace(i, 1, "F-[-FF+F+F]+[+F-F-F]");
            i = i + 19;
        } else if (ch.compare("F") == 0) {
            axiom.replace(i,1,"FF");
            i = i + 1;
        }
    }
    
    system->push_back(axiom);
}

void LSystem::drawTree3()
{
    string ch = "";
    string LSystem = system->at(depth);
    
    for (int i = 0; i < LSystem.length(); i++){
        ch = LSystem.at(i);
        
        if (ch.compare("F") == 0) {
            glColor3f(0.847059, 0.847059, 0.74902);
            //glColor3f( 0.91 , 0.76 , 0.65);
            drawLine();
        }
        else if (ch.compare("[") == 0)
            pushMatrix();
        
        else if (ch.compare("]") == 0)
            popMatrix();
        
        else if (ch.compare("+") == 0) {
            rotateLeft();
            drawMoreLeafeses();
        }
        
        else if (ch.compare("-") == 0) {
            rotateRight();
            drawMoreLeafeses();
        }
    }
}

void LSystem::pushMatrix()
{
    glPushMatrix();
    
    if (lineWidth > 0)
        lineWidth -= incr;
    
}

void LSystem::popMatrix()
{
    glPopMatrix();
    lineWidth += incr;
    
}

void LSystem::rotateLeft()
{
    glRotatef(ANGLE, 1, 0, 0);
    glRotatef(ANGLE*4, 0, 1, 0);
    glRotatef(ANGLE, 0, 0, 1);
}

void LSystem::rotateRight()
{
    
    glRotatef(-ANGLE, 1, 0, 0);
    glRotatef(ANGLE*4, 0, 1, 0);
    glRotatef(-ANGLE, 0, 0, 1);
}

void LSystem::drawLine()
{
    //glColor3f(0.5, 1.0, 0.0);
    glLineWidth(lineWidth);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, length, 0);
    glEnd();
    
    glTranslatef(0, length, 0);
}


void LSystem::drawLeaf()
{
    float a, b;
    float theta;
    
    glColor3f(0, 1, 0);
    glBegin (GL_POLYGON);
    for (theta = 30; theta <= 150; theta += 1) {
        a = (cos(c*theta));
        b = (sin(c*theta));
        glVertex2f(a,b);
    }
    for (theta = 210; theta <= 330; theta+= 1) {
        a = (cos(c*theta));
        b = (sin(c*theta)+1);
        glVertex2f(a,b);
    }
    glEnd();
}


// big af
void LSystem::drawMoreLeafeses()
{

    //glColor3f(1,1,0);
    //glColor3f(0.184314, 0.309804, 0.309804);
    
    glColor3f(0.498039, 1.0, 0.0);
    
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);glVertex3f(-0.5f,0.0f,0.0f);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(0.5f,0.0f,0.0f);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(0.5f,1.0f,0.0f);
    glTexCoord2f(0.0f, 1.0f);glVertex3f(-0.5f,1.0f,0.0f);
    glEnd();
    
    
//    glBegin(GL_POLYGON);
//    glVertex2f(0,0);
//    
//    for(int i = 150; i <= 390; i+=10)
//        glVertex2f(sin(c*i)-2, cos(c*i));
//    
//    glVertex2f(0,0);
//    glEnd();
}



void LSystem::drawSystem()
{
 
}
