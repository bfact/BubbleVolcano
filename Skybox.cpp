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
    skybox_f = Texture("/Users/BrittanyFactura/Desktop/ppm/up-the-creek_ft.ppm");
    skybox_b = Texture("/Users/BrittanyFactura/Desktop/ppm/up-the-creek_bk.ppm");
    skybox_u = Texture("/Users/BrittanyFactura/Desktop/ppm/up-the-creek_up.ppm");
    skybox_d = Texture("/Users/BrittanyFactura/Desktop/ppm/up-the-creek_dn.ppm");
    skybox_l = Texture("/Users/BrittanyFactura/Desktop/ppm/up-the-creek_lf.ppm");
    skybox_r = Texture("/Users/BrittanyFactura/Desktop/ppm/up-the-creek_rt.ppm");
    
//    glEnable(GL_TEXTURE_2D);                            // enable texture mapping
//    glShadeModel(GL_SMOOTH);                            // enable smooth shading
//    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);               // black background
//    glClearDepth(1.0f);                                 // depth buffer setup
//    glEnable(GL_DEPTH_TEST);                            // enables depth testing
//    glDepthFunc(GL_LEQUAL);                             // configure depth testing
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // really nice perspective
    
}

//----------------------------------------------------------------------------
//Draw skybox
void Skybox::draw()
{
    
    glDisable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    float size = 100;
    
    skybox_f.bind();     //front
    glBegin(GL_QUADS);   //start texture map drawing
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-size,  size,  size);
    glTexCoord2f(1.0, 0.0); glVertex3f( size,  size,  size);
    glTexCoord2f(1.0, 1.0); glVertex3f( size, -size,  size);
    glTexCoord2f(0.0, 1.0); glVertex3f(-size, -size,  size);
    glEnd();
    skybox_f.unbind();
    
    
    skybox_b.bind();     //back
    glBegin(GL_QUADS);   //start texture map drawing
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-size,  size, -size);
    glTexCoord2f(1.0, 1.0); glVertex3f(-size, -size, -size);
    glTexCoord2f(0.0, 1.0); glVertex3f( size, -size, -size);
    glTexCoord2f(0.0, 0.0); glVertex3f( size,  size, -size);
    glEnd();
    skybox_b.unbind();
    
    
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