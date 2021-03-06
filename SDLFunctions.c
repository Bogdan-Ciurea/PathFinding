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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "globalFunctions.h"

static const int width = 640;
static const int mapWidth = 425;
static const int height = 480;
static const int mapHeight = 366;
extern double maxLat, maxLon, minLat, minLon;


double relativePozX(double x){
    return (x - minLon)*mapWidth/(maxLon-minLon) + (width - mapWidth)/2;
}

double relativePozY(double y){
    return height - ((y - minLat)*mapHeight/(maxLat-minLat) + (height-mapHeight)/2);
}

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

        //Draws all the points
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        int i;
        extern Nodes listOfNodes;

        for(i = 0; i < listOfNodes.numberOfNodes; i++){
            //printf("%f, %f\n", relativePozX(listOfNodes.nodes[i].lat), relativePozY(listOfNodes.nodes[i].lon));
            SDL_RenderDrawPoint(renderer,relativePozX(listOfNodes.nodes[i].lon), relativePozY(listOfNodes.nodes[i].lat));
            //break;
        }

        //Shows what was drawn
        SDL_RenderPresent(renderer);

        //running = 0;

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}
