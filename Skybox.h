//
//  Skybox.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 11/10/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__Skybox__
#define __CSE167_Spring_2015_Starter_Code__Skybox__

#include <stdio.h>
#include <iostream>
#include <string>
#include "Texture.h"
#include "Drawable.h"
#include "Window.h"

class Skybox
{
    
protected:
    
public:
    
    Texture skybox_f;
    Texture skybox_b;
    Texture skybox_u;
    Texture skybox_d;
    Texture skybox_l;
    Texture skybox_r;
    
    Skybox(void);
    ~Skybox(void);
    
    void draw(void);
    
    void initTextures(void);
};

#endif /* defined(__CSE167_Spring_2015_Starter_Code__Skybox__) */
