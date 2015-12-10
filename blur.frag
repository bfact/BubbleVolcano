//
//  blur.frag
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 12/2/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

uniform sampler2D lavacracks;
//uniform vec2 pixelSize;
varying vec4 vertexPos;

void main()
{
    vec2 offset[9];
    vec3 colourOut = vec3(0.0);
    
    offset[0] = vec2(-vertexPos.x, -vertexPos.y);
    offset[1] = vec2( 0.0, -vertexPos.y);
    offset[2] = vec2(+vertexPos.x, -vertexPos.y);
                            
    offset[3] = vec2(-vertexPos.x, 0.0);
    offset[4] = vec2( 0.0, 0.0);
    offset[5] = vec2(+vertexPos.x, 0.0);
    
    offset[6] = vec2(-vertexPos.x, +vertexPos.y);
    offset[7] = vec2( 0.0, +vertexPos.y);
    offset[8] = vec2(+vertexPos.x, +vertexPos.y);
    
    for( int i = 0; i < 9; i++ )
    {
        colourOut += texture2D(lavacracks, gl_TexCoord[0].xy + offset[i] ).rgb;
    }
    
    vec4 result = vec4(colourOut[0], colourOut[1], colourOut[2], 0);
    
    gl_FragColor = result;
}