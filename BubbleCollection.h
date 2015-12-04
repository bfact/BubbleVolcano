//
//  BubbleCollection.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Sean Wenzel on 12/2/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef BubbleCollection_h
#define BubbleCollection_h

#include <stdio.h>
#include <vector>
#include "Bubble.h"

//class Bubble;

class BubbleCollection {
private:
    //Bubble array[];
    std::vector<Bubble> collection;
public:
    
    BubbleCollection(void);
    void addToCollection(Bubble);
    void drawRandomlyFromCollection();
    void drawEntireCollection();
    void updateEntireCollection();
    void updateCollection();
};

#endif /* BubbleCollection_h */
