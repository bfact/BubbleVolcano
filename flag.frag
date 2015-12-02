//
//  flag.frag
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 11/20/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

varying vec3 normal;
uniform sampler2D textureSampler;

void main (void)
{
    
    vec2 st = gl_TexCoord[0].st;
    vec4 textureColor = texture2D(textureSampler, st);
    
    if ((textureColor[0] <= 0.2) && (textureColor[1] <= 0.2) && (textureColor[2] <= 0.2)) {
        vec4 transparent = vec4(1.0, 1.0, 1.0, 0.3);
        gl_FragColor = transparent;
    }
    
//    else if ((textureColor[0] >= 0.6) && (textureColor[1] <= 0.6) && (textureColor[2] <= 0.6)) {
    else {
        vec3 n = normal * 0.5;
        n = n + vec3(0.5, 0.5, 0.5);
        gl_FragColor = vec4(n[0], n[1], n[2], 1);
    }
}