//
//  BubbleCollection.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Sean Wenzel on 12/2/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "BubbleCollection.h"

// Initialize collection with 50 random elements
BubbleCollection::BubbleCollection() {
    for (int i = 0; i < 50; i++) {
        collection.push_back(Bubble());
    }
}

void BubbleCollection::drawRandomlyFromCollection() {
    if (collection.size() == 0) {
        std::cerr << "Error: size of collection is 0" << std::endl;
        return;
    }
    
    // Use random number to select bubble from collection
    Bubble selection = collection.at( ((int)rand()) % collection.size() );
    
    // Draw Selection
    selection.draw();
}

void BubbleCollection::drawEntireCollection() {
    for (int i = 0; i < collection.size(); i++) {
        collection.at(i).draw();
    }
}

void BubbleCollection::updateEntireCollection() {
    for (int i = 0; i < collection.size(); i++) {
        collection.at(i).update();
    }
}

/*
void BubbleCollection::addToCollection(Bubble bubble) {
    collection.push_back(bubble);
} */

void BubbleCollection::updateCollection() {
    // Cull Bubbles
    
    // Remove from Collection after some criteria is met
}