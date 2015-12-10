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
//lava texture
#define LAVACRACKS "/Users/BrittanyFactura/GitHub/bubblevolcano/lavacracks.ppm"
//bloom effect
#define VERTEX "/Users/BrittanyFactura/GitHub/bubblevolcano/glow.vert"
#define BLOOMFRAGMENT "/Users/BrittanyFactura/GitHub/bubblevolcano/bloom.frag"
//#define BLURFRAGMENT "/Users/BrittanyFactura/GitHub/bubblevolcano/blur.frag"
#define BLENDFRAGMENT "/Users/BrittanyFactura/GitHub/bubblevolcano/blend.frag"
//bump mapping
#define BUMPVERTEX "/Users/BrittanyFactura/GitHub/bubblevolcano/bumpmap.vert"
#define BUMPFRAGMENT "/Users/BrittanyFactura/GitHub/bubblevolcano/bumpmap.frag"

#define LAVACRACKS_SEAN "/Users/seanwenzel/Github/bubblevolcano/lavacracks.ppm"
#define VERTEX_SEAN "/Users/seanwenzel/Github/bubblevolcano/glow.vert"
#define FRAGMENT_SEAN "/Users/seanwenzel/Github/bubblevolcano/bloom.frag"

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

void OBJObject::initTextures()
{
    //    lavacracks = Texture(LAVACRACKS_SEAN);
    lavacracks = Texture(LAVACRACKS);
}


void OBJObject::draw(DrawData& data)
{
    toWorld.setYDisplacement(Globals::volcanoHeightDisplacement);
    
    Face* face;
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());

    glActiveTexture(GL_TEXTURE0);
    lavacracks.bind();
    //bumpmap->bind();
    
    
    // Brittany's Version
    Shader* bloom = new Shader(VERTEX, BLOOMFRAGMENT);
//    Shader* blur  = new Shader(VERTEX, BLURFRAGMENT);
    Shader* blend = new Shader(VERTEX, BLENDFRAGMENT);
    
    
    Shader* bumpmap = new Shader(BUMPVERTEX, BUMPFRAGMENT);
    
    /*
    
    // Sean's Version
    
     Shader* bloom = new Shader(VERTEX_SEAN, FRAGMENT_SEAN);
     Shader* blur  = new Shader(VERTEX_SEAN, FRAGMENT_SEAN);
     Shader* blend = new Shader(VERTEX_SEAN, FRAGMENT_SEAN);
     */
    
    //bumpmap->bind();
    
    if (Window::lavaShader) {
        bloom->bind();
        //blend->bind();
    }
    
    // to have your lava sampler get the lava texture, you need to do:
    GLhandleARB programHandle = bloom->getPid();
    GLint lavaSamplerHandler = glGetUniformLocationARB(programHandle, "lavacracks");
    glUniform1i(lavaSamplerHandler, 0);
    
    //printf("Lavacracks texture id %u \n", lavacracks.id);


    glBegin(GL_TRIANGLES);
    
    for (int i = 0; i < faces->size(); i++) {
        face = faces->at(i);
        for (int j = 0; j < 3; j++) {
            Vector3 vn = *normals->at(face->normalIndices[j]);
            vn = vn.normalize();
            glNormal3f(vn[0], vn[1], vn[2]);
            
            if (color) {
                Vector3 c = *colors->at(face->vertexIndices[j]);
                //glColor4f(c[0], c[1], c[2], 0.5);
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
    
    if (Window::lavaShader) {
        bloom->unbind();
        //blur->unbind();
        //blend->unbind();
    }
    
    lavacracks.unbind();
    //bumpmap->unbind();
    
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
