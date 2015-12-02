//
//  flag.vert
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 11/20/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

varying vec3 normal;

void main(void)
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    normal = normalize(gl_Normal);
    gl_TexCoord[0] = gl_MultiTexCoord0;
}
