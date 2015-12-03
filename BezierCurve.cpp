//
//  BezierCurve.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Brittany Factura on 11/10/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "BezierCurve.h"
#include "Shader.h"
#include "Window.h"
#include <cmath>

#define VERTEX "/Users/BrittanyFactura/Desktop/Fall Quarter/CSE 167/projects/project 6/flag.vert"
#define FRAGMENT "/Users/BrittanyFactura/Desktop/Fall Quarter/CSE 167/projects/project 6/flag.frag"


Matrix4 pm0;
Matrix4 pm1;
Matrix4 pm2;
Matrix4 pm3;

BezierCurve::BezierCurve()
{
    controls[0]  = Vector4(-3.00,   0.00,   0.00);
    controls[1]  = Vector4( 0.00,   1.25,   3.00);
    controls[2]  = Vector4( 3.00,   0.75,  -3.00);
    controls[3]  = Vector4( 6.00,   0.00,   0.00);
    
    controls[4]  = Vector4(-3.00,   2.00,   0.00);
    controls[5]  = Vector4( 0.00,   3.25,   3.00);
    controls[6]  = Vector4( 3.00,   2.75,  -3.00);
    controls[7]  = Vector4( 6.00,   2.00,   0.00);
    
    controls[8]  = Vector4(-3.00,   4.00,   0.00);
    controls[9]  = Vector4( 0.00,   5.25,   3.00);
    controls[10] = Vector4( 3.00,   4.75,  -3.00);
    controls[11] = Vector4( 6.00,   4.00,   0.00);
    
    controls[12] = Vector4(-3.00,   6.00,   0.00);
    controls[13] = Vector4( 0.00,   7.25,   3.00);
    controls[14] = Vector4( 3.00,   6.75,  -3.00);
    controls[15] = Vector4( 6.00,   6.00,   0.00);
    
    
    pm0 = createMatrix(controls[0],  controls[1],  controls[2],  controls[3]);
    pm1 = createMatrix(controls[4],  controls[5],  controls[6],  controls[7]);
    pm2 = createMatrix(controls[8],  controls[9],  controls[10], controls[11]);
    pm3 = createMatrix(controls[12], controls[13], controls[14], controls[15]);
    
}


BezierCurve::~BezierCurve()
{
    
}

void BezierCurve::initTextures()
{
    logo = Texture("/Users/BrittanyFactura/Desktop/ppm/Ucsd-logo.ppm");
}


//Calculate the Bernstein coefficient
//n: degree of curve, i: Berstein coefficient, t: time
float BezierCurve::Bernstein(float n, float i, float t)
{
    //C(n, i) = n! / ((n-1)! * i!)
    float fact = factorial(3) / (factorial(3 - i) * factorial(i));
    return (fact * pow((1.0 - t), (3 - i)) * pow(t, i));
}

float BezierCurve::factorial(float n)
{
    if (n <= 1)
        return 1;
    return (n * factorial(n - 1));
}


// Matrix-vector product in disguise!
Vector4 BezierCurve::evalBezier(Matrix4 p, float t)
{
    //q = points matrix * bernstein vector
    Vector4 C = Vector4(Bernstein(3, 0, t), Bernstein(3, 1, t), Bernstein(3, 2, t), Bernstein(3, 3, t) );
    Vector4 q = p.multiply(C);
    return q;
}

Matrix4 BezierCurve::createMatrix(Vector4 p0, Vector4 p1, Vector4 p2, Vector4 p3)
{
    
    Matrix4 q;
    q.set(p0[0], p1[0], p2[0], p3[0],
          p0[1], p1[1], p2[1], p3[1],
          p0[2], p1[2], p2[2], p3[2],
          0, 0, 0, 0);
    
    return q;
}

