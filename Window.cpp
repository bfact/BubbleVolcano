#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#define ROTATE

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "Globals.h"
#include "Texture.h"
#include "Skybox.h"
#include "BezierCurve.h"
#include "ParticleSystem.h"
#include "LSystem.h"

int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here

double fov = 60;
float objtan = (30/180.0) * M_PI;
Matrix4 m;

Vector3 lastPoint;  //Keep track of last point
int Movement;       //Mouse movement
int spinDir = 1;    //Cube spin direction
int source = 0;     //Light source

Skybox *starbox = new Skybox();

bool Window::lavaShader = true;
bool Window::clouds = false;

float x = 25.0, y = 10.0, z = 0.0;
bool simulate = false;

using namespace std;

void Window::initialize(void)
{
    //Setup the light
    Vector4 lightPos(0.0, 10.0, 15.0, 1.0);
    Globals::light.position = lightPos;
    Globals::light.quadraticAttenuation = 0.02;
    
    //Setup camera position
    Globals::camera.setE(Vector3(84.004, 29.0696, 41.0526));  //48.8881, 18.2326, 82.8526
    
    //Setup size
    Matrix4 setup;
    setup.makeScale((16.37 * objtan)/Globals::volcano.halfSizeMAX);    // 16.37
    Globals::volcano.toWorld = setup.multiply(Globals::volcano.toWorld);
    //Init textures
    Globals::volcano.initTextures();
    
    // Initialize Texture Collection
    Texture tex = Texture("/Users/seanwenzel/Github/bubblevolcano/lavacracks.ppm");
    Globals::textures.push_back(tex);
    
    // Initialize Textures
    Globals::map.initTextures();
    starbox->initTextures();
    
    //Globals::map.printMap();
    
    int level = 3;
    Globals::tree.system = new vector<string>();
    Globals::tree1.system = new vector<string>();
    for (int i = 0; i <= level; i++) {
        Globals::tree.structure();
        Globals::tree1.structure1();
        Globals::tree2.structure2();
        Globals::tree3.structure3();
    }


}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback()
{
    //Set up a static time delta for update calls
    Globals::updateData.dt = 1.0/60.0;// 60 fps
    
    //Call the display routine to draw the cube
    displayCallback();
    
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
    glViewport(0, 0, w, h);                                          //Set new viewport size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
    gluPerspective(fov, double(width)/(double)height, 1.0, 1000.0); //Set perspective projection viewing frustum
    glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{

    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
    gluPerspective(fov, double(width)/(double)height, 1.0, 1000.0); //Set perspective projection viewing frustum
    
    //Set the OpenGL matrix mode to ModelView
    glMatrixMode(GL_MODELVIEW);
    
    //Push a matrix save point
    //This will save a copy of the current matrix so that we can
    //make changes to it and 'pop' those changes off later.
    glPushMatrix();
    
    //Replace the current top of the matrix stack with the inverse camera matrix
    //This will convert all world coordiantes into camera coordiantes
    glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());
    
    //Bind the light to slot 0.  We do this after the camera matrix is loaded so that
    //the light position will be treated as world coordiantes
    //(if we didn't the light would move with the camera, why is that?)
    Globals::light.bind(0);

    glEnable(GL_COLOR_MATERIAL);

    // Generate light source:
    glEnable(GL_LIGHTING);
    
    glPushMatrix();
    glTranslatef(0, 60.00, 0);
    starbox->draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-128, -15, -128);
    Globals::map.draw();
    glPopMatrix();
    
    Globals::volcano.draw(Globals::drawData);
    Globals::particles.draw();
    

    if (simulate && x <= 80 && y <= 50 && z <= 60) {
        x += 0.15;
        y += 0.10;
        z += 0.15;
        Globals::camera.setE(Vector3(x, y, z));
        //Globals::camera.e.print("camera's e matrix");
    }

    

    glPushMatrix();
    glTranslatef(7.0, -7.0, 0.0);
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            Globals::tree.drawTree();
        }
    }
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(14.0, -3.0, 0.0);
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            Globals::tree1.drawTree1();
        }
    }
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-7.0, -3.0, 5.0);
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            Globals::tree2.drawTree2();
        }
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.0, -3.0, 10.0);
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
//            Globals::tree3.drawTree3();
        }
    }
    glPopMatrix();

    
    //Globals::bubbles.drawEntireCollection();
    //Globals::bubbles.updateEntireCollection();

    //ParticleSystem* particles = new ParticleSystem();
    //particles->draw();

    //Pop off the changes we made to the matrix stack this frame
    glPopMatrix();
    
    //Tell OpenGL to clear any outstanding commands in its command buffer
    //This will make sure that all of our commands are fully executed before
    //we swap buffers and show the user the freshly drawn frame
    glFlush();
    
    //Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
    glutSwapBuffers();
}

