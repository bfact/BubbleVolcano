//
//  bloom.frag
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 12/2/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

uniform sampler2D lavacracks;

float luminance = 1.0;
float middleGrey = 2.0;
float threshold = 1.0;

void main()
{
    vec3 colour = texture2D(lavacracks, gl_TexCoord[0].st).rgb;
    
    colour *= (middleGrey / luminance );
    colour *= 1.0 + (colour / (threshold * threshold) );
    colour -= 0.5;
    colour /=(1.0 + colour);
    
    gl_FragColor.rgb = colour;
}
