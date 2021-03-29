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

// The purpose if this function is to compare the expected and actual input
// The function will take two char pointers, the first representing the actual input and the second representing the expected input
// If the two inputs are the same, the function will return 1
// Id the two inputs are not the same, the function will return 0
const int validDataFromFile(const char *input, const char *expected){
    if(strcmp(input, expected) == 0)
        return 1;
    return 0;
}

// The purpose if this function is to add information the nodes stored in the listOfLinks from the listOfNodes
void completeLinks(){
    extern Links listOfLinks;
    extern Nodes listOfNodes;
    static int i, j;

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

// The purpose of this function is to see if a node is connected to any other node
// The function will take one integer value as a parameter, this representing id of the node
// If the function worked properly, and the node has an edge, then it will return 1
// If there is no edge from the node, it will return 0
const int nodeInLinks(const int Id){
    extern Links listOfLinks;
    static int i;

    for(i = 0; i < listOfLinks.numberOfLinks; i++)
        if(listOfLinks.links[i].node1.id == Id || listOfLinks.links[i].node2.id == Id)
            return 1;
    return 0;
}

// The purpose of this function is to read the borders, nodes and edges of the map
// If the function worked properly, and all the data has been read correctly, then it will return 1 indicating success
// If the function did not work as intended, it will return 0 indicating an error
const int readFromFile(const char* path){
    FILE* file = fopen(path, "r");
    if(file == NULL){
        printf("File not found!\n");
        return 0;
    }
    static char line[605] ,*arg;
    static double x, y;
    static int a, i=  0;

    extern double maxLat, maxLon, minLat, minLon;
    static int links = 0, nodes = 0;

    //See how many Links are there and store the data of Lat and Lon
    while(fscanf(file, "%[^\n]\n", line) != EOF){
        arg = strtok(line, " =");
        if(!validDataFromFile("<bounding",arg) && i == 0){printf("File has invalid stored data!\n");return 0;}

        if(!strcmp("<bounding", arg)){
            arg = strtok(NULL," =");
            if(!validDataFromFile("minLat",arg)){printf("File has invalid stored data!\n");return 0;}
            arg = strtok(NULL," =");
            if(!inputIsNumber(arg)){printf("File has invalid stored data!\n");return 0;}
            minLat = atof(arg);

            arg = strtok(NULL," =");
            if(!validDataFromFile("minLon",arg)){printf("File has invalid stored data!\n");return 0;}
            arg = strtok(NULL," =");
            if(!inputIsNumber(arg)){return 0;}
            minLon = atof(arg);

            arg = strtok(NULL," =");
            if(!validDataFromFile("maxLat",arg)){printf("File has invalid stored data!\n");return 0;}
            arg = strtok(NULL," =");
            if(!inputIsNumber(arg)){return 0;}
            maxLat = atof(arg);

            arg = strtok(NULL," =");
            if(!validDataFromFile("maxLon",arg)){printf("File has invalid stored data!\n");return 0;}
            arg = strtok(NULL," =");
            if(!inputIsNumber(arg)){printf("File has invalid stored data!\n");return 0;}
            maxLon = atof(arg);

        }
        //else if(!validDataFromFile("<link", arg) && i == 1){
            //return 0;
        //}
        else if(!strcmp("<link", arg)){
            links++;
        }

        else break;
        i++;

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
            if(!validDataFromFile("id",arg)){printf("File has invalid stored data!\n");return 0;}
            arg = strtok(NULL, "= ");
            if(!inputIsNumber(arg)){printf("File has invalid stored data!\n");return 0;}
            listOfLinks.links[links].id = atoi(arg);

            arg = strtok(NULL, "= ");
            if(!validDataFromFile("node",arg)){printf("File has invalid stored data!\n");return 0;}
            arg = strtok(NULL, "= ");
            if(!inputIsNumber(arg)){printf("File has invalid stored data!\n");return 0;}
            listOfLinks.links[links].node1.id = atoi(arg);

            arg = strtok(NULL, "= ");
            if(!validDataFromFile("node",arg)){printf("File has invalid stored data!\n");return 0;}
            arg = strtok(NULL, "= ");
            if(!inputIsNumber(arg)){printf("File has invalid stored data!\n");return 0;}
            listOfLinks.links[links].node2.id = atoi(arg);

            arg = strtok(NULL, "= ");
            arg = strtok(NULL, "= ");
            arg = strtok(NULL, "= ");
            if(!validDataFromFile("length",arg)){printf("File has invalid stored data!\n");return 0;}
            arg = strtok(NULL, "= ");
            if(!inputIsNumber(arg)){printf("File has invalid stored data!\n");return 0;}
            listOfLinks.links[links++].length = atof(arg);
        }

        else if(!strcmp("<node", arg)){
            arg = strtok(NULL, "= ");
            if(!validDataFromFile("id",arg)){printf("File has invalid stored data!\n");return 0;}
            arg = strtok(NULL, "= ");
            if(!inputIsNumber(arg)){printf("File has invalid stored data!\n");return 0;}
            a = atoi(arg);

            arg = strtok(NULL, "= ");
            if(!validDataFromFile("lat",arg)){printf("File has invalid stored data!\n");return 0;}
            arg = strtok(NULL, "= ");
            if(!inputIsNumber(arg)){printf("File has invalid stored data!\n");return 0;}
            x = atof(arg);

            arg = strtok(NULL, "= ");
            if(!validDataFromFile("lon",arg)){printf("File has invalid stored data!\n");return 0;}
            arg = strtok(NULL, "= ");
            if(!inputIsNumber(arg)){printf("File has invalid stored data!\n");return 0;}
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


