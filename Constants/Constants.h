//
//  Constants.h
//  SDL_tutorial
//
//  Created by Jack Brooks on 7/6/20.
//  Copyright © 2020 SDL_tutorial. All rights reserved.
//

#ifndef Constants_h
#define Constants_h
#include "SDL.h"
namespace constants
{
    //The window we'll be rendering to
    inline extern SDL_Window* gWindow = NULL;

    //The window renderer
    inline extern SDL_Renderer* gRenderer = NULL;

    //Screen dimension constants
    inline extern const int SCREEN_WIDTH = 800;
    inline extern const int SCREEN_HEIGHT = 800;

    //Dimensions of landscape
    inline extern const int HOOP_HEIGHT = SCREEN_HEIGHT * .4;
    inline extern const int SHOT_DISTANCE = HOOP_HEIGHT * 0.8;
    inline extern const int SPACE_BEHIND_SHOOTER = HOOP_HEIGHT * .23;
    inline extern const int RIM_HEIGHT = HOOP_HEIGHT * .77;
    inline extern const int RIM_WIDTH = HOOP_HEIGHT * .13;
    inline extern const int RIM_THICKNESS = RIM_WIDTH*.09;
    inline extern const int RIM_BEGIN = SPACE_BEHIND_SHOOTER + SHOT_DISTANCE - RIM_WIDTH;
    inline extern const int RIM_END = SPACE_BEHIND_SHOOTER + SHOT_DISTANCE;
    inline extern const int BALL_START_X = SPACE_BEHIND_SHOOTER + HOOP_HEIGHT*.17;
    inline extern const int BALL_START_Y = SCREEN_HEIGHT - (HOOP_HEIGHT * .27);
    inline extern const float VELOCITY = SHOT_DISTANCE * .55;
    inline extern const float GRAVITY = pow(HOOP_HEIGHT * 2.47, 0.5)*(-1);
    inline extern const float BALL_DIAMETER = HOOP_HEIGHT*.06;
    inline extern const int FOREARM_LENGTH = HOOP_HEIGHT * .15;
    inline extern const int UPPER_ARM_LENGTH = HOOP_HEIGHT * .09;
    inline extern const int SUPPORT_ARM_LENGTH = sqrt(pow(UPPER_ARM_LENGTH, 2) + pow(FOREARM_LENGTH, 2));
    inline extern const int ARM_THICKNESS = HOOP_HEIGHT * .02;
    inline extern const int HAND_LENGTH = HOOP_HEIGHT * .05;
}

#endif /* Constants_h */
