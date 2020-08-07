/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "Rim.cpp"
#include "Hoop.cpp"
#include "Ball.cpp"
#include "LTexture.hpp"
#include "../Constants/Constants.h"

using namespace std;

const int SCREEN_WIDTH = constants::SCREEN_WIDTH;
const int SCREEN_HEIGHT = constants::SCREEN_HEIGHT;

//Dimensions of landscape
const int HOOP_HEIGHT = constants::HOOP_HEIGHT;
const int SHOT_DISTANCE = constants::SHOT_DISTANCE;
const int SPACE_BEHIND_SHOOTER = constants::SPACE_BEHIND_SHOOTER;
const int RIM_HEIGHT = constants::RIM_HEIGHT;
const int RIM_BEGIN = constants::RIM_BEGIN;
const int RIM_END = constants::RIM_END;
const int BALL_START_X = constants::BALL_START_X;
const int BALL_START_Y = constants::BALL_START_Y;
const float VELOCITY = constants::VELOCITY;
const float BALL_DIAMETER = constants::BALL_DIAMETER;
const int FOREARM_LENGTH = constants::FOREARM_LENGTH;
const int UPPER_ARM_LENGTH = constants::UPPER_ARM_LENGTH;
const int ARM_THICKNESS = constants::ARM_THICKNESS;

//Scene textures
LTexture gBallTexture;
LTexture gUpperarmTexture;
LTexture gForearmTexture;
LTexture gSupportArmTexture;
LTexture gMainScreen;
LTexture gMultiplayerScreen;
SDL_Renderer* &gRenderer = constants::gRenderer;
SDL_Window* &gWindow = constants::gWindow;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    
        if(gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMainScreen() {
    //Loading success flag
    bool success = true;
    if( !gMainScreen.loadFromFile("/Users/jack/Desktop/SDL_tutorial/Images/mainscreen.png")) {
        printf( "Failed to load main screen!\n" );
        success = false;
    }
    return success;
}
bool loadMedia()
{
    //Loading success flag
    bool success = true;
    //Load ball texture
    gBallTexture.setWidth(constants::BALL_DIAMETER);
    gBallTexture.setHeight(constants::BALL_DIAMETER);
    if( !gBallTexture.loadFromFile("/Users/jack/Desktop/SDL_tutorial/Images/basketball.png") )
    {
        printf( "Failed to load ball texture!\n" );
        success = false;
    }
    gUpperarmTexture.setWidth(constants::UPPER_ARM_LENGTH);
    gUpperarmTexture.setHeight(constants::ARM_THICKNESS);
    if( !gUpperarmTexture.loadFromFile("/Users/jack/Desktop/SDL_tutorial/Images/arm.png") )
    {
        printf( "Failed to load upper arm texture!\n" );
        success = false;
    }
   gForearmTexture.setWidth(constants::FOREARM_LENGTH);
   gForearmTexture.setHeight(constants::ARM_THICKNESS);
    if( !gForearmTexture.loadFromFile("/Users/jack/Desktop/SDL_tutorial/Images/arm.png") )
    {
        printf( "Failed to load forearm texture!\n" );
        success = false;
    }
    gSupportArmTexture.setWidth(constants::SUPPORT_ARM_LENGTH);
    gSupportArmTexture.setHeight(constants::ARM_THICKNESS);
    if( !gSupportArmTexture.loadFromFile("/Users/jack/Desktop/SDL_tutorial/Images/arm.png") )
    {
        printf( "Failed to load forearm texture!\n" );
        success = false;
    }
    return success;
}

void close()
{
    //Free loaded images
    gBallTexture.free();
    gUpperarmTexture.free();
    gForearmTexture.free();
    gSupportArmTexture.free();
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void render(Hoop hoop, Rim rim, Ball ball, float armRotation, float ballRotation, bool released, int count) {
    //Clear screen
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );
    //Draw hoop
    hoop.render( gRenderer, SPACE_BEHIND_SHOOTER + SHOT_DISTANCE, SCREEN_HEIGHT - HOOP_HEIGHT, SPACE_BEHIND_SHOOTER + SHOT_DISTANCE, SCREEN_HEIGHT);
    //Draw rim
    rim.render( gRenderer, RIM_BEGIN, SCREEN_HEIGHT - RIM_HEIGHT, RIM_END, SCREEN_HEIGHT - RIM_HEIGHT);
    //Establish point to rotate around
    SDL_Point center_rot;
    SDL_Point* rot_ptr;
    rot_ptr = &center_rot;
    static_cast<void>(center_rot.x = 0), center_rot.y = BALL_DIAMETER/4;
    gUpperarmTexture.render(BALL_START_X-FOREARM_LENGTH - ARM_THICKNESS + BALL_DIAMETER/2, BALL_START_Y - UPPER_ARM_LENGTH, NULL, armRotation+90, rot_ptr);
    auto ballPosX = ball.getCoordinates()[0], ballPosY = ball.getCoordinates()[1];
    //Change rotation point
    if (released) {
        static_cast<void>(center_rot.x = 0), center_rot.y = 0;
        const int forearm_length = constants::FOREARM_LENGTH;
        const int upper_arm_length = constants::UPPER_ARM_LENGTH;
        int x = 0;
        int y = upper_arm_length;
        float x_val = x*cos((armRotation*M_PI)/180.0) - y*sin((armRotation*M_PI)/180.0) + (constants::BALL_START_X - forearm_length*.95);
        float y_val = y*cos((armRotation*M_PI)/180.0) + x*sin((armRotation*M_PI)/180.0) + (constants::BALL_START_Y - upper_arm_length);
        gForearmTexture.render(x_val, y_val, NULL, armRotation + count*13, rot_ptr);
        //Draw supporting arm
        gSupportArmTexture.render(BALL_START_X-FOREARM_LENGTH - ARM_THICKNESS + BALL_DIAMETER/2, BALL_START_Y - UPPER_ARM_LENGTH, NULL, 35 + armRotation + count, rot_ptr);
    }
    else {
        static_cast<void>(center_rot.x = 0), center_rot.y = (-1) * UPPER_ARM_LENGTH;
        gForearmTexture.render(BALL_START_X-FOREARM_LENGTH, BALL_START_Y+BALL_DIAMETER/4, NULL, armRotation, rot_ptr);
        //Draw supporting arm
        static_cast<void>(center_rot.x = 0), center_rot.y = 0;
        gSupportArmTexture.render(BALL_START_X-FOREARM_LENGTH - ARM_THICKNESS + BALL_DIAMETER/2, BALL_START_Y - UPPER_ARM_LENGTH, NULL, 35 + armRotation, rot_ptr);
    }
    gBallTexture.render(ballPosX, ballPosY, NULL, ballRotation);
    ball.drawTrajectory();
    //Update screen
    SDL_RenderPresent( gRenderer );
}
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int sockfd, newsockfd, portno = 2001;
socklen_t clilen;
struct sockaddr_in serv_addr, cli_addr;
int n;
struct hostent *server;
bool is_server = false;
char buffer[256];
bool my_turn = false;

void server_init() {
    is_server = true;
    my_turn = true;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
       error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (::bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
             error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,
                (struct sockaddr *) &cli_addr,
                &clilen);
    if (newsockfd < 0)
         error("ERROR on accept");
}

void client_init() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    printf("Client is connected\n");
    printf("%s\n",buffer);
}

