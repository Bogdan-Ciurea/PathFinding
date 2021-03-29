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

//Taken from : https://stackoverflow.com/questions/1157209/is-there-an-alternative-sleep-function-in-c-to-milliseconds
//Start
#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif
//Finish reference code


#include "functions.h"



// The purpose of this function is to see if a node has the given coordinates
// The function will take two double variables, representing the x and y coordinates of the supposed node
// If the given coordinates have a corresponding node, the function will return the index if the node the coordinates correspond with
// If the given coordinates do not have a corresponding node, the function will return -1
int nodeInNodes(double x, double y){
    extern Nodes listOfNodes;
    int i;
    for(i = 0; i < listOfNodes.numberOfNodes; i++)
        if(listOfNodes.nodes[i].lat == x && listOfNodes.nodes[i].lon == y)
            return listOfNodes.nodes[i].matrixId;
    printf("Node not found! Try again.\n");
    return -1;
}

// The purpose of this function is to chose two random nodes from the list
// If the function worked properly, and the two random nodes where selected, then it will return 1 indicating success
// If the function did not work as intended, it will return 0 indicating an error
int randomNodes(){
    extern int indexStart, indexFinish;
    extern Nodes listOfNodes;

    indexStart = rand()%(listOfNodes.numberOfNodes - 1);
    indexFinish = rand()%(listOfNodes.numberOfNodes - 1);
    indexStart = rand()%(listOfNodes.numberOfNodes - 1);
    indexFinish = rand()%(listOfNodes.numberOfNodes - 1);
    while(indexStart == indexFinish){
        indexFinish = rand()%(listOfNodes.numberOfNodes - 1);
    }

    return 1;
}

// The purpose of this function is to see if the input is a number or not
// The function will take a char pointer as a parameter
// If the input is a number, the function will return 1
// If the input is not a number, the function will return 0
int inputIsNumber(char* input){
    int i, dots = 0;
    for(i = 0; i < strlen(input); i++){
        if(strchr("1234567890.", input[i]) == NULL){
            if(! (i == 0 && input[0] == '-') ){
                printf("Invalid format! Try again.\n");
                return 0;
            }
        }
        if( '.' == input[i] ){
            dots++;
            if(dots > 1){
            printf("Invalid format! Try again.\n");
            return 0;
            }
        }
    }

    return 1;
}

//The function that will get the two points' coordinates
// The purpose of this function is to get the two nodes
// If the function worked properly, and the nodes have been read successfully, then it will return 1 indicating success
// If the function did not work as intended, it will return 0 indicating an error
// The user will be asked to give the coordinates of the nodes
// The function will read the input and validate it (if it is a number)
// If the input is valid the function will try to find the nodes
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

// The purpose of this function is to find the distance between two nodes that are connected with one edge
// The function will take two integers as parameters. These parameters represent the matrixId.
// If the function worked properly, and the node have an edge connecting them, then it will return the weight of the edge indicating success
// If the function did not work as intended, it will return DBL_MAX indicating an error
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

// The purpose of this function is to wait a specific number of seconds
// The function will take one float value as a parameter, this representing the seconds we want to wait
// It is an equivalent of time.sleep in python
void wait(float time){// cross-platform sleep function
    time *= 1000;
    int seconds = time;

    //Taken from : https://stackoverflow.com/questions/1157209/is-there-an-alternative-sleep-function-in-c-to-milliseconds
    //Start
    #ifdef WIN32
        Sleep(seconds);
    #elif _POSIX_C_SOURCE >= 199309L
        struct timespec ts;
        ts.tv_sec = seconds / 1000;
        ts.tv_nsec = (seconds % 1000) * 1000000;
        nanosleep(&ts, NULL);
    #else
        if (seconds >= 1000)
        sleep(seconds / 1000);
        usleep((seconds % 1000) * 1000);
    #endif
    //Finish reference code
/*
    #ifdef _WIN32
    Sleep(1000 * seconds);
    #else
    //sleep(1);
    usleep(1000000 * seconds);
    #endif*/
}

// The purpose of this function is to add information to the pathOfNodes from the listOfNodes
// After the path is build, it will only store the id in matrix of each node
// So, we add the information to the pathOfNodes
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
