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
#include "Globals.h"
#include <limits>
#include <random>

#define TERRAINVERTEX "/Users/BrittanyFactura/GitHub/bubblevolcano/terrain.vert"
#define TERRAINFRAGMENT "/Users/BrittanyFactura/GitHub/bubblevolcano/terrain.frag"
#define SNOW "/Users/BrittanyFactura/GitHub/bubblevolcano/snow.ppm"
#define ROCK "/Users/BrittanyFactura/GitHub/bubblevolcano/rock.ppm"
#define GRASS "/Users/BrittanyFactura/GitHub/bubblevolcano/grass.ppm"
#define DIRT "/Users/BrittanyFactura/GitHub/bubblevolcano/dirt.ppm"
// Sean
#define SNOW_SEAN "/Users/seanwenzel/Github/bubblevolcano/snow.ppm"
#define ROCK_SEAN "/Users/seanwenzel/GitHub/bubblevolcano/rock.ppm"
#define GRASS_SEAN "/Users/seanwenzel/GitHub/bubblevolcano/grass.ppm"
#define DIRT_SEAN "/Users/seanwenzel/GitHub/bubblevolcano/dirt.ppm"
#define TERRAINVERTEX_SEAN "/Users/seanwenzel/GitHub/bubblevolcano/terrain.vert"
#define TERRAINFRAGMENT_SEAN "/Users/seanwenzel/GitHub/bubblevolcano/terrain.frag"

Texture snow;
Texture rock;
Texture grass;
Texture dirt;

using namespace std;

// Generate a height map using the Diamond-Square algorithm
HeightMap::HeightMap() {
    float initialValue = 10.0;
    map[0][0] = map[0][256] = map[256][0] = map[256][256] = initialValue;
    float range = 10.0;
    diamondSquareAlgorithm(0, 0, 256, 256, range, 256);
    evalNormals();   
    
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
    
    float i, j;
    
    int DATA_SIZE = 257;
    
    
    float h = 50.0;//the range (-h -> +h) for the average offset
    float r = getRnd(h);//for the new value in range of h
        for(int sideLength = DATA_SIZE-1;
                sideLength >= 2;
        
        sideLength /=2, h/= 2.0){
        
        int halfSide = sideLength/2;
        
        //generate the new square values
        for(int x=0;x<DATA_SIZE-1;x+=sideLength){
            for(int y=0;y<DATA_SIZE-1;y+=sideLength){
                
                float avg = map[x][y] + //top left
                map[x+sideLength][y] +//top right
                map[x][y+sideLength] + //lower left
                map[x+sideLength][y+sideLength];//lower right
                avg /= 4.0;
                
                j = ((float) rand() / (RAND_MAX));
                //center is average plus random offset
                map[x+halfSide][y+halfSide] =
                
                avg + (j*2*h) - h;
            }
        }
        
        
        for(int x=0;x<DATA_SIZE-1;x+=halfSide){
            
            for(int y=(x+halfSide)%sideLength;y<DATA_SIZE-1;y+=sideLength){
               
                float avg =
                map[(x-halfSide+DATA_SIZE)%DATA_SIZE][y] + //left of center
                map[(x+halfSide)%DATA_SIZE][y] + //right of center
                map[x][(y+halfSide)%DATA_SIZE] + //below center
                map[x][(y-halfSide+DATA_SIZE)%DATA_SIZE]; //above center
                avg /= 4.0;
                
                
                i = ((float) rand() / (RAND_MAX));
                avg = avg + (i*2*h) - h;
                //update value for center of diamond
                map[x][y] = avg;
                
                
                if(x == 0)  map[DATA_SIZE-1][y] = avg;
                if(y == 0)  map[x][DATA_SIZE-1] = avg;
            }
        }
    }
    float min = std::numeric_limits<float>::max();
    for (int i = 123; i < 133; i++) {
        for (int j = 123; j < 133; j++ ) {
            if (map[i][j] < min) {
                min = map[i][j];
            }
        }
    }
    Globals::volcanoHeightDisplacement = min-8.55664;
    findMinAndMax();
    evalNormals();
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

    glActiveTexture(GL_TEXTURE2);
    snow.bind();
    
    glActiveTexture(GL_TEXTURE3);
    rock.bind();
    
    glActiveTexture(GL_TEXTURE4);
    dirt.bind();

    Shader* terrain = new Shader(TERRAINVERTEX, TERRAINFRAGMENT);
    terrain->bind();
    
    // to have your dirt sampler get the dirt texture, you need to do:
    GLhandleARB programHandle = terrain->getPid();
    
    GLint snowSamplerHandle = glGetUniformLocationARB(programHandle, "snow");
    GLint rockSamplerHandle = glGetUniformLocationARB(programHandle, "rock");
    GLint dirtSamplerHandle = glGetUniformLocationARB(programHandle, "dirt");
    
    //do this every frame -- according to king alexander hawker
    glUniform1i(snowSamplerHandle, 2);        //number corresponds to glActiveTexture
    glUniform1i(rockSamplerHandle, 3);
    glUniform1i(dirtSamplerHandle, 4);
    
    //printf("Snow texture id %u \n", snow.id);
    //printf("Rock texture id %u \n", rock.id);
    //printf("Grass texture id %u \n", grass.id);

    glBegin(GL_QUADS);
    glColor3f(1.0,1.0,1.0);
    
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            Vector3 n0 = normals[i][j];
            Vector3 n1 = normals[i][j + 1];
            Vector3 n2 = normals[i + 1][j + 1];
            Vector3 n3 = normals[i + 1][j];
            
            glMultiTexCoord2f(GL_TEXTURE2, 0.0, 0.0);
            glMultiTexCoord2f(GL_TEXTURE3, 0.0, 0.0);
            glMultiTexCoord2f(GL_TEXTURE4, 0.0, 0.0);
            //glTexCoord2f(0, 0);
            glVertex3f(i, map[i][j], j);
            glNormal3f(n0[0], n0[1], n0[2]);
            
            glMultiTexCoord2f(GL_TEXTURE2, 0.0, 1.0);
            glMultiTexCoord2f(GL_TEXTURE3, 0.0, 1.0);
            glMultiTexCoord2f(GL_TEXTURE4, 0.0, 1.0);
            //glTexCoord2f(0, 1);
            glVertex3f(i, map[i][j+1], j+1);
            glNormal3f(n1[0], n1[1], n1[2]);

            glMultiTexCoord2f(GL_TEXTURE2, 1.0, 1.0);
            glMultiTexCoord2f(GL_TEXTURE3, 1.0, 1.0);
            glMultiTexCoord2f(GL_TEXTURE4, 1.0, 1.0);
            //glTexCoord2f(1, 1);
            glVertex3f(i+1, map[i+1][j+1], j+1);
            glNormal3f(n2[0], n2[1], n2[2]);

            glMultiTexCoord2f(GL_TEXTURE2, 1.0, 0.0);
            glMultiTexCoord2f(GL_TEXTURE3, 1.0, 0.0);
            glMultiTexCoord2f(GL_TEXTURE4, 1.0, 0.0);
            //glTexCoord2f(1, 0);
            glVertex3f(i+1, map[i+1][j], j);
            glNormal3f(n2[0], n2[1], n2[2]);

        }
    }
    
    glEnd();
    
    snow.unbind();
    rock.unbind();
    dirt.unbind();
    
    terrain->unbind();
    
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