//----------------------------------------------------------------------------
// TODO: Keyboard callbacks!
// Callback method called by GLUT for processing normal keys.
void Window::processNormalKeys(unsigned char key, int x, int y)
{
    switch (key) {
//        case 'r':    // reset
//            Globals::camera = Camera();
//            break;
            
        case 'x':    // move left
            m.makeTranslate(-.5, 0, 0);
            Globals::objdraw->toWorld = m.multiply(Globals::objdraw->toWorld);
            displayPosition();
            break;
            
        case 'X':    // move right
            m.makeTranslate(.5, 0, 0);
            Globals::objdraw->toWorld = m.multiply(Globals::objdraw->toWorld);
            displayPosition();
            break;
            
        case 'y':   // move down
            m.makeTranslate(0, -.5, 0);
            Globals::objdraw->toWorld = m.multiply(Globals::objdraw->toWorld);
            displayPosition();
            break;
            
        case 'Y':    // move up
            m.makeTranslate(0, .5, 0);
            Globals::objdraw->toWorld = m.multiply(Globals::objdraw->toWorld);
            displayPosition();
            break;
            
        case 'z':    // move into
            m.makeTranslate(0, 0, -.5);
            Globals::objdraw->toWorld = m.multiply(Globals::objdraw->toWorld);
            displayPosition();
            break;
            
        case 'Z':    // move out of
            m.makeTranslate(0, 0, .5);
            Globals::objdraw->toWorld = m.multiply(Globals::objdraw->toWorld);
            displayPosition();
            break;
            
        case 'r':  {  // reset
            //Globals::objdraw->toWorld.identity();
            //Matrix4 setup;
            //setup.makeScale((16.37 * objtan)/Globals::volcano.halfSizeMAX);
            //Globals::volcano.toWorld = setup.multiply(Globals::volcano.toWorld);
            //displayPosition();
            Globals::camera.setE(Vector3(3.0577, 1.09578, 19.7345));
            break;
        }
        case 'o':    // orbit about z counterclockwise
        
            m.makeRotateZ(0.5);
            Globals::objdraw->toWorld = m.multiply(Globals::objdraw->toWorld);
            displayPosition();
            break;
        
        case 'O':    // orbit about z clockwise
            m.makeRotateZ(-0.5);
            Globals::objdraw->toWorld = m.multiply(Globals::objdraw->toWorld);
            displayPosition();
            break;
            
        case 's':    // scale down
            m.makeScale(.8);
            Globals::objdraw->toWorld = m.multiply(Globals::objdraw->toWorld);
            displayPosition();
            break;
            
        case 'S':    // scale up
            m.makeScale(1.2);
            Globals::objdraw->toWorld = m.multiply(Globals::objdraw->toWorld);
            displayPosition();
            break;
            
        case 't':
            Window::lavaShader = !Window::lavaShader;
            break;
            
        case 'c':
            Window::clouds = !Window::clouds;
            starbox->initTextures();
            break;
            
        case 'g':
            Globals::map.generateNewHeightMap();
            break;
            
        case 'b':
            simulate = !simulate;
            break;
        case 'p':
            if (Globals::red == true) {
                Globals::red = false;
                Globals::white = true;
            }
            else if (Globals::white == true) {
                Globals::white = false;
                Globals::rainbow = true;
            }
            else if (Globals::rainbow == true){
                Globals::rainbow = false;
                Globals::red = true;
            }
            break;
            
    }
}


//----------------------------------------------------------------------------
//TODO: Function Key callbacks!
// Callback method called by GLUT for processing normal keys.
void Window::processSpecialKeys(int key, int x, int y)
{

}

