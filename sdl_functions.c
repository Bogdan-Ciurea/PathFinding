/************************************************************************
    University of Leeds
    School of Computing
    COMP1921 - Programming project
    Coursework 2
    File: SDLFunctions.c
    Student Name: Bogdan Alexandru Ciurea
    Student ID: 201438333
    Email: sc20bac@leeds.ac.uk
    Date Work Commenced: 3rd Mar 2021
*************************************************************************/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

//These distances are taken from the image that we where given
//They can be changed by changing the value of the scaler
float scaler = 1.5;
extern int width;
int mapWidth;
extern int height;
int mapHeight;
int distToBoxWidth;
int distToBoxHeight;
int distFromBoxWidth;
int distFromBoxHeight;
int smallLine;
int distBetweenLinesBot;
int distBetweenLinesLeft;
int boxWidth;
int boxHeight;

// The purpose of this function is to initialize the sizes of the lines, boxes etc to build the frame
void initValues(){
    width = 640 * scaler;
    mapWidth = 421 * scaler;
    height = 480 * scaler;
    mapHeight = 358 * scaler;
    distToBoxWidth = 107 * scaler;
    distToBoxHeight = 24 * scaler;
    distFromBoxWidth = 20 * scaler;
    distFromBoxHeight = 40 * scaler;
    smallLine = 5 * scaler;
    distBetweenLinesBot = mapWidth/4;
    distBetweenLinesLeft = mapHeight/9;
    boxWidth = 500 * scaler;
    boxHeight = 420 * scaler;
}

extern double maxLat, maxLon, minLat, minLon;
extern Nodes pathOfNodes;

// The purpose of this function is to draw a small star around a node
// The third parameter will be an SDL_Renderer pointer
// The first and second parameters will be the x and y coordinates of the node
void drawPoint(int x, int y, SDL_Renderer *renderer){
    SDL_RenderDrawPoint(renderer, x, y);

    //Make the box
    SDL_RenderDrawPoint(renderer, x, y - 3);

    SDL_RenderDrawPoint(renderer, x - 2, y - 2);
    SDL_RenderDrawPoint(renderer, x - 1, y - 2);
    SDL_RenderDrawPoint(renderer, x, y - 2);
    SDL_RenderDrawPoint(renderer, x + 1, y - 2);
    SDL_RenderDrawPoint(renderer, x + 2, y - 2);

    SDL_RenderDrawPoint(renderer, x - 2, y - 1);
    SDL_RenderDrawPoint(renderer, x + 2, y - 1);

    SDL_RenderDrawPoint(renderer, x - 3, y);
    SDL_RenderDrawPoint(renderer, x - 2, y);
    SDL_RenderDrawPoint(renderer, x + 2, y);
    SDL_RenderDrawPoint(renderer, x + 3, y);

    SDL_RenderDrawPoint(renderer, x - 2, y + 1);
    SDL_RenderDrawPoint(renderer, x + 2, y + 1);

    SDL_RenderDrawPoint(renderer, x - 2, y + 2);
    SDL_RenderDrawPoint(renderer, x - 1, y + 2);
    SDL_RenderDrawPoint(renderer, x, y + 2);
    SDL_RenderDrawPoint(renderer, x + 1, y + 2);
    SDL_RenderDrawPoint(renderer, x + 2, y + 2);

    SDL_RenderDrawPoint(renderer, x, y + 3);
}

