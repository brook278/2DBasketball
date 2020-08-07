//
//  Ball.hpp
//  SDL_tutorial
//
//  Created by Jack Brooks on 7/6/20.
//  Copyright © 2020 SDL_tutorial. All rights reserved.
//

#ifndef Ball_hpp
#define Ball_hpp
#include "/Users/jack/Desktop/SDL_tutorial/Constants/Constants.h"
using namespace std;

class Ball
{
    public:
        //The dimensions of the ball
        static const int BALL_WIDTH = constants::BALL_DIAMETER;
        static const int BALL_HEIGHT = constants::BALL_DIAMETER;

        //Initializes the variables
        Ball();
        
        //Calculate release position of ball
        vector<int> calculateReleasePosition(float time, vector<int> coordinates);
    
        //Moves ball as player shoots
        void shoot(float angle);
    
        //Moves ball after player releases
        void release(float time, vector<int> coordinates);
    
        //Set coordinates of ball
        void setCoordinates(int x, int y);
        //Get coordinates of ball
        vector<int> getCoordinates();
    
        //Calculate angle of ball in relation to point
        float calculateAngle(float x1, float y1, float x2, float y2);
        
        //Set release angle of ball
        void setAngle(vector<int> coordinates, bool backboardCollision, string rimCollision);
    
        //Set coordinates of ball
        void setPreCoordinates(int x, int y);
        //Get coordinates of ball before collision
        vector<int> getPreCoordinates();
        
        //Gets the collision boxes
        std::vector<SDL_Rect>& getColliders();
    
        //Get random float between two floats
        float RandomFloat(float a, float b);
    
        //Set ball's velocity
        void setVelocity(float vel);
        //Get ball's velocity
        float getVelocity();
    
        //Set ball's release point
        void setReleasePoint(int x, int y);
        //Get ball's release point
        vector<int> getReleasePoint();
    
        //Draw ball's trajectory
        void drawTrajectory();
    
    private:
    
        //Ball's point at release
        int releasePosX, releasePosY;
        //The X and Y offsets of the ball
        int mPosX, mPosY;
        //The X and Y offsets of the ball just before collision
        int prePosX, prePosY;
        //Release angle of ball
        float releaseAngle;
        //Ball's collision boxes
        std::vector<SDL_Rect> mColliders;
        //Moves the collision boxes relative to the ball's offset
        void shiftColliders();
        //Ball's velocity
        float mVelocity;
};
#endif /* Ball_hpp */
