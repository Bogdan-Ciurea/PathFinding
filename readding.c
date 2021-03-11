/************************************************************************
    University of Leeds
    School of Computing
    COMP1921 - Programming project
    Coursework 2
    File: readding.c
    Student Name: Bogdan Alexandru Ciurea
    Student ID: 201438333
    Email: sc20bac@leeds.ac.uk
    Date Work Commenced: 3rd Mar 2021
*************************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

//Adds the points to the end on each Link
void completeLinks(){
    extern Links listOfLinks;
    extern Nodes listOfNodes;
    int i, j;

    for(i = 0; i < listOfLinks.numberOfLinks; i++)
        for(j = 0; j < listOfNodes.numberOfNodes; j++){
            if(listOfLinks.links[i].node1.id ==listOfNodes.nodes[j].id){
                listOfLinks.links[i].node1.lat = listOfNodes.nodes[j].lat;
                listOfLinks.links[i].node1.lon = listOfNodes.nodes[j].lon;
                listOfLinks.links[i].node1.matrixId = listOfNodes.nodes[j].matrixId;
            }
            if(listOfLinks.links[i].node2.id == listOfNodes.nodes[j].id){
                listOfLinks.links[i].node2.lat = listOfNodes.nodes[j].lat;
                listOfLinks.links[i].node2.lon = listOfNodes.nodes[j].lon;
                listOfLinks.links[i].node2.matrixId = listOfNodes.nodes[j].matrixId;
            }
        }
}

//The function will return -1 if the node is not in the list
//or the index otherwise
int nodeInLinks(int Id){
    extern Links listOfLinks;
    int i;

    for(i = 0; i < listOfLinks.numberOfLinks; i++)
        if(listOfLinks.links[i].node1.id == Id || listOfLinks.links[i].node2.id == Id)
            return 1;
    return 0;
}

//Reads the information from the file
int readFromFile(char* path){
    FILE* file = fopen(path, "r");
    char line[605] ,*arg;
    double x, y; int a;

    extern double maxLat, maxLon, minLat, minLon;
    int links = 0, nodes = 0;

    //See how many Links are there and store the data of Lat and Lon
    while(fscanf(file, "%[^\n]\n", line) != EOF){
        arg = strtok(line, " =");
        if(!strcmp("<bounding", arg)){
            arg = strtok(NULL," =");
            arg = strtok(NULL," =");
            minLat = atof(arg);

            arg = strtok(NULL," =");
            arg = strtok(NULL," =");
            minLon = atof(arg);

            arg = strtok(NULL," =");
            arg = strtok(NULL," =");
            maxLat = atof(arg);

            arg = strtok(NULL," =");
            arg = strtok(NULL," =");
            maxLon = atof(arg);

        }
        else if(!strcmp("<link", arg))
            links++;
        else break;
        /*if(!strcmp("<way", arg))
            way++;
        else if(!strcmp("<geom", arg))
            geom++;*/
    }
    fclose(file);

    //Create the list of Links
    extern Links listOfLinks;
    listOfLinks.numberOfLinks = links;
    listOfLinks.links = calloc(links, sizeof(Link));
    links = 0;

    //Store the information for the listOfLinks and see what Nodes are valid
    file = fopen(path, "r");
    while(fscanf(file, "%[^\n]\n", line) != EOF){
        arg = strtok(line, " =");
        if(!strcmp("<bounding", arg)){}

        else if(!strcmp("<link", arg)){
            arg = strtok(NULL, "= ");
            arg = strtok(NULL, "= ");
            listOfLinks.links[links].id = atoi(arg);

            arg = strtok(NULL, "= ");
            arg = strtok(NULL, "= ");
            listOfLinks.links[links].node1.id = atoi(arg);

            arg = strtok(NULL, "= ");
            arg = strtok(NULL, "= ");
            listOfLinks.links[links].node2.id = atoi(arg);

            arg = strtok(NULL, "= ");
            arg = strtok(NULL, "= ");
            arg = strtok(NULL, "= ");
            arg = strtok(NULL, "= ");
            listOfLinks.links[links++].length = atof(arg);
        }

        else if(!strcmp("<node", arg)){
            arg = strtok(NULL, "= ");
            arg = strtok(NULL, "= ");
            a = atoi(arg);

            arg = strtok(NULL, "= ");
            arg = strtok(NULL, "= ");
            x = atof(arg);

            arg = strtok(NULL, "= ");
            arg = strtok(NULL, "= ");
            y = atof(arg);

            if(minLat <= x && x <= maxLat && minLon <= y && y <= maxLon && nodeInLinks(a))
                nodes++;
        }
        else break;
    }


    extern Nodes listOfNodes;
    listOfNodes.numberOfNodes = nodes;
    listOfNodes.nodes = calloc(nodes, sizeof(Node));
    nodes = 0;


    file = fopen(path, "r");
    while(fscanf(file, "%[^\n]\n", line) != EOF){
        arg = strtok(line, " ");
        if(!strcmp("<bounding", arg) || !strcmp("<link", arg)){}

        else if(!strcmp("<node", arg)){
            arg = strtok(NULL, "= ");
            arg = strtok(NULL, "= ");
            a = atoi(arg);

            arg = strtok(NULL, "= ");
            arg = strtok(NULL, "= ");
            x = atof(arg);

            arg = strtok(NULL, "= ");
            arg = strtok(NULL, "= ");
            y = atof(arg);

            if(minLat <= x && x <= maxLat && minLon <= y && y <= maxLon && nodeInLinks(a)){
                listOfNodes.nodes[nodes].id = a;
                listOfNodes.nodes[nodes].lat = x;
                listOfNodes.nodes[nodes].lon = y;
                listOfNodes.nodes[nodes].matrixId = nodes;
                nodes++;
            }

        }
        else break;
    }

    fclose(file);

    //Adds the points to the end on each Link
    completeLinks();

    return 1;
}

//Makes a matrix that will be used later for the algorithms
/*
void makeMatrix(){
    extern Nodes listOfNodes;
    extern Links listOfLinks;
    int i, j;

    graph.matrix = calloc(listOfNodes.numberOfNodes, listOfNodes.numberOfNodes * sizeof(double));
    graph.dimension = listOfNodes.numberOfNodes;

    for(i = 0; i < listOfNodes.numberOfNodes; i++)
        for(j = 0; j < listOfNodes.numberOfNodes; j++)
            graph.matrix[i][j] = 0;

    printf("Hello\n");

    for(i = 0; i < listOfLinks.numberOfLinks; i++){
        graph.matrix[listOfLinks.links[i].node1.matrixId][listOfLinks.links[i].node2.matrixId] = listOfLinks.links[i].length;
        graph.matrix[listOfLinks.links[i].node2.matrixId][listOfLinks.links[i].node1.matrixId] = listOfLinks.links[i].length;
    }
}*/

