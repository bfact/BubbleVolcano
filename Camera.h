#ifndef CSE167_Camera_h
#define CSE167_Camera_h

#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"

class Camera
{
private:
    
protected:
    
    Matrix4 c;   //Camera Matrix
    Matrix4 ci;  //Inverse of Camera Matrix
    
public:
    
    Vector3 e;   //Center of Projection
    Vector3 d;   //Look At
    Vector3 up;  //Up Vector ^
    
    Camera(void);
    ~Camera(void);
    
    void update(void);
    
    Matrix4& getMatrix(void);
    Matrix4& getInverseMatrix(void);
    
    Vector3 getPosition(void);
    
    void set(Vector3&, Vector3&, Vector3&);
    
    Vector3 getE(void);
    void setE(Vector3);
};

#endif