void HeightMap::initTextures()
{
    // Brittany's version
    
    snow = Texture(SNOW);
    rock = Texture(ROCK);
    grass= Texture(GRASS);
    dirt = Texture(DIRT);
    
    
    // Sean's version
    /*
     snow = Texture(SNOW_SEAN);
     rock = Texture(ROCK_SEAN);
     grass= Texture(GRASS_SEAN);
     dirt = Texture(DIRT_SEAN);
    */
}

void HeightMap::evalNormals()
{
    
    for (int i = 0; i < 257; i++) {
        for (int j = 0; j < 257; j++) {
            
            Vector3 v0 = Vector3(i, map[i][j], j);
            Vector3 v1 = Vector3(i, map[i][j+1], j+1);
            Vector3 v2 = Vector3(i+1, map[i+1][j+1], j+1);
            Vector3 v3 = Vector3(i+1, map[i+1][j], j);

            Vector3 vn0 = Vector3(v1 - v0);
            Vector3 vn1 = Vector3(v2 - v0);
            vn0.normalize();
            vn1.normalize();
            
            //vn0.print("vn0");
            //vn1.print("vn1");
            
            Vector3 normal = (vn0.cross(vn1)).normalize();
            
            normals[i][j] = normal;
           
            
            //normals[i][j].print("Height map normals");
            
        }
    }
}

void HeightMap::smoothTerrain(float k)
{
    
    int i, j;
    
    for(i = 0; i < 256;i++)
        for(j = 1; j < 256;j++)
            map[i][j] =  map[i][j] * (1 - k) + map[i][j-1] * k;
    
    for(i = 1; i < 256;i++)
        for(j = 0; j < 256;j++)
            map[i][j] =  map[i][j] * (1-k) + map[i-1][j] * k;
    
    for(i = 0; i < 256; i++)
        for(j= 256-1;j>-1;j--)
            map[i][j] =  map[i][j] * (1-k) + map[i][j+1] * k;
    
    for(i = 256-2; i < -1; i--)
        for(j = 0 ;j < 256; j++)
            map[i][j] = map[i][j] * (1-k) + map[i+1][j] * k;
    
    
}
