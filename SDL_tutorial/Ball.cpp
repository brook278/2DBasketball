//
//  Ball.cpp
//  SDL_tutorial
//
//  Created by Jack Brooks on 7/6/20.
//  Copyright © 2020 SDL_tutorial. All rights reserved.
//

#include "Ball.hpp"
#include "/Users/jack/Desktop/SDL_tutorial/Constants/Constants.h"
#include <iostream>
using namespace std;

Ball::Ball()
{
    
    //Initialize the offsets
    mPosX = constants::BALL_START_X;
    mPosY = constants::BALL_START_Y;
    //Initialize velocity
    mVelocity = constants::VELOCITY;
    //Create the necessary SDL_Rects
    mColliders.resize(11);

    //Initialize the collision boxes' width and height
    mColliders[ 0 ].w = 6;
    mColliders[ 0 ].h = 1;

    mColliders[ 1 ].w = 10;
    mColliders[ 1 ].h = 1;

    mColliders[ 2 ].w = 14;
    mColliders[ 2 ].h = 1;

    mColliders[ 3 ].w = 16;
    mColliders[ 3 ].h = 2;

    mColliders[ 4 ].w = 18;
    mColliders[ 4 ].h = 2;

    mColliders[ 5 ].w = 20;
    mColliders[ 5 ].h = 6;

    mColliders[ 6 ].w = 18;
    mColliders[ 6 ].h = 2;

    mColliders[ 7 ].w = 16;
    mColliders[ 7 ].h = 2;

    mColliders[ 8 ].w = 14;
    mColliders[ 8 ].h = 1;

    mColliders[ 9 ].w = 10;
    mColliders[ 9 ].h = 1;

    mColliders[ 10 ].w = 6;
    mColliders[ 10 ].h = 1;

    //Initialize colliders relative to position
    shiftColliders();
}


std::vector<SDL_Rect>& Ball::getColliders()
{
    return mColliders;
}

void Ball::shiftColliders()
{
    //The row offset
    int r = 0;

    //Go through the balls's collision boxes
    for( int set = 0; set < mColliders.size(); ++set )
    {
        //Center the collision box
        mColliders[ set ].x = mPosX + (BALL_WIDTH - mColliders[ set ].w ) / 2;

        //Set the collision box at its row offset
        mColliders[ set ].y = mPosY + r;

        //Move the row offset down the height of the collision box
        r += mColliders[ set ].h;
    }
}

float Ball::calculateAngle(float x1, float y1, float x2, float y2) {
    float vert_dist = y1 - y2;
    float horiz_dist = x2 - x1;
    float angle = atan(vert_dist / horiz_dist) * (180.0 / M_PI);
    return angle;
}

void Ball::setCoordinates(int x, int y) {
    mPosX = x;
    mPosY = y;
}
vector<int> Ball::getCoordinates() {
    vector<int> coordinates;
    coordinates.push_back(mPosX);
    coordinates.push_back(mPosY);
    return coordinates;
}

void Ball::setPreCoordinates(int x, int y) {
    prePosX = x;
    prePosY = y;
}

vector<int> Ball::getPreCoordinates() {
    vector<int> preCoordinates;
    preCoordinates.push_back(mPosX);
    preCoordinates.push_back(mPosY);
    return preCoordinates;
}

