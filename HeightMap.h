//
//  HeightMap.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Sean Wenzel on 12/3/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef HeightMap_h
#define HeightMap_h

#include <stdio.h>
#include "Texture.h"
#include "Shader.h"

class HeightMap {
private:
    float map[257][257];
    float min;
    float max;
    
    void diamondSquareAlgorithm(unsigned, unsigned, unsigned, unsigned, float, unsigned);
    //void diamondStep(float, float, float, float);
    //void squareStep(float, float, float, float);
    float getRnd(float);
    float getMaxDisplacement(float, float, float, float);
public:
    HeightMap();
    void printMap();
    void draw();
    void generateNewHeightMap();
    void resetMap();
    void findMinAndMax();
    void initTextures();
    
};

#endif /* HeightMap_h */
