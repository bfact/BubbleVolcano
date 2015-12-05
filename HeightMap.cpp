//
//  HeightMap.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Sean Wenzel on 12/3/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include "HeightMap.h"
#include <limits>
#include <random>

// Generate a height map using the Diamond-Square algorithm
HeightMap::HeightMap() {
    float initialValue = 10.0;
    map[0][0] = map[0][256] = map[256][0] = map[256][256] = initialValue;
    float range = 10.0;
    diamondSquareAlgorithm(0, 0, 256, 256, range, 256);
}

/*
 * Pseudocode:
 * While the length of the side of the squares is greater than zero {
 *      Pass through the array and perform the diamond step for each square present.
 *      Pass through the array and perform the square step for each diamond present.
 *      Reduce the random number range.
 * }
 */
void HeightMap::diamondSquareAlgorithm(unsigned x1,unsigned y1,unsigned x2,unsigned y2,float range, unsigned level) {
    if (level < 1) return;
    
    float maxDisplacement = 0.0;
    
    // diamonds
    for (unsigned i = x1 + level; i < x2; i += level)
        for (unsigned j = y1 + level; j < y2; j += level) {
            float a = map[i - level][j - level];
            float b = map[i][j - level];
            float c = map[i - level][j];
            float d = map[i][j];
            maxDisplacement = getMaxDisplacement(a, b, c, d);
            float e = map[i - level / 2][j - level / 2] = (a + b + c + d) / 4 + getRnd(maxDisplacement) * range;
            
            if (e > maxDisplacement) {
                maxDisplacement = e;
            }
        }
    
    // squares
    for (unsigned i = x1 + 2 * level; i < x2; i += level)
        for (unsigned j = y1 + 2 * level; j < y2; j += level) {
            float a = map[i - level][j - level];
            float b = map[i][j - level];
            float c = map[i - level][j];
            float d = map[i][j];
            float e = map[i - level / 2][j - level / 2];
            
            float f = map[i - level][j - level / 2] = (a + c + e + map[i - 3 * level / 2][j - level / 2]) / 4 + getRnd(maxDisplacement) * range;
            float g = map[i - level / 2][j - level] = (a + b + e + map[i - level / 2][j - 3 * level / 2]) / 4 + getRnd(maxDisplacement) * range;
            
            //range = range * 0.9;
        }
    
    diamondSquareAlgorithm(x1, y1, x2, y2, range / 2, level / 2);

     
}


float HeightMap::getRnd(float d) {
    float max = d;
    float min = -d;
    
    float n = max - min + 1.0;
    float remainder = fmod((float)RAND_MAX,n);
    float x;
    do{
        x = rand();
    }while (x >= RAND_MAX - remainder);
    return min + fmod(x,n);
}

float HeightMap::getMaxDisplacement(float m1, float m2, float m3, float m4) {
    float result = m1;
    if (m2 > result) {
        result = m2;
    }
    if (m3 > result) {
        result = m3;
    }
    if (m4 > result) {
        result = m4;
    }
    return result;
}

void HeightMap::printMap() {
    for (int i = 0; i < 257; i++) {
        for (int j = 0; j < 257; j++) {
            printf("%f\n", map[i][j]);
        }
    }
}

void HeightMap::draw() {
    glBegin(GL_QUADS);
    glColor3f(1.0,1.0,1.0);
    
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            glVertex3f(i, map[i][j], j);
            glVertex3f(i, map[i][j+1], j+1);
            glVertex3f(i+1, map[i+1][j+1], j+1);
            glVertex3f(i+1, map[i+1][j], j);
        }
    }
    
    glEnd();
    
}

void HeightMap::generateNewHeightMap() {
    resetMap();
    float initialValue = 10.0;
    map[0][0] = map[0][256] = map[256][0] = map[256][256] = initialValue;
    float range = 10.0;
    diamondSquareAlgorithm(0, 0, 256, 256, range, 256);
}

void HeightMap::resetMap() {
    for (int i = 0; i < 257; i++) {
        for (int j = 0; j < 257; j++) {
            map[i][j] = 0.0;
        }
    }
}

