#include "OBJObject.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include "Globals.h"
#include <sstream>
#include <fstream>

#define deleteVector(__type__, __vect__) do {\
                                   std::vector<__type__>::iterator iter; \
                                   std::vector<__type__>::iterator end; \
                                   iter = __vect__->begin();\
                                   end = __vect__->end();\
                                   while(iter != end) delete (*(iter++));\
                                   delete __vect__;\
                               } while(false)

#define LAVACRACKS "/Users/BrittanyFactura/GitHub/bubblevolcano/lavacracks.ppm"
#define VERTEX "/Users/BrittanyFactura/GitHub/bubblevolcano/glow.vert"
//#define FRAGMENT "/Users/BrittanyFactura/GitHub/bubblevolcano/glow.frag"
#define FRAGMENT "/Users/BrittanyFactura/GitHub/bubblevolcano/bloom.frag"

using namespace std;

OBJObject::OBJObject(std::string filename) : Drawable()
{
    this->vertices = new std::vector<Vector3*>();
    this->normals = new std::vector<Vector3*>();
    this->faces = new std::vector<Face*>();
    this->colors = new std::vector<Vector3*>();
    
    parse(filename);
}

OBJObject::~OBJObject()
{
    //Delete any dynamically allocated memory/objects here
    
    deleteVector(Vector3*, vertices);
    deleteVector(Vector3*, normals);
    deleteVector(Face*, faces);
    deleteVector(Vector3*, colors);
}

void OBJObject::draw(DrawData& data)
{
    Face* face;
    
//    material.apply();
    
    Color none     = Color(0.0, 0.0, 0.0, 1.0);
    Color all      = Color(1.0, 1.0, 1.0, 1.0);
    Color ambient  = Color(0.2, 0.2, 0.2, 1.0);
    Color diffuse1 = Color(0.1, 0.5, 0.8, 1.0);
    Color diffuse2 = Color(0.4, 0.5, 0.6, 1.0);
    Color diffuse3 = Color(0.8, 0.8, 0.8, 1.0);
    Color emission = Color(0.3, 0.2, 0.2, 0.0);
    
    Material bunny = Material(Color::ambientMaterialDefault(),
                              none,
                              all,
                              none,
                              Color(0.0,1.0,0.0), 128.0);
    
//    Material dragon = Material(ambient,
//                               Color::diffuseMaterialDefault(),
//                               Color::specularMaterialDefault(),
//                               none,
//                               Color(0,1.0,0), 128.0);
    
    Material dragon = Material(ambient,
                               diffuse1,
                               none,
                               none,
                               Color(0,1.0,0), 50.0);

    
    Material bear = Material(Color::ambientMaterialDefault(),
                             none,
                             all,
                             none,
                             Color(1.0,1.0,0), 5.0);
    
//    if (Globals::objdraw == &Globals::bunny)
//        bunny.apply();
//    else if (Globals::objdraw == &Globals::dragon)
//        dragon.apply();
//    else if (Globals::objdraw == &Globals::bear)
//        bear.apply();
    
    Shader* bloom = new Shader(VERTEX, FRAGMENT);
    Shader* blur  = new Shader(VERTEX, FRAGMENT);
    Shader* blend = new Shader(VERTEX, FRAGMENT);
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    cout << "Starting draw" << endl;
    
    lavacracks.bind();
//    lavacracks.frameBufferSetup();
    if (Window::shader) {
        bloom->bind();
        blur->bind();
        blend->bind();
    }
    
    glBegin(GL_TRIANGLES);
//    glBegin(GL_QUADS);
    
    for (int i = 0; i < faces->size(); i++) {
        face = faces->at(i);
        for (int j = 0; j < 3; j++) {
            Vector3 vn = *normals->at(face->normalIndices[j]);
            vn = vn.normalize();
            glNormal3f(vn[0], vn[1], vn[2]);
            if (color) {
                Vector3 c = *colors->at(face->vertexIndices[j]);
//                glColor4f(c[0], c[1], c[2], 0.5);
                glColor4f(1.0, 1.0, 1.0, 0.0);
            }
            Vector3 v  = *vertices->at(face->vertexIndices[j]);
            if (j == 0) {
                glTexCoord2f(0, 0);
                glVertex3f(v[0], v[1], v[2]);
            }
            else if (j == 1) {
                glTexCoord2f(1, 0);
                glVertex3f(v[0], v[1], v[2]);
            }
            else if (j == 2) {
                glTexCoord2f(0.5, 1);
                glVertex3f(v[0], v[1], v[2]);
            }
        }
    }
    
    glEnd();
    lavacracks.unbind();
    if (Window::shader) {
        bloom->unbind();
        blur->unbind();
        blend->unbind();
    }
    cout << "Finished draw" << endl;
    
    glPopMatrix();
}

