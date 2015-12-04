//
//  Skybox.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 11/10/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "Skybox.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


Skybox::Skybox()
{

}


Skybox::~Skybox()
{
    
}

//----------------------------------------------------------------------------
//Reference: http://nehe.gamedev.net/tutorial/texture_mapping/12038 for nice tutorial
//If everything went OK, and the texture was created, we enable 2D texture mapping.
//If you forget to enable texture mapping your object will usually appear solid white,
//which is definitely not good.
//OpenGL needs to be initialized before we can load textures.

void Skybox::initTextures()
{
    if (!Window::clouds) {
        skybox_f = Texture("/Users/BrittanyFactura/GitHub/bubblevolcano/stars_front.ppm");
        skybox_b = Texture("/Users/BrittanyFactura/GitHub/bubblevolcano/stars_back.ppm");
        skybox_u = Texture("/Users/BrittanyFactura/GitHub/bubblevolcano/stars_top.ppm");
        skybox_d = Texture("/Users/BrittanyFactura/GitHub/bubblevolcano/stars_front.ppm");
        skybox_l = Texture("/Users/BrittanyFactura/GitHub/bubblevolcano/stars_left.ppm");
        skybox_r = Texture("/Users/BrittanyFactura/GitHub/bubblevolcano/stars_right.ppm");
    } else if (Window::clouds) {
        skybox_f = Texture("/Users/BrittanyFactura/GitHub/bubblevolcano/clouds_front.ppm");
        skybox_b = Texture("/Users/BrittanyFactura/GitHub/bubblevolcano/clouds_back.ppm");
        skybox_u = Texture("/Users/BrittanyFactura/GitHub/bubblevolcano/clouds_top.ppm");
        skybox_d = Texture("/Users/BrittanyFactura/GitHub/bubblevolcano/clouds_front.ppm");
        skybox_l = Texture("/Users/BrittanyFactura/GitHub/bubblevolcano/clouds_left.ppm");
        skybox_r = Texture("/Users/BrittanyFactura/GitHub/bubblevolcano/clouds_right.ppm");
    }
}

//----------------------------------------------------------------------------
//Draw skybox
void Skybox::draw()
{
    
    glDisable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    float size = 100;
    
    skybox_b.bind();     //front
    glBegin(GL_QUADS);   //start texture map drawing
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-size,  size,  size);
    glTexCoord2f(1.0, 0.0); glVertex3f( size,  size,  size);
    glTexCoord2f(1.0, 1.0); glVertex3f( size, -size,  size);
    glTexCoord2f(0.0, 1.0); glVertex3f(-size, -size,  size);
    glEnd();
    skybox_b.unbind();
    
    
    skybox_f.bind();     //back
    glBegin(GL_QUADS);   //start texture map drawing
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-size,  size, -size);
    glTexCoord2f(1.0, 1.0); glVertex3f(-size, -size, -size);
    glTexCoord2f(0.0, 1.0); glVertex3f( size, -size, -size);
    glTexCoord2f(0.0, 0.0); glVertex3f( size,  size, -size);
    glEnd();
    skybox_f.unbind();
    
    
    skybox_u.bind();     //top
    glBegin(GL_QUADS);   //start texture map drawing
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-size,  size, -size);
    glTexCoord2f(0.0, 1.0); glVertex3f( size,  size, -size);
    glTexCoord2f(0.0, 0.0); glVertex3f( size,  size,  size);
    glTexCoord2f(1.0, 0.0); glVertex3f(-size,  size,  size);
    glEnd();
    skybox_u.unbind();
    
    skybox_d.bind();     //bottom
    glBegin(GL_QUADS);   //start texture map drawing
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-size, -size, -size);
    glTexCoord2f(1.0, 0.0); glVertex3f(-size, -size,  size);
    glTexCoord2f(0.0, 0.0); glVertex3f( size, -size,  size);
    glTexCoord2f(0.0, 1.0); glVertex3f( size, -size, -size);
    glEnd();
    skybox_d.unbind();
    
    skybox_r.bind();     //right
    glBegin(GL_QUADS);   //start texture map drawing
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-size,  size, -size);
    glTexCoord2f(1.0, 0.0); glVertex3f(-size,  size,  size);
    glTexCoord2f(1.0, 1.0); glVertex3f(-size, -size,  size);
    glTexCoord2f(0.0, 1.0); glVertex3f(-size, -size, -size);
    glEnd();
    skybox_r.unbind();
    
    
    skybox_l.bind();     //left
    glBegin(GL_QUADS);   //start texture map drawing
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f( size,  size, -size);
    glTexCoord2f(1.0, 1.0); glVertex3f( size, -size, -size);
    glTexCoord2f(0.0, 1.0); glVertex3f( size, -size,  size);
    glTexCoord2f(0.0, 0.0); glVertex3f( size,  size,  size);
    glEnd();
    skybox_l.unbind();
    
    glEnable(GL_LIGHTING);
    
}