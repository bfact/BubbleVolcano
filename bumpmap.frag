//
//  bumpmap.frag
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 12/4/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

uniform sampler2D color_texture;
uniform sampler2D normal_texture;

void main() {

    vec3 normal = normalize(texture2D(normal_texture, gl_TexCoord[0].st).rgb * 2.0 - 1.0);
    vec3 light_pos = normalize(vec3(0.0, 1.0, 10.5));
    float diffuse = max(dot(normal, light_pos), 0.0);
    vec3 color = diffuse * texture2D(color_texture, gl_TexCoord[0].st).rgb;
    
    gl_FragColor = vec4(color, 1.0);
}
