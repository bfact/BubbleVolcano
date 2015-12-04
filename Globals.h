#ifndef CSE167_Globals_h
#define CSE167_Globals_h

#include "Camera.h"
#include "Cube.h"
#include "Sphere.h"
#include "Light.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "House.h"
#include "Texture.h"
#include "OBJObject.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Texture.h"
#include "BezierPatch.h"
#include "BubbleCollection.h"
#include "Bubble.h"
#include "HeightMap.h"

class Globals
{
    
public:
    
    static Camera camera;
    static Cube cube;
    static Sphere sphere;
    static Light light;
    static DrawData drawData;
    static UpdateData updateData;
    //Feel free to add more member variables as needed
    
    //Objects
    static House house;
    static Drawable *objdraw;

    static OBJObject volcano;

    //Lights
    static DirectionalLight directionlight;
    static PointLight pointlight;
    static SpotLight spotlight;
    
    static std::vector<Texture> textures;
    static BubbleCollection bubbles;
    
    static HeightMap map;

};

#endif
