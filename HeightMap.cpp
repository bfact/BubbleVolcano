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
#include "Texture.h"
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
    
    /*
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
    
    diamondSquareAlgorithm(x1, y1, x2, y2, range / 2, level / 2); */
    
    float i, j;
    
    //size of grid to generate, note this must be a
    //value 2^n+1
    int DATA_SIZE = 257;
    //an initial seed value for the corners of the data
    //float SEED = 1000.0;
    //float map[DATA_SIZE][DATA_SIZE];
    //seed the data
    //data[0][0] = data[0][DATA_SIZE-1] = data[DATA_SIZE-1][0] =
    //data[DATA_SIZE-1][DATA_SIZE-1] = SEED;
    
    float h = 50.0;//the range (-h -> +h) for the average offset
    float r = getRnd(h);//for the new value in range of h
    //side length is distance of a single square side
    //or distance of diagonal in diamond
    for(int sideLength = DATA_SIZE-1;
        //side length must be >= 2 so we always have
        //a new value (if its 1 we overwrite existing values
        //on the last iteration)
        sideLength >= 2;
        //each iteration we are looking at smaller squares
        //diamonds, and we decrease the variation of the offset
        sideLength /=2, h/= 2.0){
        //half the length of the side of a square
        //or distance from diamond center to one corner
        //(just to make calcs below a little clearer)
        int halfSide = sideLength/2;
        
        //generate the new square values
        for(int x=0;x<DATA_SIZE-1;x+=sideLength){
            for(int y=0;y<DATA_SIZE-1;y+=sideLength){
                //x, y is upper left corner of square
                //calculate average of existing corners
                float avg = map[x][y] + //top left
                map[x+sideLength][y] +//top right
                map[x][y+sideLength] + //lower left
                map[x+sideLength][y+sideLength];//lower right
                avg /= 4.0;
                
                j = ((float) rand() / (RAND_MAX));
                //center is average plus random offset
                map[x+halfSide][y+halfSide] =
                //We calculate random value in range of 2h
                //and then subtract h so the end value is
                //in the range (-h, +h)
                avg + (j*2*h) - h;
            }
        }
        
        //generate the diamond values
        //since the diamonds are staggered we only move x
        //by half side
        //NOTE: if the data shouldn't wrap then x < DATA_SIZE
        //to generate the far edge values
        for(int x=0;x<DATA_SIZE-1;x+=halfSide){
            //and y is x offset by half a side, but moved by
            //the full side length
            //NOTE: if the data shouldn't wrap then y < DATA_SIZE
            //to generate the far edge values
            for(int y=(x+halfSide)%sideLength;y<DATA_SIZE-1;y+=sideLength){
                //x, y is center of diamond
                //note we must use mod  and add DATA_SIZE for subtraction
                //so that we can wrap around the array to find the corners
                float avg =
                map[(x-halfSide+DATA_SIZE)%DATA_SIZE][y] + //left of center
                map[(x+halfSide)%DATA_SIZE][y] + //right of center
                map[x][(y+halfSide)%DATA_SIZE] + //below center
                map[x][(y-halfSide+DATA_SIZE)%DATA_SIZE]; //above center
                avg /= 4.0;
                
                //new value = average plus random offset
                //We calculate random value in range of 2h
                //and then subtract h so the end value is
                //in the range (-h, +h)
                i = ((float) rand() / (RAND_MAX));
                avg = avg + (i*2*h) - h;
                //update value for center of diamond
                map[x][y] = avg;
                
                //wrap values on the edges, remove
                //this and adjust loop condition above
                //for non-wrapping values.
                if(x == 0)  map[DATA_SIZE-1][y] = avg;
                if(y == 0)  map[x][DATA_SIZE-1] = avg;
            }
        }
    }
    findMinAndMax();
}

void HeightMap::findMinAndMax() {
    for (int i = 0; i < 257; i++) {
        for (int j = 0; j < 257; j++) {
            if (map[i][j] < min) {
                min = map[i][j];
            }
            if (map[i][j] > max) {
                max = map[i][j];
            }
        }
    }
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
    //Texture texture = Texture("/Users/seanwenzel/Github/bubblevolcano/icesnow.ppm");
    //texture.bind();
    glBegin(GL_QUADS);
    glColor3f(1.0,1.0,1.0);
    
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            
            glTexCoord2f(0, 1); glVertex3f(i, map[i][j], j);
            glTexCoord2f(0, 0); glVertex3f(i, map[i][j+1], j+1);
            glTexCoord2f(1, 0); glVertex3f(i+1, map[i+1][j+1], j+1);
            glTexCoord2f(1, 1); glVertex3f(i+1, map[i+1][j], j);
        }
    }
    
    glEnd();
    //texture.unbind();
    
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