//TODO: Mouse callbacks!

void Window::processMouse(int button, int state, int x, int y)
{
    //Detect the left-button of the mouse being depressed
    if (button == GLUT_LEFT_BUTTON && glutGetModifiers() == GLUT_ACTIVE_CTRL) {         // right mouse -- x/y trans
        lastPoint = Vector3(x, y, 0);
        Movement = GLUT_RIGHT_BUTTON;
    } else if (button == GLUT_LEFT_BUTTON && glutGetModifiers() == GLUT_ACTIVE_SHIFT) { // mouse wheel -- scale
        lastPoint = Vector3(x, y, 0);
        Movement = GLUT_RIGHT_BUTTON + 1;
    } else if (button == GLUT_LEFT_BUTTON && glutGetModifiers() != GLUT_ACTIVE_CTRL && glutGetModifiers() != GLUT_ACTIVE_SHIFT) { // left
        lastPoint = trackBallMapping(x, y);
        Movement = button;
    }
}

//TODO: Mouse Motion callbacks!

void Window::processMouseActiveMotion(int x, int y)
{
    Vector3 currPoint;
    Vector3 direction;
    float rotAngle;
    
    switch (Movement) {
        case GLUT_LEFT_BUTTON: {   // rotation
            //std::cout << "GLU LEFT BUTTON" << std::endl;
            currPoint = trackBallMapping(x, y); //map mouse to logical sphere location
            currPoint = currPoint.normalize();
            lastPoint = lastPoint.normalize();
            direction = currPoint - lastPoint;
            float velocity = direction.magnitude();
            std::cout << velocity << std::endl;
            if (velocity > 0.0001) {
                Vector3 rotAxis;
                rotAxis = lastPoint.cross(currPoint);
                rotAxis = rotAxis.normalize();
                rotAngle = velocity * 0.025;
                Matrix4 lol;
                lol.makeRotateArbitrary(rotAxis, rotAngle);
                Globals::camera.setE(lol.multiply(Globals::camera.getE()));
                Globals::camera.e.print("camera's e matrix");
            }
            
            break;
        }
        case GLUT_RIGHT_BUTTON: {   // x/y translation
            //std::cout << "GLU RIGHT BUTTON" << std::endl;
            currPoint = Vector3(x, y, 0);
            direction.set((currPoint[0] - lastPoint[0]) *  0.001,
                          (currPoint[1] - lastPoint[1]) * -0.001, 0);
            Matrix4 lol;
            lol.makeTranslate(direction);
            Globals::camera.setE(Globals::camera.getE() + direction);
            Globals::camera.e.print("camera's e matrix");
            break;
        }
            
        case 3:     // mouse wheel -- scale
            //std::cout << "MOUSE WHEEL" << std::endl;
            currPoint = Vector3(x, y, 0);
            direction.set(0, 0, (currPoint[1] - lastPoint[1]) * -0.001);
            Matrix4 lol;
            lol.makeTranslate(direction);
            Globals::camera.setE(Globals::camera.getE() + direction);
            break;
            
    }
}


//----------------------------------------------------------------------------
//Utility routine to calculate teh 3D position of a projected unit vector onto
//the xy-plane. Given an y point on the xy-plane, we can think of it as the
//projection from a sphere down onto the plane.
Vector3 Window::trackBallMapping(int x, int y)
{
    Vector3 v;
    float d;
    v[0] = (2.0 * x - (float)width)/(float)width;
    v[1] = ((float)height - 2.0 * y)/(float)height;
    v[2] = 0.0;
    
    d = v.magnitude();
    d = (d < 1.0) ? d : 1.0;
    v[2] = sqrtf(1.001 - d * d);
    v.normalize();
    return v;
}



//----------------------------------------------------------------------------
// display the position of the cube.
void Window::displayPosition()
{
    Vector3 v;
    float vx;
    float vy;
    float vz;
    vx = Globals::objdraw->toWorld.get(3, 0);
    vy = Globals::objdraw->toWorld.get(3, 1);
    vz = Globals::objdraw->toWorld.get(3, 2);
    v = Vector3(vx,vy,vz);
    v.print("Position: ");
}

