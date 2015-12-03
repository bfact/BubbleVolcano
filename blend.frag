//
//  blend.frag
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 12/2/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

uniform sampler2D input_scene;
uniform sampler2D input_bloom;

vec3 screen(vec3 colour1, vec3 colour2)
{
    return ( 1.0- (1.0 - colour1) * (1.0 - colour2) );
}

void main()
{
    vec3 colourA = texture2D(input_scene, gl_TexCoord[0].st).rgb;
    vec3 colourB = texture2D(input_bloom, gl_TexCoord[0].st).rgb;
    gl_FragColor.rgb = screen(colourA, colourB);
}
