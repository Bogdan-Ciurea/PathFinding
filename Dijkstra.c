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
#include "functions.h"
/*
Final_Map.map
read nodes
53.807817
-1.562377
53.808649
-1.544174
dijkstra
 */

extern Links listOfLinks;
extern Nodes pathOfNodes;
extern Nodes listOfNodes;

void completePath(){
    for(int i = 0; i < pathOfNodes.numberOfNodes; i++){
        pathOfNodes.nodes[i].id = listOfNodes.nodes[pathOfNodes.nodes[i].matrixId].id;
        pathOfNodes.nodes[i].lat = listOfNodes.nodes[pathOfNodes.nodes[i].matrixId].lat;
        pathOfNodes.nodes[i].lon = listOfNodes.nodes[pathOfNodes.nodes[i].matrixId].lon;
    }
}

double distBetweenNodes(int node1, int node2){
    for(int i = 0 ;i < listOfLinks.numberOfLinks; i++)
        if(listOfLinks.links[i].node1.matrixId == node1 && listOfLinks.links[i].node2.matrixId == node2)
            return listOfLinks.links[i].length;
        else if(listOfLinks.links[i].node1.matrixId == node2 && listOfLinks.links[i].node2.matrixId == node1)
            return listOfLinks.links[i].length;
    return DBL_MAX;
}

int dijkstra(){

    extern int indexStart, indexFinish;

    int n = listOfNodes.numberOfNodes, i, j;

	double distance[n], mindistance;
	int visited[n], count, nextnode, pred[n];

	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the cost matrix

	//initialize pred[],distance[] and visited[]
	for(i = 0; i < n; i++){
		distance[i] = distBetweenNodes(indexStart, i);
		pred[i] = indexStart;
		visited[i] = 0;
	}

	distance[indexStart] = 0;
	visited[indexStart] = 1;
	count = 1;

	while(count < n - 1 && visited[indexFinish] == 0)
	{
		mindistance = DBL_MAX;

		//nextnode stores the node at the smallest distace
		for(i = 0; i < n; i++)
			if(distance[i] < mindistance && !visited[i]){
				mindistance = distance[i];
				nextnode = i;
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

	}
    else{
        printf("There is no connection between the two points");
    }


	return 1;
}
