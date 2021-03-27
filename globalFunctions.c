/************************************************************************
    University of Leeds
    School of Computing
    COMP1921 - Programming project
    Coursework 2
    File: globalFunctions.c
    Student Name: Bogdan Alexandru Ciurea
    Student ID: 201438333
    Email: sc20bac@leeds.ac.uk
    Date Work Commenced: 3rd Mar 2021
*************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "functions.h"



//A function that will check if a point exists
int nodeInNodes(double x, double y){
    extern Nodes listOfNodes;
    int i;
    for(i = 0; i < listOfNodes.numberOfNodes; i++)
        if(listOfNodes.nodes[i].lat == x && listOfNodes.nodes[i].lon == y)
            return listOfNodes.nodes[i].matrixId;
    printf("Node not found! Try again.\n");
    return -1;
}

int randomNodes(){
    extern int indexStart, indexFinish;
    extern Nodes listOfNodes;

    indexStart = rand()%listOfNodes.numberOfNodes;
    indexFinish = rand()%listOfNodes.numberOfNodes;
    indexStart = rand()%listOfNodes.numberOfNodes;
    indexFinish = rand()%listOfNodes.numberOfNodes;
    while(indexStart == indexFinish){
        indexFinish = rand()%listOfNodes.numberOfNodes;
    }

    return 1;
}

int inputIsNumber(char* input){
    int i;
    for(i = 0; i < strlen(input); i++){
        if(strchr("1234567890.", input[i]) == NULL){
            if(! (i == 0 && input[0] == '-') ){
                printf("Invalid format! Try again.\n");
                return 0;
            }
        }
    }

    return 1;
}

//A function that will read the coordinates and validate them
int getCoordinatesStFin(){
    extern int indexStart, indexFinish;
    double x, y;
    char input[100], *firstElem;

    printf("Keep in mind that you can also type 'back' to return to the Main Menu.\n");

    //Read the coordinates for the first point
    do{
        //The X-axis
        printf("Type the coordinates of the start node:\n\nLongitude/X-Axis\n");

        do{
            printf("\n>>>"); scanf(" %[^\n]", input);
            firstElem = strtok(input, " ");
            if(!strcmp(firstElem, "back"))
                return 0;
        }while(!inputIsNumber(firstElem));
        x = atof(firstElem);

        printf("The start node's Longitude was read successfully!\n\nLatitude/Y-Axis\n");
        //The Y-axis
        do{
            printf("\n>>>"); scanf(" %[^\n]", input);
            firstElem = strtok(input, " ");
            if(!strcmp(firstElem, "back"))
                return 0;
        }while(!inputIsNumber(firstElem));
        y = atof(firstElem);


    }while( (indexStart = nodeInNodes(x,y)) == -1);
    printf("\n-------------------------------------\n");
    printf("The start node was found successfully!\n-------------------------------------\n\n");

    //Read the coordinates for the second point
    do{
        //The X-axis
        printf("Type the coordinates of the finish node:\n\nLongitude/X-Axis\n");

        do{
            printf("\n>>>"); scanf(" %[^\n]", input);
            firstElem = strtok(input, " ");
            if(!strcmp(firstElem, "back"))
                return 0;
        }while(!inputIsNumber(firstElem));
        x = atof(firstElem);

        printf("The finish node's Longitude was read successfully!\n\nLatitude/Y-Axis\n");

        //The Y-axis
        do{
            printf("\n>>>"); scanf(" %[^\n]", input);
            firstElem = strtok(input, " ");
            if(!strcmp(firstElem, "back"))
                return 0;
        }while(!inputIsNumber(firstElem));
        y = atof(firstElem);

    }while( (indexFinish = nodeInNodes(x,y)) == -1);

    printf("\n-------------------------------------\nThe finish node was found successfully!\n-------------------------------------\n\n");


    return 1;
}

double distBetweenNodes(int node1, int node2){
    int i;
    extern Links listOfLinks;

    for(i = 0 ;i < listOfLinks.numberOfLinks; i++)
        if(listOfLinks.links[i].node1.matrixId == node1 && listOfLinks.links[i].node2.matrixId == node2)
            return listOfLinks.links[i].length;
        else if(listOfLinks.links[i].node1.matrixId == node2 && listOfLinks.links[i].node2.matrixId == node1)
            return listOfLinks.links[i].length;
    return DBL_MAX;
}


void wait(float seconds){
    #ifdef _WIN32
    Sleep(1000 * seconds);
    #else
    usleep(1000000 * seconds);
    #endif
}

void completePath(){
    extern Nodes pathOfNodes;
    extern Nodes listOfNodes;
    int i;

    for(i = 0; i < pathOfNodes.numberOfNodes; i++){
        pathOfNodes.nodes[i].id = listOfNodes.nodes[pathOfNodes.nodes[i].matrixId].id;
        pathOfNodes.nodes[i].lat = listOfNodes.nodes[pathOfNodes.nodes[i].matrixId].lat;
        pathOfNodes.nodes[i].lon = listOfNodes.nodes[pathOfNodes.nodes[i].matrixId].lon;
    }
}
