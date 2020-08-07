//
//  LTimer.hpp
//  SDL_tutorial
//
//  Created by Jack Brooks on 7/6/20.
//  Copyright © 2020 SDL_tutorial. All rights reserved.
//

#ifndef LTimer_hpp
#define LTimer_hpp
#include <stdio.h>
#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
using namespace std;
//The application time based timer
class LTimer
{
    public:
        //Initializes variables
        LTimer();

        //The various clock actions
        void start();
        void stop();
        void pause();
        void unpause();

        //Gets the timer's time
        Uint32 getTicks();

        //Checks the status of the timer
        bool isStarted();
        bool isPaused();

    private:
        //The clock time when the timer started
        Uint32 mStartTicks;

        //The ticks stored when the timer was paused
        Uint32 mPausedTicks;

        //The timer status
        bool mPaused;
        bool mStarted;
};
#endif /* LTimer_hpp */
