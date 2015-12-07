//
//  glow.vert
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 12/2/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//


varying vec3 N;
varying vec3 v;

void main(void)
{
//    v = vec3(gl_ModelViewMatrix * gl_Vertex);
//    N = normalize(gl_NormalMatrix * gl_Normal);
//    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ftransform();
}