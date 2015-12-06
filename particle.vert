//
//  particle.vert
//

#version 400
   // Initial velocity and start time
   layout (location = 0) in vec3 VertexInitVel;
   layout (location = 1) in float StartTime;
   out float Transp;  // Transparency of the particle
   uniform float Time = 0.0;  // Animation time
   uniform vec3 Gravity = vec3(0.0,-0.05,0.0);  // world coords
   uniform float ParticleLifetime = 10000.0;  // Max particle lifetime
   uniform mat4 MVP;
void main() {
       // Assume the initial position is (0,0,0).
       vec3 pos = vec3(0.0);
       Transp = 0.0;
       // Particle doesn't exist until the start time
       if( Time >StartTime ) {
         float t = Time - StartTime;
         if( t <ParticleLifetime ) {
         pos = VertexInitVel * t + Gravity * t * t;
         Transp = 1.0 - t / ParticleLifetime;
} }
     gl_Position = MVP * vec4(pos, 1.0);
   }