void BezierCurve::createPatch()
{
    
    Vector4 q0, q1, q2, q3;
    Vector4 r;
    
    Matrix4 qm, rm;
    
    for (int x = 0; x < 100; x++) {
        float u = ((float)x)/((float)101);
        
        for (int y = 0 ; y < 100; y++) {
            float v = ((float)y)/((float)101);
            
            q0 = evalBezier(pm0, u);
            q1 = evalBezier(pm1, u);
            q2 = evalBezier(pm2, u);
            q3 = evalBezier(pm3, u);
            
            qm = createMatrix(q0, q1, q2, q3);
        
            
            //bezier patch point
            r = evalBezier(qm, v);
            
            vertices[x][y] = r;
            evalNormals(u, v, x, y);
            
        }
    }
    
}

void BezierCurve::evalNormals(float u, float v, int x, int y)
{
    Vector4 q0, q1, q2, q3;
    Vector4 r0, r1, r2, r3;
    Vector4 tan_u;
    Vector4 tan_v;
    Matrix4 qm, rm;
    Vector4 u0, u1, v0;
    
    float delta_t = 0.00001;
    
    q0 = evalBezier(pm0, u);
    q1 = evalBezier(pm1, u);
    q2 = evalBezier(pm2, u);
    q3 = evalBezier(pm3, u);
    qm = createMatrix(q0, q1, q2, q3);
    
    r0 = evalBezier(pm0, u + delta_t);
    r1 = evalBezier(pm1, u + delta_t);
    r2 = evalBezier(pm2, u + delta_t);
    r3 = evalBezier(pm3, u + delta_t);
    rm = createMatrix(r0, r1, r2, r3);
    
    u0 = evalBezier(qm, v);
    u1 = evalBezier(qm, v + delta_t);
    
    tan_u = u1 - u0;
    
    v0 = evalBezier(rm, v);
    
    tan_v = v0 - u0;
    
    tan_u.normalize();
    tan_v.normalize();
    
    Vector3 normal = tan_v.toVector3().cross(tan_u.toVector3());
    
    normals[x][y] = normal;
}

void BezierCurve::draw()
{
    Shader* shader = new Shader(VERTEX, FRAGMENT);
    
    Vector4 q0, q1, q2, q3;
    Vector3 n0, n1, n2, n3;
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    logo.bind();
//    if (Window::shader) shader->bind();
    
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    for (int i = 0; i < 99; i++) {
        
        for (int j = 0; j < 99; j++) {
            
            q0 = vertices[i][j];
            q1 = vertices[i][j + 1];
            q2 = vertices[i + 1][j + 1];
            q3 = vertices[i + 1][j];
            
            n0 = normals[i][j];
            n1 = normals[i][j + 1];
            n2 = normals[i + 1][j + 1];
            n3 = normals[i + 1][j];
            
            
            glTexCoord2f( (float)j/100.0, (float)i/100.0);
            glVertex3f(q0[0], q0[1], q0[2]);
            glNormal3f(n0[0], n0[1], n0[2]);
            
            
            glTexCoord2f( ((float)j+1)/100.0, (float)i/100.0);
            glVertex3f(q1[0], q1[1], q1[2]);
            glNormal3f(n1[0], n1[1], n1[2]);
            
            
            glTexCoord2f( ((float)j+1)/100.0, ((float)i+1)/100.0);
            glVertex3f(q2[0], q2[1], q2[2]);
            glNormal3f(n2[0], n2[1], n2[2]);
            
            
            glTexCoord2f( (float)j/100.0, ((float)i+1)/100.0);
            glVertex3f(q3[0], q3[1], q3[2]);
            glNormal3f(n3[0], n3[1], n3[2]);
        }
    }
    glEnd();
    logo.unbind();
//    if (Window::shader) shader->unbind();
    
    
    
//        glPointSize(10.0);
//        glBegin(GL_POINTS);
//        glColor3f(1.0f, 0.0f, 0.0f);
//        for(int i = 0; i < 16; i++) {
//            glVertex3f(controls[i].get(0), controls[i].get(1), controls[i].get(2));
//        }
//        glEnd();
    
    
}










