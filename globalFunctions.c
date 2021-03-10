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
#include "functions.h"

//A function that will check if a point exists
int nodeInNodes(double x, double y){
    extern Nodes listOfNodes;
    for(int i = 0; i < listOfNodes.numberOfNodes; i++)
        if(listOfNodes.nodes[i].lat == x && listOfNodes.nodes[i].lon == y)
            return listOfNodes.nodes[i].matrixId;
    printf("Node not found! Try again.\n");
    return -1;
}

int inputIsNumber(char* input){
    for(int i = 0; i < strlen(input); i++)
        if(strchr("1234567890.", input[i]) == NULL)
            if(! (i == 0 && input[0] == '-') ){
            printf("Invalid format! Try again.\n");
            return 0;
        }
    return 1;
}

//A function that will read the coordinates and validate them
int getCoordinatesStFin(){
    extern int indexStart, indexFinish;
    double x, y;
    char input[100], *firstElem;

    //Read the coordinates for the first point
    do{
        //The X-axis
        printf("Type the coordinates of the start node:\nLongitude/X-Axis\n");

        do{
            printf(">>>"); scanf(" %[^\n]", input);
            firstElem = strtok(input, " ");
        }while(!inputIsNumber(firstElem));
        x = atof(firstElem);

        printf("The start node's Longitude was read successfully!\nLatitude/Y-Axis\n");
        //The Y-axis
        do{
            printf(">>>"); scanf(" %[^\n]", input);
            firstElem = strtok(input, " ");
        }while(!inputIsNumber(firstElem));
        y = atof(firstElem);


    }while( (indexStart = nodeInNodes(x,y)) == -1);
    printf("\n-------------------------------------\n");
    printf("The start node was found successfully!\n-------------------------------------\n\n");

    //Read the coordinates for the second point
    do{
        //The X-axis
        printf("Type the coordinates of the finish node:\nLongitude/X-Axis\n");

        do{
            printf(">>>"); scanf(" %[^\n]", input);
            firstElem = strtok(input, " ");
        }while(!inputIsNumber(firstElem));
        x = atof(firstElem);

        printf("The finish node's Longitude was read successfully!\nLatitude/Y-Axis\n");

        //The Y-axis
        do{
            printf(">>>"); scanf(" %[^\n]", input);
            firstElem = strtok(input, " ");
        }while(!inputIsNumber(firstElem));
        y = atof(firstElem);

    }while( (indexFinish = nodeInNodes(x,y)) == -1);

    printf("\n-------------------------------------\nThe finish node was found successfully!\n-------------------------------------\n\n");


    return 1;
}
