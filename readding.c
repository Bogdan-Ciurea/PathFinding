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

int readFromFile(char* path){
    FILE* file = fopen(path, "r");
    char line[604] ,*arg;;

    extern double maxLat, maxLon, minLat, minLon;
    int links = 0, nodes = 0;
    
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
        else if(!strcmp("<node", arg))
            nodes++;
        else break;
        /*if(!strcmp("<way", arg))
            way++;
        else if(!strcmp("<geom", arg))
            geom++;*/
    }
    fclose(file);
    
    

    extern Links listOfLinks;
    listOfLinks.numberOfLinks = links;
    listOfLinks.links = calloc(links, sizeof(Link));
    links = 0;
    
    extern Nodes listOfNodes;
    listOfNodes.numberOfNodes = nodes;
    listOfNodes.nodes = calloc(nodes, sizeof(Node));
    nodes = 0;

    

    file = fopen(path, "r");
    while(fscanf(file, "%[^\n]\n", line) != EOF){
        arg = strtok(line, " ");
        if(!strcmp("<bounding", arg)){

        }
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
            listOfNodes.nodes[nodes].id = atoi(arg);

            arg = strtok(NULL, "= ");
            arg = strtok(NULL, "= ");
            listOfNodes.nodes[nodes].lat = atof(arg);

            arg = strtok(NULL, "= ");
            arg = strtok(NULL, "= ");
            listOfNodes.nodes[nodes++].lon = atof(arg);
        }
        else break;
    }

    fclose(file);
    return 1;
}

int linkPoints(){
    extern Links listOfLinks;
    extern Nodes listOfNodes;
    int i, j, s;

    for(i = 0; i < listOfNodes.numberOfNodes; i++){
        s = 0;
        for(j = 0; j < listOfLinks.numberOfLinks; j++)
            if(listOfLinks.links[j].node1Id == listOfNodes.nodes[i].id || listOfLinks.links[j].node2Id == listOfNodes.nodes[i].id)
                s++;
        
        listOfNodes.nodes[i].numberOfNextNodes = s;
        listOfNodes.nodes[i].nextNodes = calloc(s, sizeof(NextNode));
        s = 0;

        for(j = 0; j < listOfLinks.numberOfLinks; j++)
            if(listOfLinks.links[j].node1Id == listOfNodes.nodes[i].id){
                listOfNodes.nodes[i].nextNodes[s].Id = listOfLinks.links[j].node2Id;
                listOfNodes.nodes[i].nextNodes[s++].length = listOfLinks.links[j].length;
            }
            else if(listOfLinks.links[j].node2Id == listOfNodes.nodes[i].id){
                listOfNodes.nodes[i].nextNodes[s].Id = listOfLinks.links[j].node1Id;
                listOfNodes.nodes[i].nextNodes[s++].length = listOfLinks.links[j].length;
            }
    }

    return 1;

}