//
//  terrain.vert
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 12/2/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

varying vec4 vertexPos;
varying vec4 normal;

void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    vertexPos = gl_Position;
    
    //normal.xyz = gl_Normal;
    
    //normal.xyz = normalize(gl_Normal);
    
    normal.xyz = normalize(gl_NormalMatrix * gl_Normal);
    normal.w = gl_Vertex.y;

    
    gl_TexCoord[2] = gl_MultiTexCoord2;
    gl_TexCoord[3] = gl_MultiTexCoord3;
    gl_TexCoord[4] = gl_MultiTexCoord4;
}