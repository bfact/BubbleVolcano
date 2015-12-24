//
//  terrain.frag
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 12/2/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

uniform sampler2D snow;    // (we'll bind to texture unit 0)
uniform sampler2D rock;    // (we'll bind to texture unit 1)
uniform sampler2D dirt;   // (we'll bind to texture unit 2)

varying vec4 vertexPos;
varying vec4 normal;

float blendAmount;

void main(void) {

    vec4 snowColor = texture2D(snow, gl_TexCoord[2].st);
    vec4 rockColor = texture2D(rock, gl_TexCoord[3].st);
    vec4 dirtColor = texture2D(dirt, gl_TexCoord[4].st);
    
    
    //----- Height-based texturing -----//
    
    
    float height = normal.w;
    
    vec4 mixColor = mix(snowColor, rockColor, dirtColor);
    vec4 terrainColor = vec4(0.0, 0.0, 0.0, 1.0);
    
    // Terrain region 1
    terrainColor += 0.75 * texture2D(snow, gl_TexCoord[2].st);
    // Terrain region 2
    terrainColor += 0.75 * texture2D(rock, gl_TexCoord[3].st);
    // Terrain region 3
    terrainColor += 0.75 * texture2D(dirt, gl_TexCoord[4].st);
    
    vec4 vTexColor = vec4(0.0);
    
    // vertexPos[1]
    if (height < 16.00)
        gl_FragColor = rockColor;
    
    else if (height >= 16.00 && height < 18.00)
    {
        //gl_FragColor = mix(rockColor, dirtColor, 0.75);
        vTexColor += snowColor * 0.95;
        vTexColor += dirtColor * 0.05;
        gl_FragColor = vTexColor;
    }
    else if ((height >= 19.50 && height < 22.50))
        gl_FragColor = dirtColor;
    
    else if (height >= 28.00 && height < 30.50)
        gl_FragColor = mix(dirtColor, snowColor, 0.95);
    
    else if (height >= 33.50)
        gl_FragColor = snowColor;
    
    else
        gl_FragColor = mix(dirtColor, snowColor, 0.95);
     
     
    
    
    //----- TO DO:: SLOPE -----//
    
     //You simply subtract one from the Y (height) value of the normal.
     //This will give you a value between 0.0f (completely flat terrain)
     //1.0f (terrain pointing straight up at 90 degrees).

//    height = normal.y;
//    float slope = 1.0 - height;
//    
//    if (slope < 0.0) slope = slope * 1.0;
//    
//    if (slope < 0.2)
//        gl_FragColor = dirtColor;
//
//
//    else if ((slope >= 0.2) && (slope < 0.5))
//    {
//        blendAmount = (slope - 0.2) * (1.0 / (0.5 - 0.2));
//        gl_FragColor = mix(dirtColor, rockColor, blendAmount);
//    }
//
//    else if ((slope >= 0.5) || (normal.w > 20.0))
//    {
//        blendAmount = (slope - 0.5) * (1.0 / 0.5);
//        gl_FragColor = mix(dirtColor, snowColor, 1.0);
//    }

//    
//    if (slope < 0.2) gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
//    if ((slope >= 0.2) && (slope < 0.5)) gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
//    if (slope >= 0.5) gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);

}