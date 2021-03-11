/************************************************************************
    University of Leeds
    School of Computing
    COMP1921 - Programming project
    Coursework 2
    File: Dijkstra.c
    Student Name: Bogdan Alexandru Ciurea
    Student ID: 201438333
    Email: sc20bac@leeds.ac.uk
    Date Work Commenced: 3rd Mar 2021
*************************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>

#include <time.h> //To make the animation

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

 */

extern Links listOfLinks;
extern Nodes pathOfNodes;
extern Nodes listOfNodes;

void wait(float seconds){
    int millSec = 10000 * seconds;
    clock_t startTime = clock();

    while(clock() < startTime + millSec){

    }
}

void completePath(){
    int i;
    for(i = 0; i < pathOfNodes.numberOfNodes; i++){
        pathOfNodes.nodes[i].id = listOfNodes.nodes[pathOfNodes.nodes[i].matrixId].id;
        pathOfNodes.nodes[i].lat = listOfNodes.nodes[pathOfNodes.nodes[i].matrixId].lat;
        pathOfNodes.nodes[i].lon = listOfNodes.nodes[pathOfNodes.nodes[i].matrixId].lon;
    }
}

double distBetweenNodes(int node1, int node2){
    int i;
    for(i = 0 ;i < listOfLinks.numberOfLinks; i++)
        if(listOfLinks.links[i].node1.matrixId == node1 && listOfLinks.links[i].node2.matrixId == node2)
            return listOfLinks.links[i].length;
        else if(listOfLinks.links[i].node1.matrixId == node2 && listOfLinks.links[i].node2.matrixId == node1)
            return listOfLinks.links[i].length;
    return DBL_MAX;
}

void drawInitialFrame(SDL_Renderer *renderer){
    int i;

    //Draw the points
    for(i = 0; i < listOfNodes.numberOfNodes; i++)
        drawPoint(relativePozX(listOfNodes.nodes[i].lon), relativePozY(listOfNodes.nodes[i].lat), renderer);



    for(i = 0; i < listOfLinks.numberOfLinks; i++)
        drawLine(renderer, relativePozX(listOfLinks.links[i].node1.lon), relativePozX(listOfLinks.links[i].node2.lon),
            relativePozY(listOfLinks.links[i].node1.lat), relativePozY(listOfLinks.links[i].node2.lat));

    //Draw the initial state of the frame
    SDL_RenderPresent(renderer);

}

