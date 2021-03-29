/************************************************************************
    University of Leeds
    School of Computing
    COMP1921 - Programming project
    Coursework 2
    File: bellman_ford.c
    Student Name: Bogdan Alexandru Ciurea
    Student ID: 201438333
    Email: sc20bac@leeds.ac.uk
    Date Work Commenced: 3rd Mar 2021
*************************************************************************/

/*
Final_Map.map
read nodes
53.807817
-1.562377
53.808649
-1.544174
bellman-ford
yes

 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

#include "functions.h"

extern Links listOfLinks;
extern Nodes pathOfNodes;
extern Nodes listOfNodes;
extern int indexStart, height, width, indexFinish;

// The purpose of this function is to find the shortest distance from node x to node y using Bellman-Ford's Algorithm
// If the function worked properly, and the path is found, then it will return 1 indicating success
// If the function did not work as intended, it will return 0 indicating an error
// The function will have three steps:
// Step 1: Initialize distances from the start node to all other nodes
// Step 2: Relax all edges |listOfNodes.numberOfNodes| - 1 times
// Disclaimer!: The function is not meant for find the path so it will just show the distance
int bellmanFord(){
    initValues();
    SDL_Event event;

    int i, j, lastNode;
	double distance[listOfNodes.numberOfNodes], weight;

    // Step 1: Initialize distances from the start node to all other nodes
    for (i = 0; i < listOfNodes.numberOfNodes; i++)
        distance[i] = DBL_MAX;
    distance[indexStart] = 0;

    // Step 2: Relax all edges |listOfNodes.numberOfNodes| - 1 times
    for (i = 1; i < listOfNodes.numberOfNodes; i++) {
        for (j = 0; j < listOfLinks.numberOfLinks; j++) {
            weight = listOfLinks.links[j].length;
            if (distance[listOfLinks.links[j].node1.matrixId] != DBL_MAX && distance[listOfLinks.links[j].node1.matrixId] + weight < distance[listOfLinks.links[j].node2.matrixId])
                distance[listOfLinks.links[j].node2.matrixId] = distance[listOfLinks.links[j].node1.matrixId] + weight;
            else if (distance[listOfLinks.links[j].node2.matrixId] != DBL_MAX && distance[listOfLinks.links[j].node2.matrixId] + weight < distance[listOfLinks.links[j].node1.matrixId])
                distance[listOfLinks.links[j].node1.matrixId] = distance[listOfLinks.links[j].node2.matrixId] + weight;
        }
    }

    // Step 3: Check for negative-weight cycles
    /*for (i = 0; i < listOfLinks.numberOfLinks; i++) {
        weight = listOfLinks.links[j].length;
        if (distance[listOfLinks.links[i].node1.matrixId] != DBL_MAX && distance[listOfLinks.links[i].node1.matrixId] + weight < distance[listOfLinks.links[i].node2.matrixId]) {
            printf("Graph contains negative weight cycle");
            return 0;
        }
        else if (distance[listOfLinks.links[j].node2.matrixId] != DBL_MAX && distance[listOfLinks.links[j].node2.matrixId] + weight < distance[listOfLinks.links[j].node1.matrixId]){
            printf("Graph contains negative weight cycle");
            return 0;
        }
    }*/

    //Return 0 if there is no path between the two nodes
    if(distance[indexFinish] == DBL_MAX)
        return 0;

    printf("The distance between the node Node %i and the Node %i is %f\n", listOfNodes.nodes[indexStart].id, listOfNodes.nodes[indexFinish].id, distance[indexFinish]);

    return 1;
}

