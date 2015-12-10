//
//  bumpmap.vert
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 12/4/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0;

    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}