string compressInfo(Ball ball, int armRotation, int ballRotation, bool released, int count) {
    ostringstream ss;
    ss << ball.getCoordinates()[0] << " " << ball.getCoordinates()[1] << " " << armRotation << " " << ballRotation << " " << released << " " << count;
    std::string s(ss.str());
    
    return s;
}

void unpackInfo(char info[], Ball &ball, int &armRotation, int &ballRotation, bool &released, int &count) {
    vector<string> ballCoordinates;
    string coordinate = strtok(info, " ");
    ballCoordinates.push_back(coordinate);
    coordinate = strtok(NULL, " ");
    ballCoordinates.push_back(coordinate);
    ball.setCoordinates(stoi(ballCoordinates[0]), stoi(ballCoordinates[1]));
    armRotation = stoi(strtok(NULL, " "));
    ballRotation = stoi(strtok(NULL, " "));
    released = strtok(NULL, " ");
    count = stoi(strtok(NULL, " "));
}

unsigned long int getNofTokens(const char* str){
    int count =0,i;
    for(i=0;i<strlen(str);i++){
        if(str[i] == ' ')
            count++;
    }
    return count;
}

int main(int argc, char *argv[])
{
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    if (strstr(buffer, "0")) {
        server_init();
    }
    else if (strstr(buffer, "1")) {
        client_init();
    }
    bzero(buffer, 256);
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia())
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;
            
            //Event handler
            SDL_Event e;
            //The ball that will be moving around on the screen
            Ball ball;
            Rim rim;
            Hoop hoop;
            auto *keystates = SDL_GetKeyboardState( NULL );
            float offset = 0.000;
            int count = 0;
            bool pressed = false;
            bool released = false;
            bool backboardCollision = false;
            string rimCollision = "";
            string rimAffected = "";
            bool end = false;
            bool above = false;
            int armRotation = 0;
            int ballRotation = 0;
            //While application is running
            while( !quit )
            {
                if (end == true) {
                    SDL_Delay(200);
                    end = false;
                }
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    if (my_turn) {
                        if (keystates[SDL_SCANCODE_UP] && !released) {
                            ball.setVelocity(ball.getVelocity()+1);
                        }
                        if (keystates[SDL_SCANCODE_SPACE] && !pressed) {
                            pressed = true;
                            offset = (SDL_GetTicks()/ 1000.0f);
                        }
                        if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_SPACE && !released) {
                            released = true;
                            offset = (SDL_GetTicks()/ 1000.0f);
                            ball.setReleasePoint(ball.getCoordinates()[0], ball.getCoordinates()[1]);
                            ball.setAngle(ball.getReleasePoint(), backboardCollision, rimCollision);
                        }
                    }
                }
    
                float time = ((SDL_GetTicks()/ 1000.0f)) - offset;
                if (my_turn) {
                    float ballVelocity = ball.getVelocity();
                    //Shoot ball
                    if (keystates[SDL_SCANCODE_SPACE] && released == false) {
                        armRotation -= 5;
                        ball.shoot(armRotation);
                    }
                    //Release ball
                    else if (pressed == true) {
                        ballRotation -= 10;
                        ball.release(time*4.5, ball.getReleasePoint());
                    }
                    //Position of ball
                    int ballPosX = ball.getCoordinates()[0], ballPosY = ball.getCoordinates()[1];
                    rimCollision = rim.checkCollision(ball.getColliders(), rim.getColliders());
                    if (rimCollision != "" && rimAffected == "") {
                        rimAffected = rimCollision;
                        ball.setVelocity(ballVelocity*0.4 );
                        ball.setReleasePoint(ballPosX, ballPosY);
                        offset = (SDL_GetTicks()/ 1000.0f);
                        backboardCollision = false;
                        ball.setAngle(ball.getReleasePoint(), backboardCollision, rimCollision);
                    }
                    
                    //Ball's X distance from the hoop
                    int ballDistFromHoop = SPACE_BEHIND_SHOOTER + SHOT_DISTANCE - ballPosX;
                    //Check if ball has made contact with hoop
                    if (ballDistFromHoop <= BALL_DIAMETER && !backboardCollision) {
                        //Change starting coordinates of ball's resulting trajectory
                        ball.setReleasePoint(ballPosX, ballPosY);
                        offset = (SDL_GetTicks()/ 1000.0f);
                        backboardCollision = true;
                        ball.setAngle(ball.getReleasePoint(), backboardCollision, rimCollision);
                        rimAffected = "";
                        //Check if ball hit backboard
                        if (ballPosY < SCREEN_HEIGHT - RIM_HEIGHT) {
                            ball.setVelocity(ballVelocity*0.5);
                        }
                        else {
                            ball.setVelocity(ballVelocity*0.75);
                        }
                    }
                    //Calculate angle from position of ball before collision
                    else if (ball.getReleasePoint().size() == 0 || (!(ballPosX == ball.getReleasePoint()[0] && ballPosY == ball.getReleasePoint()[1]))) {
                        ball.setPreCoordinates(ballPosX, ballPosY);
                    }
                    if (released && count <= 6) {
                        armRotation -= 1;
                        ++ count;
                    }
                    if (hoop.checkCollision(ball.getColliders(), hoop.getAboveColliders()) != "") {
                        above = true;
                    }
                    
                    if (hoop.checkCollision(ball.getColliders(), hoop.getBelowColliders()) != "" && above == true) {
                        cout << "SCOOOOORE" << endl;
                    }
                    string status = compressInfo(ball, armRotation, ballRotation, released, count);
                    //Reset ball to starting position
                    if (ballPosY >= SCREEN_HEIGHT) {
                        pressed = false;
                        released = false;
                        above = false;
                        end = true;
                        backboardCollision = false;
                        rimAffected = "";
                        armRotation = 0;
                        ball = Ball();
                        status = "finished";
                        cout << "\n\n\n" << endl;
                        my_turn = false;
                        count = 0;
                    }
                    if (is_server) {
                        write(newsockfd, status.c_str(), 100);
                    }
                    else {
                        write(sockfd, status.c_str(), 100);
                    }
                }
                else {
                    bzero(buffer,256);
                    ssize_t n;
                    if (is_server) {
                        n = read(newsockfd,buffer,255);
                    }
                    else {
                        n = read(sockfd, buffer, 255);
                    }
                    if (n < 0)
                         error("ERROR reading from socket");
                    printf("%s\n",buffer);
                    if (strstr(buffer, "fini")) {
                        my_turn = true;
                        ball = Ball();
                        armRotation = 0;
                        ballRotation = 0;
                        released = false;
                        count = 0;
                        continue;
                    }
                    if (getNofTokens(buffer) == 5) {
                        unpackInfo(buffer, ball, armRotation, ballRotation, released, count);
                    }
                }
                
                render(hoop, rim, ball, armRotation, ballRotation, released, count);
            }
        }
    }
    close(newsockfd);
    close(sockfd);
    //Free resources and close SDL
    close();
    return 0;
}

