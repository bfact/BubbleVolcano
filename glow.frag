//
//  glow.frag
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 12/2/15.
//  Copyright (c) 2015 RexWest. All rights reserved.

//tutorial on: http://www.learnopengl.com/#!Advanced-Lighting/Bloom
//The first step requires us to extract two images from a rendered scene.
//We could render the scene twice, both rendering to a different framebuffer
//with different shaders, but we can also use a neat little trick called
//Multiple Render Targets (MRT) that allows us to specify more than one
//fragment shader output; this gives us the option to extract the first two
//images in a single render pass. By specifying a layout location specifier
//before a fragment shader's output we can control to which colorbuffer a
//fragment shader writes to:

#extension ARB_explicit_attrib_location : enable

#ifdef ARB_explicit_attrib_location


layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;


varying vec3 vN;
varying vec3 v;

#define MAX_LIGHTS 3

void main()
{
    //[...] // first do normal lighting calculations and output results
    
    
    vec3 N = normalize(vN);
    vec4 lighting = vec4(0.0, 0.0, 0.0, 0.0);
    
    for (int i=0;i<MAX_LIGHTS;i++)
    {
        vec3 L = normalize(gl_LightSource[i].position.xyz - v);
        vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)
        vec3 R = normalize(-reflect(L,N));
        
        //calculate Ambient Term:
        vec4 Iamb = gl_FrontLightProduct[i].ambient;
        //calculate Diffuse Term:
        vec4 Idiff = gl_FrontLightProduct[i].diffuse * max(dot(N,L), 0.0);
        Idiff = clamp(Idiff, 0.0, 1.0);
        
        // calculate Specular Term:
        vec4 Ispec = gl_FrontLightProduct[i].specular
        * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);
        Ispec = clamp(Ispec, 0.0, 1.0);
        
        lighting += Iamb + Idiff + Ispec;
    }
    
    
    
    FragColor = vec4(lighting, 1.0f);
    // Check whether fragment output is higher than threshold, if so output as brightness color
    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(FragColor.rgb, 1.0);
}

#endif