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
#include "globalFunctions.h"

//The function will return -1 if the node is not in the list
//or the index otherwise
int nodeInLinks(int Id){
    extern Links listOfLinks;

    for(int i = 0; i < listOfLinks.numberOfLinks; i++)
        if(listOfLinks.links[i].node1Id == Id || listOfLinks.links[i].node2Id == Id)
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
            listOfLinks.links[links].node1Id = atoi(arg);

            arg = strtok(NULL, "= ");
            arg = strtok(NULL, "= ");
            listOfLinks.links[links].node2Id = atoi(arg);

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
    int position;


    file = fopen(path, "r");
    while(fscanf(file, "%[^\n]\n", line) != EOF){
        arg = strtok(line, " ");
        if(!strcmp("<bounding", arg)){}

        else if(!strcmp("<link", arg)){}

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
                listOfNodes.nodes[nodes++].lon = y;
            }

        }
        else break;
    }

    fclose(file);
    return 1;
}

int completeLinks(){
    extern Links listOfLinks;
    extern Nodes listOfNodes;
    int i, j;

    for(i = 0; i < listOfLinks.numberOfLinks; i++)
        for(j = 0; j < listOfNodes.numberOfNodes; j++){
            if(listOfLinks.links[i].node1Id ==listOfNodes.nodes[j].id){
                listOfLinks.links[i].node1Lat = listOfNodes.nodes[j].lat;
                listOfLinks.links[i].node1Lon = listOfNodes.nodes[j].lon;
            }
            if(listOfLinks.links[i].node2Id == listOfNodes.nodes[j].id){
                listOfLinks.links[i].node2Lat = listOfNodes.nodes[j].lat;
                listOfLinks.links[i].node2Lon = listOfNodes.nodes[j].lon;
            }

        }


    return 1;
}

