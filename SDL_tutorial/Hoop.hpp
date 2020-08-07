//
//  Hoop.hpp
//  SDL_tutorial
//
//  Created by Jack Brooks on 7/1/20.
//  Copyright © 2020 SDL_tutorial. All rights reserved.
//

#ifndef Hoop_hpp
#define Hoop_hpp

#include<vector>
#include <stdio.h>
#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
using namespace std;

class Hoop {
    public:
        //Render hoop
        void render(SDL_Renderer* gRender, const int x1, const int y1, const int x2, const int y2);
        //Gets the collision boxes for ball above rim
        std::vector<SDL_Rect>& getAboveColliders();
        //Gets the collision boxes for ball below rim
        std::vector<SDL_Rect>& getBelowColliders();
        //Check collision between ball and hoop's target zones
        string checkCollision( std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b );
        //Initialize rim
        Hoop();
    private:
        //Hoop's goal collision boxes for ball above rim
        std::vector<SDL_Rect> mAboveColliders;
        //Hoop's goal collision boxes for ball below rim
        std::vector<SDL_Rect> mBelowColliders;
};

#endif /* Hoop_hpp */