void Ball::setAngle(vector<int> coordinates, bool backboardCollision, string rimCollision) {
    int boundaryX = coordinates[0], boundaryY = coordinates[1];
    float contactAngle = calculateAngle(boundaryX, boundaryY, prePosX, prePosY);
    if (backboardCollision || rimCollision == "outer") {
        if (prePosX > boundaryX) {
            releaseAngle = 225.0;
        }
        else {
            releaseAngle = 180 - contactAngle;
        }
    }
    else if (rimCollision == "bottom") {
        if (prePosY < boundaryY) {
            releaseAngle = 270.0;
        }
        else if (prePosX > boundaryX) {
            releaseAngle = 180 + (contactAngle * (-1));
        }
        else {
            releaseAngle = contactAngle * (-1);
        }
    }
    else if (rimCollision == "top") {
        cout << "angle before collision: " << calculateAngle(boundaryX, boundaryY, prePosX, prePosY) << endl;
        if (prePosX > boundaryX) {
            releaseAngle = 180 - contactAngle;
        }
        else {
            releaseAngle = contactAngle * (-1);
        }
    }
    else if (rimCollision == "inner") {
        if (prePosX < boundaryX) {
            releaseAngle = -45.0;
        }
        else {
            releaseAngle = contactAngle * (-1);
        }
    }
    //Player is shooting ball
    else {
        releaseAngle = calculateAngle(constants::SPACE_BEHIND_SHOOTER, constants::BALL_START_Y, boundaryX, boundaryY);
        releaseAngle = RandomFloat(releaseAngle - 2.0, releaseAngle + 2.0);
    }
    if (backboardCollision) {
        cout << "BACKBOARD COLLISION!!" << endl;
    }
    if (rimCollision != "") {
        cout << rimCollision << " RIM COLLISION" << endl;
    }
    cout << "Angle after collision: " << releaseAngle << endl;
}

void Ball::release(float time, vector<int> coordinates)
{
    vector<int> f_coordinates = calculateReleasePosition(time, coordinates);
    mPosX = f_coordinates[0];
    mPosY = f_coordinates[1];
    shiftColliders();
}

void Ball::shoot(float angle) {
    const int forearm_length = constants::FOREARM_LENGTH;
    const int upper_arm_length = constants::UPPER_ARM_LENGTH;
    int x = forearm_length*1.1;
    int y = upper_arm_length;
    float x_val = x*cos((angle*M_PI)/180.0) - y*sin((angle*M_PI)/180.0) + (constants::BALL_START_X - forearm_length);
    float y_val = y*cos((angle*M_PI)/180.0) + x*sin((angle*M_PI)/180.0) + (constants::BALL_START_Y - upper_arm_length);
    vector<int> coordinates{int(x_val), int(y_val)};
    mPosX = coordinates[0];
    mPosY = coordinates[1];

}


float Ball::RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void Ball::setVelocity(float vel) {
    mVelocity = vel;
}

float Ball::getVelocity() {
    return mVelocity;
}

vector<int> Ball::calculateReleasePosition(float time, vector<int> coordinates) {
    const float grav = constants::GRAVITY;
    int boundaryX = coordinates[0], boundaryY = coordinates[1];
    float x_vel = cos((releaseAngle*M_PI)/180.0) * mVelocity;
    float y_vel = sin((releaseAngle*M_PI)/180.0) * mVelocity;
    float y_val = boundaryY - ( ((grav)*(pow(time, 2))) + y_vel*time);
    float x_val = boundaryX + (x_vel * time);
    vector<int> f_coordinates{int(x_val), int(y_val)};
    return f_coordinates;
}

void Ball::drawTrajectory() {
    auto temp_angle = releaseAngle;
    releaseAngle = 45.0;
    vector<int> coordinates{129, 653};
    float time = 0;
    while (true) {
        auto f_coordinates = calculateReleasePosition(time, coordinates);
        //cout << "X: " << f_coordinates[0] << ", Y: " << f_coordinates[1] << "\n";
        SDL_RenderDrawLine(constants::gRenderer, f_coordinates[0], f_coordinates[1], f_coordinates[0] + 10, f_coordinates[1]);
        //SDL_RenderDrawPoint(constants::gRenderer, f_coordinates[0], f_coordinates[1]);
        if (f_coordinates[1] > constants::SCREEN_HEIGHT) {
            break;
        }
        time += 0.5;
    }
    releaseAngle = temp_angle;
}

void Ball::setReleasePoint(int relX, int relY) {
    releasePosX = relX;
    releasePosY = relY;
}

vector<int> Ball::getReleasePoint() {
    return vector<int>{releasePosX, releasePosY};
}
