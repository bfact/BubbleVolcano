//
//  blur.frag
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 12/2/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

uniform sampler2D inputImage;
uniform vec2 pixelSize;

void main()
{
    vec3 colourOut = vec3(0.0);
    
    vec2 offset[9] = vec2[]( // Bottom of the kernal
                            vec2(-pixelSize.x, -pixelSize.y),
                            vec2( 0.0, -pixelSize.y),
                            vec2(+pixelSize.x, -pixelSize.y),
                            
                            // Middle of the kernal
                            vec2(-pixelSize.x, 0.0),
                            vec2( 0.0, 0.0),
                            vec2(+pixelSize.x, 0.0),
                            
                            //Top of the kernal
                            vec2(-pixelSize.x, +pixelSize.y),
                            vec2( 0.0, +pixelSize.y),
                            vec2(+pixelSize.x, +pixelSize.y)  );
    
    for( int i = 0; i < 9; i++ )
    {
        colourOut += texture2D(inputImage, texCoord + offset[i] ).rgb;
    }
    
    return ( colourOut / 9.0);
}