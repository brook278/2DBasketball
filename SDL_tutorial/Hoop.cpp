//
//  Hoop.cpp
//  SDL_tutorial
//
//  Created by Jack Brooks on 7/1/20.
//  Copyright © 2020 SDL_tutorial. All rights reserved.
//

#include "Hoop.hpp"
#include "/Users/jack/Desktop/SDL_tutorial/Constants/Constants.h"

Hoop::Hoop() {
    mAboveColliders.resize( 1 );
    mBelowColliders.resize( 1 );
    //Initialize the collision boxes' width and height
    mAboveColliders[ 0 ].x = mBelowColliders[0].x = constants::RIM_BEGIN;
    mAboveColliders[ 0 ].y = constants::SCREEN_HEIGHT - constants::RIM_HEIGHT - (constants::BALL_DIAMETER*3);
    mBelowColliders[ 0 ].y = constants::SCREEN_HEIGHT - constants::RIM_HEIGHT;
    mAboveColliders[ 0 ].w = mBelowColliders[ 0 ].w = constants::RIM_WIDTH;
    mAboveColliders[ 0 ].h = constants::BALL_DIAMETER * 3;
    mBelowColliders[ 0 ].h = constants::BALL_DIAMETER;
}

void Hoop::render(SDL_Renderer* gRenderer, const int x1, const int y1, const int x2, const int y2) {
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
    SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
}

string Hoop::checkCollision( std::vector<SDL_Rect>& inner, std::vector<SDL_Rect>& outer )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    auto index = (inner.size() - 1) / 2;
    //Calculate the sides of rect A
    leftA = inner[ index ].x;
    rightA = inner[ index ].x + inner[ index ].w;
    topA = inner[ index ].y;
    bottomA = inner[ index ].y + inner[ index ].h;
    //Calculate the sides of rect B
    leftB = outer[ 0 ].x;
    rightB = outer[ 0 ].x + outer[ 0 ].w;
    topB = outer[ 0 ].y;
    bottomB = outer[ 0 ].y + outer[ 0 ].h;
    if (leftA >= leftB) {
        /*
        cout << "Left A: " << leftA << ", Right A: " << rightA << ", Top A: " << topA << ", Bottom A: " << bottomA << endl;
        cout << "Left B: " << leftB << ", Right B: " << rightB << ", Top B: " << topB << ", Bottom B: " << bottomB << endl;
         */
    }
    if (leftA >= leftB && rightA <= rightB && topA >= topB && bottomA <= bottomB) {
        return "true";
    }
    return "";
}

std::vector<SDL_Rect>& Hoop::getAboveColliders() {
    return mAboveColliders;
}

std::vector<SDL_Rect>& Hoop::getBelowColliders() {
    return mBelowColliders;
}