void OBJObject::update(UpdateData& data)
{
    //
}

void OBJObject::parse(std::string& filename)
{
    std::ifstream infile(filename);
    std::string line;
    std::vector<std::string> tokens;
    std::string token;
    std::vector<std::string> vertex1, vertex2, vertex3;  // face

    int lineNum = 0;

    
    std::cout << "Starting parse..." << std::endl;
    
    //While all your lines are belong to us
    while (std::getline(infile, line))
    {
        //Progress
        if(++lineNum % 10000 == 0)
            std::cout << "At line " << lineNum << std::endl;
        
        //Split a line into tokens by delimiting it on spaces
        //"Er Mah Gerd" becomes ["Er", "Mah", "Gerd"]
        tokens.clear();
        tokens = split(line, ' ', tokens);
        
        //If first token is a v then it gots to be a vertex
        if(tokens.at(0).compare("v") == 0)
        {

            //Parse the vertex line
            float x = std::stof(tokens.at(1));
            float y = std::stof(tokens.at(2));
            float z = std::stof(tokens.at(3));
            
            if (x < minX) {
                minX = x;
            }
            if (x > maxX) {
                maxX = x;
            }
            if (y < minY) {
                minY = y;
            }
            if (y > maxY) {
                maxY = y;
            }
            if (z < minZ) {
                minZ = z;
            }
            if (z > maxZ) {
                maxZ = z;
            }
            
            vertices->push_back(new Vector3(x, y, z));
            
            if (tokens.size() > 4) {
                color = true;
                float r = std::stof(tokens.at(4));
                float g = std::stof(tokens.at(5));
                float b = std::stof(tokens.at(6));
                colors->push_back(new Vector3(1.0, 1.0, 1.0));
            }
            
        }
        else if(tokens.at(0).compare("vn") == 0)
        {
            //Parse the normal line
            float x = std::stof(tokens.at(1));
            float y = std::stof(tokens.at(2));
            float z = std::stof(tokens.at(3));
            
            normals->push_back(new Vector3(x, y, z));
            
        }
        else if(tokens.at(0).compare("f") == 0)
        {
            Face* face = new Face;
            
            //Parse the face line
            
            vertex1.clear();
            vertex2.clear();
            vertex3.clear();
            
            vertex1 = split(tokens.at(1), '/');
            vertex2 = split(tokens.at(2), '/');
            vertex3 = split(tokens.at(3), '/');
            
            face->vertexIndices[0] = std::stof(vertex1.at(0)) - 1;
            face->normalIndices[0] = std::stof(vertex1.at(2)) - 1;
            face->vertexIndices[1] = std::stof(vertex2.at(0)) - 1;
            face->normalIndices[1] = std::stof(vertex2.at(2)) - 1;
            face->vertexIndices[2] = std::stof(vertex3.at(0)) - 1;
            face->normalIndices[2] = std::stof(vertex3.at(2)) - 1;

            faces->push_back(face);
        }
        else if(tokens.at(0).compare("How does I are C++?!?!!") == 0)
        {
            //Parse as appropriate
            //There are more line types than just the above listed
            //See the Wavefront Object format specification for details
        }
        
    }
    
    std::cout << "Done parsing." << std::endl;
    
    getCenter();
    getHalfSize();
    
    for (int i = 0; i < vertices->size(); i++) {
        Vector3* v  = vertices->at(i);
        float x = v->get(0) - centerX;
        float y = v->get(1) - centerY;
        float z = v->get(2) - centerZ;
        *v = Vector3(x,y,z);
    }
}

void OBJObject::getCenter()
{
    centerX = (maxX + minX)/2;
    centerY = (maxY + minY)/2;
    centerZ = (maxZ + minZ)/2;
}

void OBJObject::getHalfSize()
{
    float halfSizeX = (maxX - minX)/2;
    float halfSizeY = (maxY - minY)/2;
    float halfSizeZ = (maxZ - minZ)/2;
    halfSizeMAX = fmax(fmax(halfSizeX, halfSizeY), halfSizeZ);
}

void OBJObject::initTextures()
{
    lavacracks = Texture(LAVACRACKS);
}

//Split functions from the interwebs
//http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string>& OBJObject::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> OBJObject::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
