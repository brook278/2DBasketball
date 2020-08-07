//
//  LTexture.hpp
//  SDL_tutorial
//
//  Created by Jack Brooks on 7/6/20.
//  Copyright © 2020 SDL_tutorial. All rights reserved.
//

#ifndef LTexture_hpp
#define LTexture_hpp

#include <stdio.h>
#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
#include <string>
using namespace std;

//Texture wrapper class
class LTexture
{
    public:
        //Initializes variables
        LTexture();

        //Deallocates memory
        ~LTexture();

        //Loads image at specified path
        bool loadFromFile(string path);

        //Deallocates texture
        void free();

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void setAlpha( Uint8 alpha );
        
        //Renders texture at given point
        void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

        //Sets size dimensions
        void setWidth(int width);
        void setHeight(int height);

    private:
        //The actual hardware texture
        SDL_Texture* mTexture;
        //Image dimensions
        int mWidth;
        int mHeight;
};
#endif /* LTexture_hpp */