void animatePath(SDL_Renderer *renderer){
    int running = 1, i, j;
    SDL_Event event;


    //Show the path with a green color

    //Clear the rendered image and render one from scratch
    SDL_SetRenderDrawColor(renderer, 255, 255 ,255, 255);
    SDL_RenderClear(renderer);
    makeFrame(renderer); //Draw the plot (color is black)



    while(running){

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Color is red
        drawInitialFrame(renderer);

        //Draw the path with a blue color
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

        drawPoint(relativePozX(pathOfNodes.nodes[pathOfNodes.numberOfNodes - 1].lon), relativePozY(pathOfNodes.nodes[pathOfNodes.numberOfNodes - 1].lat),renderer);

        for(i = pathOfNodes.numberOfNodes - 2; i > 0 && running ==1 ; i--){
            while(SDL_PollEvent(&event))
                if(event.type == SDL_QUIT)
                    running = 0;

            drawPoint(relativePozX(pathOfNodes.nodes[i].lon), relativePozY(pathOfNodes.nodes[i].lat),renderer);
            drawLine(renderer, relativePozX(pathOfNodes.nodes[i - 1].lon), relativePozX(pathOfNodes.nodes[i].lon),
                relativePozY(pathOfNodes.nodes[i - 1].lat), relativePozY(pathOfNodes.nodes[i].lat));

            wait(0.2);
            SDL_RenderPresent(renderer);
        }

        for(j = 0; j < 3 && running == 1; j++){
            while(SDL_PollEvent(&event))
                if(event.type == SDL_QUIT)
                    running = 0;

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Color is red
            drawInitialFrame(renderer);


            //Draw the path with a blue color
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            wait(0.4);
            SDL_RenderPresent(renderer);
            drawPoint(relativePozX(pathOfNodes.nodes[pathOfNodes.numberOfNodes - 1].lon), relativePozY(pathOfNodes.nodes[pathOfNodes.numberOfNodes - 1].lat),renderer);

            for(i = pathOfNodes.numberOfNodes - 2; i > 0 && running == 1 ; i--){
                while(SDL_PollEvent(&event))
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

int dijkstra(int animation){
    //Initialize the variables
    initValues();
    SDL_Event event;
    extern int indexStart, height, width; //indexFinish;

    int n = listOfNodes.numberOfNodes, i, j, lastNode;
	double distance[n], mindistance;
	int visited[n], count, nextnode, pred[n];


    //Initialize the SDL Window to show how the algorithm works
    //It has to be initialized even if we do not need it
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Dijkstra", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!animation){
        //Destroy the window that shows how the algorithm works
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    if(animation){

        //Make the frame
        SDL_SetRenderDrawColor(renderer, 255, 255 ,255, 255); //White
        SDL_RenderClear(renderer);
        makeFrame(renderer); //Draw the plot (color is black)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //Red

        //Draw the initial state of the frame
        drawInitialFrame(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); //Blue
        drawPoint(relativePozX(listOfNodes.nodes[indexStart].lon), relativePozY(listOfNodes.nodes[indexStart].lat), renderer);
        SDL_RenderPresent(renderer);
    }

	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the cost matrix



	//Initialize pred[],distance[] and visited[]
	for(i = 0; i < n; i++){
		distance[i] = distBetweenNodes(indexStart, i);
		pred[i] = indexStart;
		visited[i] = 0;

		//Draw the pint in green and then change it to red
		/*if(indexStart != i){
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); //Green
            drawPoint(relativePozX(listOfNodes.nodes[i].lon), relativePozY(listOfNodes.nodes[i].lat), renderer);
            SDL_RenderPresent(renderer);
            //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //Red
            //drawPoint(relativePozX(listOfNodes.nodes[i].lon), relativePozY(listOfNodes.nodes[i].lat), renderer);
        }*/

	}

	distance[indexStart] = 0;
	visited[indexStart] = 1;
	count = 1;
	nextnode = indexStart;

	while(count < n - 1 && visited[indexFinish] == 0){
		mindistance = DBL_MAX;
        lastNode = nextnode;


		//nextnode stores the node at the smallest distance
		for(i = 0; i < n; i++){
			if(distance[i] < mindistance && !visited[i]){
				mindistance = distance[i];
				nextnode = i;

				if(animation){
                    while(SDL_PollEvent(&event))
                        if(event.type == SDL_QUIT){
                            SDL_DestroyRenderer(renderer);
                            SDL_DestroyWindow(window);
                            SDL_Quit();
                            return 0;
                        }

                    //draw the searched node
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
            //printf("%i %i %i", lastNode, nextnode, listOfNodes.numberOfNodes);
            //drawLine(renderer, relativePozX(pathOfNodes.nodes[lastNode].lon), relativePozX(pathOfNodes.nodes[nextnode].lon),
                     //relativePozY(pathOfNodes.nodes[lastNode].lat), relativePozY(pathOfNodes.nodes[nextnode].lat));
        }


        //check if a better path exists through nextnode
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

	//If there is a path, the program will make a list of nodes that will be used in the "show path" command
    if(distance[indexFinish] != DBL_MAX){
        pathOfNodes.numberOfNodes = 1;
        printf("The distance between the node Node %i and the Node %i is %f\n", listOfNodes.nodes[indexStart].id, listOfNodes.nodes[indexFinish].id, distance[indexFinish]);

        //Finds the size of the path of nodes
        j = indexFinish;
        do{
            j = pred[j];
            pathOfNodes.numberOfNodes++;
        }while(j != indexStart);

        //Builds the pathOfNode
        pathOfNodes.nodes = calloc(pathOfNodes.numberOfNodes, sizeof(Node));
        i = 0;
        pathOfNodes.nodes[i++].matrixId = indexFinish;

        j = indexFinish;
        do{
            j = pred[j];
            pathOfNodes.nodes[i++].matrixId = j;
        }while(j != indexStart);
        //Adds the information to the path
        completePath();

        //Shows the path of nodes
        printf("Path: %i", pathOfNodes.nodes[pathOfNodes.numberOfNodes - 1].id);
        for(i = pathOfNodes.numberOfNodes - 2; i >=0 ; i--)
            printf(" -> %i", pathOfNodes.nodes[i].id);
        printf("\n");

        if(animation){
            //Animates the path with a green color
            animatePath(renderer);
        }


	}
    else{
        printf("There is no connection between the two points");
    }

    if(animation){
        //Destroy the window that shows how the algorithm works
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }





	return 1;
}