// The purpose of this function is to draw a line between two nodes
// The first parameter will be an SDL_Renderer pointer
// The second and forth parameters will be the x and y coordinates of the first node
// The third and fith parameters will be the x and y coordinates of the second node
void drawLine(SDL_Renderer *renderer, int x1, int x2, int y1, int y2){
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

// The purpose of this function is to draw the boxes, lines and numbers
// The function will take take an SDL_Renderer pointer as a parameter
void makeFrame(SDL_Renderer *renderer){

    char num[100];
    float heightDist =  (maxLat - minLat)/9, widthDist = (maxLon - minLon)/4;

    //Creates the font
    TTF_Init();
    TTF_Font* Sans = TTF_OpenFont("OpenSans.ttf", 24);
    if(Sans == NULL){
        printf("No font!");
    }

    SDL_Color Black = {0, 0, 0};
    SDL_Surface* surfaceMessage;
    SDL_Texture* Message;

    SDL_Rect Message_rect;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect rect = { distToBoxWidth, distToBoxHeight, boxWidth, boxHeight};
    SDL_RenderDrawRect(renderer, &rect);

    //The future corrections (-x) that you will see at the end of every coordinates
    //are there to correct the differences between some values

    int i;
    for(i = 0; i < 5; i++){
        drawLine(renderer, distToBoxWidth + i*distBetweenLinesBot + distFromBoxWidth, distToBoxWidth + distFromBoxWidth + i*distBetweenLinesBot,
                 boxHeight + distToBoxHeight - smallLine - 1, boxHeight + distToBoxHeight - 1);
        drawLine(renderer, distToBoxWidth + i*distBetweenLinesBot + distFromBoxWidth, distToBoxWidth + i*distBetweenLinesBot + distFromBoxWidth,
                 distToBoxHeight + smallLine, distToBoxHeight);


        sprintf(num, "%lf", minLon + i*widthDist);
        Message_rect.w = strlen(num) * 6 * scaler;
        Message_rect.h = strlen(num) * 3 * scaler;
        surfaceMessage = TTF_RenderText_Solid(Sans, num, Black);
        Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

        Message_rect.x = distToBoxWidth - Message_rect.w/2 + i*distBetweenLinesBot + distFromBoxWidth;
        Message_rect.y = distToBoxHeight + boxHeight + 10;

        SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    }

    for(i = 0; i < 10; i++){
        drawLine(renderer, distToBoxWidth, distToBoxWidth + smallLine,
                 distToBoxHeight + i*distBetweenLinesLeft + distFromBoxHeight, distToBoxHeight + i*distBetweenLinesLeft + distFromBoxHeight);
        drawLine(renderer, distToBoxWidth + boxWidth - 2 - smallLine, distToBoxWidth + boxWidth - 1,
                 distToBoxHeight + i*distBetweenLinesLeft + distFromBoxHeight, distToBoxHeight + i*distBetweenLinesLeft + distFromBoxHeight);

        sprintf(num, "%lf", minLat + i*heightDist);
        Message_rect.w = strlen(num) * 6 * scaler;
        Message_rect.h = strlen(num) * 3 * scaler;
        surfaceMessage = TTF_RenderText_Solid(Sans, num, Black);
        Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

        Message_rect.x = distToBoxWidth - Message_rect.w - 14;
        Message_rect.y = distToBoxHeight + i*distBetweenLinesLeft - Message_rect.h/2 + distFromBoxHeight;

        SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    }
}

// The purpose of this function is to give the position of a node relative to the window that we render
// The function will take one double value as a parameter, this representing the longitude of the node
// The function will return the integer value of the relative value to the window
int relativePozX(double x){
    return (int) ((x - minLon)*mapWidth/(maxLon-minLon) + distToBoxWidth + distFromBoxWidth);
}

// The purpose of this function is to give the position of a node relative to the window that we render
// The function will take one double value as a parameter, this representing the latitude of the node
// The function will return the integer value of the relative value to the window
int relativePozY(double y){
    return (int) (height - ((y - minLat)*mapHeight/(maxLat-minLat) + distToBoxHeight + distFromBoxHeight));
}

// The purpose of this function is to show the map of the nodes and edges
// The function will take an integer as a parameter, this representing if the function should also show the path
// If the user has read two points, these two points will be colored black
void showMap(int showPath){
    initValues();

    //Creates the map
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Map", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    int running = 1;
    SDL_Event event;

    //The main window
    SDL_SetRenderDrawColor(renderer, 255, 255 ,255, 255);
    SDL_RenderClear(renderer);

    //Make a box for the map
    makeFrame(renderer);

    int i;
    extern Nodes listOfNodes;
    extern Links listOfLinks;
    extern int hasReadNodes;

    if(!showPath){
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        //Draw the points
        for(i = 0; i < listOfNodes.numberOfNodes; i++){
            drawPoint(relativePozX(listOfNodes.nodes[i].lon), relativePozY(listOfNodes.nodes[i].lat), renderer);
        }

        for(i = 0; i < listOfLinks.numberOfLinks; i++){
            drawLine(renderer, relativePozX(listOfLinks.links[i].node1.lon), relativePozX(listOfLinks.links[i].node2.lon),
                relativePozY(listOfLinks.links[i].node1.lat), relativePozY(listOfLinks.links[i].node2.lat));
        }


        if(hasReadNodes){
            extern int indexStart, indexFinish;
            SDL_SetRenderDrawColor(renderer, 0, 0 ,0 ,255);
            drawPoint(relativePozX(listOfNodes.nodes[indexStart].lon), relativePozY(listOfNodes.nodes[indexStart].lat), renderer);
            drawPoint(relativePozX(listOfNodes.nodes[indexFinish].lon), relativePozY(listOfNodes.nodes[indexFinish].lat), renderer);
        }

        //Shows what was drawn
        SDL_RenderPresent(renderer);

        while(running){
            while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
                    running = 0;
                }
            }
        }
    }

    if(showPath){
        animatePath(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
