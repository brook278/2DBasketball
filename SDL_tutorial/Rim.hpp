//
//  Rim.hpp
//  SDL_tutorial
//
//  Created by Jack Brooks on 6/10/20.
//  Copyright © 2020 SDL_tutorial. All rights reserved.
//

#ifndef Rim_hpp
#define Rim_hpp
#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
#include<vector>
#include <stdio.h>

using namespace std;
class Rim {
    public:
        //Gets the collision boxes
        std::vector<SDL_Rect>& getColliders();
        //Render rim
        void render(SDL_Renderer* gRender, const int x1, const int y1, const int x2, const int y2);
        //Check collision between ball and rim
        string checkCollision( std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b );
        //Initialize rim
        Rim();
    private:
        //Rim's collision boxes
        std::vector<SDL_Rect> mColliders;
};

#endif /* Rim_hpp */
