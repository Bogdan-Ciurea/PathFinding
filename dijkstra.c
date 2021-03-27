/************************************************************************
    University of Leeds
    School of Computing
    COMP1921 - Programming project
    Coursework 2
    File: dijkstra.c
    Student Name: Bogdan Alexandru Ciurea
    Student ID: 201438333
    Email: sc20bac@leeds.ac.uk
    Date Work Commenced: 3rd Mar 2021
*************************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "functions.h"
/*
Final_Map.map
read nodes
53.807817
-1.562377
53.808649
-1.544174
dijkstra
yes

Final_Map.map
random nodes
find path
no

 */

extern Links listOfLinks;
extern Nodes pathOfNodes;
extern Nodes listOfNodes;


// The purpose of this function is to draw the first state of the frame (red dots and edges and the legend)
// This function will take an SDL_Renderer pointer as a parameter
void drawInitialFrame(SDL_Renderer *renderer){
    int i;

    //Draw the points
    for(i = 0; i < listOfNodes.numberOfNodes; i++)
        drawPoint(relativePozX(listOfNodes.nodes[i].lon), relativePozY(listOfNodes.nodes[i].lat), renderer);

    for(i = 0; i < listOfLinks.numberOfLinks; i++)
        drawLine(renderer, relativePozX(listOfLinks.links[i].node1.lon), relativePozX(listOfLinks.links[i].node2.lon),
            relativePozY(listOfLinks.links[i].node1.lat), relativePozY(listOfLinks.links[i].node2.lat));

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //Color is Black
    drawPoint(listOfNodes.nodes[indexFinish].lon);
    drawPoint(relativePozX(listOfNodes.nodes[indexStart].lon), relativePozY(listOfNodes.nodes[indexStart].lat), renderer);
    drawPoint(relativePozX(listOfNodes.nodes[indexFinish].lon), relativePozY(listOfNodes.nodes[indexFinish].lat), renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //Color is Red

    //Draw the initial state of the frame
    SDL_RenderPresent(renderer);
}

// The purpose of this function is to make an animation of the path from node x to node y
// This function will take an SDL_Renderer pointer as a parameter
// The animation will consist of two parts:
// The first part is to connect every pont, from node x to node y
// The second part is to make the nodes flash, in a blue color there, three times
void animatePath(SDL_Renderer *renderer){
    int running = 1, i, j;
    SDL_Event event;

    // Show the path with a blue color

    // Clear the rendered image and render one from scratch
    SDL_SetRenderDrawColor(renderer, 255, 255 ,255, 255);
    SDL_RenderClear(renderer);
    makeFrame(renderer); // Draw the plot (color is black)

    while(running){

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Color is red
        drawInitialFrame(renderer);

        // Draw the path with a blue color
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

        // First part
        for(i = pathOfNodes.numberOfNodes - 1; i > 0 && running == 1 ; i--){
            while(SDL_PollEvent(&event)) // Checks if the window is closed
                if(event.type == SDL_QUIT)
                    running = 0;


            drawPoint(relativePozX(pathOfNodes.nodes[i].lon), relativePozY(pathOfNodes.nodes[i].lat),renderer);
            drawLine(renderer, relativePozX(pathOfNodes.nodes[i - 1].lon), relativePozX(pathOfNodes.nodes[i].lon),
                relativePozY(pathOfNodes.nodes[i - 1].lat), relativePozY(pathOfNodes.nodes[i].lat));

            wait(0.13);
            SDL_RenderPresent(renderer);
        }

        // Second part
        for(j = 0; j < 3 && running == 1; j++){
            while(SDL_PollEvent(&event)) // Checks if the window is closed
                if(event.type == SDL_QUIT)
                    running = 0;

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Color is red
            drawInitialFrame(renderer);

            //Draw the path with a blue color
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            wait(0.4);
            SDL_RenderPresent(renderer);
            drawPoint(relativePozX(pathOfNodes.nodes[pathOfNodes.numberOfNodes - 1].lon), relativePozY(pathOfNodes.nodes[pathOfNodes.numberOfNodes - 1].lat),renderer);

            // Draws all of the points
            for(i = pathOfNodes.numberOfNodes - 2; i > 0 && running == 1 ; i--){
                while(SDL_PollEvent(&event)) // Checks if the window is closed
                    if(event.type == SDL_QUIT)
                        running = 0;

                drawPoint(relativePozX(pathOfNodes.nodes[i].lon), relativePozY(pathOfNodes.nodes[i].lat),renderer);
                drawLine(renderer, relativePozX(pathOfNodes.nodes[i - 1].lon), relativePozX(pathOfNodes.nodes[i].lon),
                    relativePozY(pathOfNodes.nodes[i - 1].lat), relativePozY(pathOfNodes.nodes[i].lat));
            }
            SDL_RenderPresent(renderer);
            wait(0.4);

        }

    }
}

// The purpose of this function is to find the shortest path and shortest distance from node x to node y using Dijkstra's Algorith
// The function will take an integer as a parameter. This value indicates if the user wants to see how the algorithm works
// If the function worked properly, and the path is found, then it will return 1 indicating succes
// If the function did not work as intended, it will return 0 indicating an error
// The function will have three steps:
// Step 1: Initialise the predecesor, the distance and the visited matrices
// Step 2: Relax all the edges
// Step 3: Make the path
// If the user chooses to see the animation, during the 2nd step, the viseded nodes will be collored in blue and the comared one in green
int dijkstra(int animation){
    // Initialize the variables
    initValues();
    SDL_Event event;
    extern int indexStart, height, width, indexFinish;

    int n = listOfNodes.numberOfNodes, i, j, lastNode;
	double distance[n], mindistance;
	int visited[n], count, nextnode, pred[n];

    // Initialize the SDL Window to show how the algorithm works
    // It has to be initialized even if we do not need it
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Dijkstra", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!animation){
        // Destroy the window that shows how the algorithm works
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    if(animation){

        // Make the frame
        SDL_SetRenderDrawColor(renderer, 255, 255 ,255, 255); //White
        SDL_RenderClear(renderer);
        makeFrame(renderer); //Draw the plot (color is black)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //Red

        // Draw the initial state of the frame
        drawInitialFrame(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); //Blue
        drawPoint(relativePozX(listOfNodes.nodes[indexStart].lon), relativePozY(listOfNodes.nodes[indexStart].lat), renderer);
        SDL_RenderPresent(renderer);
    } 

	// Step 1: Initialize pred[],distance[] and visited[]
	for(i = 0; i < n; i++){
		distance[i] = distBetweenNodes(indexStart, i);
		pred[i] = indexStart;
		visited[i] = 0;
	}

	distance[indexStart] = 0;
	visited[indexStart] = 1;
	count = 1;
	nextnode = indexStart;

	// Step 2: Relax all edges
	while(count < n - 1 && visited[indexFinish] == 0){
		mindistance = DBL_MAX;
        lastNode = nextnode;

		//nextnode stores the node at the smallest distance
		for(i = 0; i < n; i++){
			if(distance[i] < mindistance && !visited[i]){
				mindistance = distance[i];
				nextnode = i;

				if(animation){
                    while(SDL_PollEvent(&event)) // Checks if the window is closed
                        if(event.type == SDL_QUIT){
                            SDL_DestroyRenderer(renderer);
                            SDL_DestroyWindow(window);
                            SDL_Quit();
                            return 0;
                        }

                    // Draw the searched node
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); //Green
                    drawPoint(relativePozX(listOfNodes.nodes[i].lon), relativePozY(listOfNodes.nodes[i].lat), renderer);
                    SDL_RenderPresent(renderer);
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //Red
                    drawPoint(relativePozX(listOfNodes.nodes[i].lon), relativePozY(listOfNodes.nodes[i].lat), renderer);
				}
			}
        }

        if(animation){
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); //Blue
            drawPoint(relativePozX(listOfNodes.nodes[nextnode].lon), relativePozY(listOfNodes.nodes[nextnode].lat), renderer);
        }


        // Check if a better path exists through nextnode
        visited[nextnode] = 1;
        for(i = 0; i < n; i++){
            if(!visited[i]){
                if(mindistance + distBetweenNodes(nextnode, i) < distance[i]){
                    distance[i] = mindistance + distBetweenNodes(nextnode, i);
                    pred[i] = nextnode;
                }
            }
        }
		count++;
	}

    // Step 3: Make the path
	// If there is a path, the program will make a list of nodes that will be used in the "show path" command
    if(distance[indexFinish] != DBL_MAX){
        pathOfNodes.numberOfNodes = 1;
        printf("The distance between the node Node %i and the Node %i is %f\n", listOfNodes.nodes[indexStart].id, listOfNodes.nodes[indexFinish].id, distance[indexFinish]);

        //Finds the size of the path of nodes
        j = indexFinish;
        do{
            j = pred[j];
            pathOfNodes.numberOfNodes++;
        }while(j != indexStart);

        // Builds the pathOfNode
        pathOfNodes.nodes = calloc(pathOfNodes.numberOfNodes, sizeof(Node));
        i = 0;
        pathOfNodes.nodes[i++].matrixId = indexFinish;

        j = indexFinish;
        do{
            j = pred[j];
            pathOfNodes.nodes[i++].matrixId = j;
        }while(j != indexStart);
        // Adds the information to the path
        completePath();

        // Shows the path of nodes
        printf("Path: %i", pathOfNodes.nodes[pathOfNodes.numberOfNodes - 1].id);
        for(i = pathOfNodes.numberOfNodes - 2; i >=0 ; i--)
            printf(" -> %i", pathOfNodes.nodes[i].id);
        printf("\n");

        if(animation){
            // Animates the path with a green color
            animatePath(renderer);
        }
	}
    else{
        printf("There is no connection between the two points");
    }

    if(animation){
        // Destroy the window that shows how the algorithm works
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

	return 1;
}
