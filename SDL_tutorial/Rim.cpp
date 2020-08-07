//
//  Rim.cpp
//  SDL_tutorial
//
//  Created by Jack Brooks on 6/10/20.
//  Copyright © 2020 SDL_tutorial. All rights reserved.
//

#include "Rim.hpp"
#include "/Users/jack/Desktop/SDL_tutorial/Constants/Constants.h"

Rim::Rim() {
     mColliders.resize( 1 );
    //Initialize the collision boxes' width and height
     mColliders[ 0 ].x = constants::RIM_BEGIN;
     mColliders[ 0 ].y = constants::SCREEN_HEIGHT - constants::RIM_HEIGHT;
     mColliders[ 0 ].w = constants::RIM_THICKNESS;
     mColliders[ 0 ].h = constants::RIM_THICKNESS;
}

std::vector<SDL_Rect>& Rim::getColliders() {
    return mColliders;
}

void Rim::render(SDL_Renderer* gRenderer, const int x1, const int y1, const int x2, const int y2) {
    SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
}

string Rim::checkCollision( std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Go through the A boxes
    for( int Abox = 0; Abox < a.size(); Abox++ )
    {
        //Calculate the sides of rect A
        leftA = a[ Abox ].x;
        rightA = a[ Abox ].x + a[ Abox ].w;
        topA = a[ Abox ].y;
        bottomA = a[ Abox ].y + a[ Abox ].h;
        //Go through the B boxes
        for( int Bbox = 0; Bbox < b.size(); Bbox++ )
        {
            //Calculate the sides of rect B
            leftB = b[ Bbox ].x;
            rightB = b[ Bbox ].x + b[ Bbox ].w;
            topB = b[ Bbox ].y;
            bottomB = b[ Bbox ].y + b[ Bbox ].h;
            //If no sides from A are outside of B
            if( ( ( bottomA <= topB ) || ( topA >= bottomB ) || ( rightA <= leftB ) || ( leftA >= rightB ) ) == false )
            {
                //A collision is detected
                //If ball hits top of rim

                if (Abox >= 7) {
                    return "top";
                }
                //If ball hits bottom of rim
                else if (Abox <= 2) {
                    return "bottom";
                }
                //If ball hits inner rim
                else if (leftA >= leftB) {
                    return "inner";
                }
                //If ball hits outer rim
                else {
                    return "outer";
                }
            }
        }
    }
    //If neither set of collision boxes touched
    return "";
}
