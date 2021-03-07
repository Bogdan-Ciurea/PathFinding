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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "globalFunctions.h"

static const float multiplier = 1.5;
static const int width = 640 * multiplier;
static const int mapWidth = 500 * multiplier;
static const int height = 480 * multiplier;
static const int mapHeight = 400 * multiplier;
extern double maxLat, maxLon, minLat, minLon;

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

//Shows the relative position to the window that we want to show
int relativePozX(double x){
    return (int) ((x - minLon)*mapWidth/(maxLon-minLon) + (width - mapWidth)/2);
}

int relativePozY(double y){
    return (int) (height - ((y - minLat)*mapHeight/(maxLat-minLat) + (height-mapHeight)/2));
}

//Draws the map
void showMap(){

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Map", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    int running = 1;
    SDL_Event event;
    while(running){

        while(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT)
                running = 0;

        //The main window
        SDL_SetRenderDrawColor(renderer, 255, 255 ,255, 255);
        SDL_RenderClear(renderer);

        //Make a box for the map
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Rect rect = {(width - mapWidth) / 2 - 4, (height - mapHeight) / 2 - 4, mapWidth + 8, mapHeight + 8};
        SDL_RenderDrawRect(renderer, &rect);

        //Draws all the points
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        int i;
        extern Nodes listOfNodes;
        extern Links listOfLinks;

        //Draw the points
        for(i = 0; i < listOfNodes.numberOfNodes; i++)
            drawPoint(relativePozX(listOfNodes.nodes[i].lon), relativePozY(listOfNodes.nodes[i].lat), renderer);


        //SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        for(i = 0; i < listOfLinks.numberOfLinks; i++)
            drawLine(renderer, relativePozX(listOfLinks.links[i].node1Lon), relativePozX(listOfLinks.links[i].node2Lon),
                     relativePozY(listOfLinks.links[i].node1Lat), relativePozY(listOfLinks.links[i].node2Lat));

        //Shows what was drawn
        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}
