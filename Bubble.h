//
//  Bubble.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Sean Wenzel on 12/2/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef Bubble_h
#define Bubble_h

#include <stdio.h>
#include "Texture.h"
#include "Drawable.h"
#include <vector>

class Bubble : public Drawable {
    
private:
    
    double radius;
    double slices;
    double stacks;
    Texture texture;
    
public:
    Bubble();
    Bubble(double, int, int, Texture);
    void draw();
    void update();
   
    
    
};

#endif /* Bubble_h */
