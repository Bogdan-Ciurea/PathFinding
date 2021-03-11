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

#include <SDL.h>
#include <SDL_image.h>
//#include <SDL_ttf.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

//These distances are taken from the image that we where given
//They can be changed by changing the value of the scaler
extern const float scaler = 1.5;
extern const int width = 640 * scaler;
extern const int mapWidth = 421 * scaler;
extern const int height = 480 * scaler;
extern const int mapHeight = 358 * scaler;
extern const int distToBoxWidth = 107 * scaler;
extern const int distToBoxHeight = 24 * scaler;
extern const int distFromBoxWidth = 20 * scaler;
extern const int distFromBoxHeight = 40 * scaler;
extern const int smallLine = 5 * scaler;
extern const int distBetweenLinesBot = 100 * scaler;
extern const int distBetweenLinesLeft = 38 * scaler;
extern const int boxWidth = 500 * scaler;
extern const int boxHeight = 420 * scaler;

extern double maxLat, maxLon, minLat, minLon;
extern Nodes pathOfNodes;

//Shows the points in a star like formation
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

// Draws a line between two points
void drawLine(SDL_Renderer *renderer, int x1, int x2, int y1, int y2){
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void makeFrame(SDL_Renderer *renderer){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect rect = { distToBoxWidth, distToBoxHeight, boxWidth, boxHeight};
    SDL_RenderDrawRect(renderer, &rect);

    //The future corrections (-x) that you will see at the end of every coordinates
    //are there to correct the differences between some values

    int i;
    for(i = 1; i <= 4; i++){
        drawLine(renderer, distToBoxWidth + i*distBetweenLinesBot - 1, distToBoxWidth + i*distBetweenLinesBot - 1,
                 boxHeight + distToBoxHeight - smallLine - 1, boxHeight + distToBoxHeight - 1);
        drawLine(renderer, distToBoxWidth + i*distBetweenLinesBot - 1, distToBoxWidth + i*distBetweenLinesBot - 1,
                 distToBoxHeight + smallLine, distToBoxHeight);
    }
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for(i = 1; i <= 10; i++){
        drawLine(renderer, distToBoxWidth, distToBoxWidth + smallLine, distToBoxHeight + i*distBetweenLinesLeft - 1, distToBoxHeight + i*distBetweenLinesLeft - 1);
        drawLine(renderer, distToBoxWidth + boxWidth - 2 - smallLine, distToBoxWidth + boxWidth - 1,
                 distToBoxHeight + i*distBetweenLinesLeft - 1, distToBoxHeight + i*distBetweenLinesLeft - 1);
    }

}

//Shows the relative position to the window that we want to show
int relativePozX(double x){
    return (int) ((x - minLon)*mapWidth/(maxLon-minLon) + distToBoxWidth + distFromBoxWidth);
}

int relativePozY(double y){
    return (int) (height - ((y - minLat)*mapHeight/(maxLat-minLat) + distToBoxHeight + distFromBoxHeight));
}

//Draws the map
void showMap(int showPath){

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

    while(running && !showPath){

        while(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT)
                running = 0;

        //Draws all the points
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);



        //Draw the points
        for(i = 0; i < listOfNodes.numberOfNodes; i++)
            drawPoint(relativePozX(listOfNodes.nodes[i].lon), relativePozY(listOfNodes.nodes[i].lat), renderer);



        for(i = 0; i < listOfLinks.numberOfLinks; i++)
            drawLine(renderer, relativePozX(listOfLinks.links[i].node1.lon), relativePozX(listOfLinks.links[i].node2.lon),
                     relativePozY(listOfLinks.links[i].node1.lat), relativePozY(listOfLinks.links[i].node2.lat));

        //Shows what was drawn
        SDL_RenderPresent(renderer);

    }
    if(showPath)
        animatePath(renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    //TTF_Quit();
    SDL_Quit();

}
