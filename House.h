//
//  House.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 10/5/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__House__
#define __CSE167_Spring_2015_Starter_Code__House__

#include "Drawable.h"

class House : public Drawable
{
    
public:
    float size;
    
    House(float);
    virtual ~House(void);
    
    virtual void draw(DrawData&);
    
};







#endif /* defined(__CSE167_Spring_2015_Starter_Code__House__) */
