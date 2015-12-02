#include "Sphere.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


Sphere::Sphere(double radius, int slices, int stacks) : Drawable()
{
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
}

void Sphere::draw(DrawData& data)
{
//    material.apply();
    Material sphere = Material(Color(0.0, 0.0, 0.0, 0.1),
                               Color::diffuseMaterialDefault(),
                               Color::specularMaterialDefault(),
                               Color::emissionMaterialDefault(),
                               Color(0,1,1), 5.0);
    
    sphere.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    glutSolidSphere(radius, slices, stacks);
    
    glPopMatrix();
}


void Sphere::update(UpdateData& data)
{
    //
}


