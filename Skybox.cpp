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

#define STARS_FRONT "/Users/BrittanyFactura/GitHub/bubblevolcano/stars_front.ppm"
#define STARS_BACK "/Users/BrittanyFactura/GitHub/bubblevolcano/stars_back.ppm"
#define STARS_TOP "/Users/BrittanyFactura/GitHub/bubblevolcano/stars_top.ppm"
#define STARS_LEFT "/Users/BrittanyFactura/GitHub/bubblevolcano/stars_left.ppm"
#define STARS_RIGHT "/Users/BrittanyFactura/GitHub/bubblevolcano/stars_right.ppm"

#define STARS_FRONT_SEAN "/Users/seanwenzel/Github/bubblevolcano/stars_front.ppm"
#define STARS_BACK_SEAN "/Users/seanwenzel/Github/bubblevolcano/stars_back.ppm"
#define STARS_TOP_SEAN "/Users/seanwenzel/Github/bubblevolcano/stars_top.ppm"
#define STARS_LEFT_SEAN "/Users/seanwenzel/Github/bubblevolcano/stars_left.ppm"
#define STARS_RIGHT_SEAN "/Users/seanwenzel/Github/bubblevolcano/stars_right.ppm"

#define CLOUDS_FRONT "/Users/BrittanyFactura/GitHub/bubblevolcano/clouds_front.ppm"
#define CLOUDS_BACK "/Users/BrittanyFactura/GitHub/bubblevolcano/clouds_back.ppm"
#define CLOUDS_TOP "/Users/BrittanyFactura/GitHub/bubblevolcano/clouds_top.ppm"
#define CLOUDS_LEFT "/Users/BrittanyFactura/GitHub/bubblevolcano/clouds_left.ppm"
#define CLOUDS_RIGHT "/Users/BrittanyFactura/GitHub/bubblevolcano/clouds_right.ppm"

#define CLOUDS_FRONT_SEAN "/Users/seanwenzel/Github/bubblevolcano/clouds_front.ppm"
#define CLOUDS_BACK_SEAN "/Users/seanwenzel/Github/bubblevolcano/clouds_back.ppm"
#define CLOUDS_TOP_SEAN "/Users/seanwenzel/Github/bubblevolcano/clouds_top.ppm"
#define CLOUDS_LEFT_SEAN "/Users/seanwenzel/Github/bubblevolcano/clouds_left.ppm"
#define CLOUDS_RIGHT_SEAN "/Users/seanwenzel/Github/bubblevolcano/clouds_right.ppm"

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
    /*
    // Brittany's Version
    if (!Window::clouds) {
        skybox_f = Texture(STARS_FRONT);
        skybox_b = Texture(STARS_BACK);
        skybox_u = Texture(STARS_TOP);
        skybox_d = Texture(STARS_FRONT);
        skybox_l = Texture(STARS_LEFT);
        skybox_r = Texture(STARS_RIGHT);
    } else if (Window::clouds) {
        skybox_f = Texture(CLOUDS_FRONT);
        skybox_b = Texture(CLOUDS_BACK);
        skybox_u = Texture(CLOUDS_TOP);
        skybox_d = Texture(CLOUDS_FRONT);
        skybox_l = Texture(CLOUDS_LEFT);
        skybox_r = Texture(CLOUDS_RIGHT);
    } */
    
    
    // Sean's Version
    if (!Window::clouds) {
        skybox_f = Texture(STARS_FRONT_SEAN);
        skybox_b = Texture(STARS_BACK_SEAN);
        skybox_u = Texture(STARS_TOP_SEAN);
        skybox_d = Texture(STARS_FRONT_SEAN);
        skybox_l = Texture(STARS_LEFT_SEAN);
        skybox_r = Texture(STARS_RIGHT_SEAN);
    } else if (Window::clouds) {
        skybox_f = Texture(CLOUDS_FRONT_SEAN);
        skybox_b = Texture(CLOUDS_BACK_SEAN);
        skybox_u = Texture(CLOUDS_TOP_SEAN);
        skybox_d = Texture(CLOUDS_FRONT_SEAN);
        skybox_l = Texture(CLOUDS_LEFT_SEAN);
        skybox_r = Texture(CLOUDS_RIGHT_SEAN);
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
    
    /*
    skybox_d.bind();     //bottom
    glBegin(GL_QUADS);   //start texture map drawing
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-size, -size, -size);
    glTexCoord2f(1.0, 0.0); glVertex3f(-size, -size,  size);
    glTexCoord2f(0.0, 0.0); glVertex3f( size, -size,  size);
    glTexCoord2f(0.0, 1.0); glVertex3f( size, -size, -size);
    glEnd();
    skybox_d.unbind(); */
    
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