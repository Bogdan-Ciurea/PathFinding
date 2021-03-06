/************************************************************************
    University of Leeds
    School of Computing
    COMP1921 - Programming project
    Coursework 2
    File: globalFunctions.h
    Student Name: Bogdan Alexandru Ciurea
    Student ID: 201438333
    Email: sc20bac@leeds.ac.uk
    Date Work Commenced: 3rd Mar 2021
*************************************************************************/

#ifndef globalFunctions_h
#define globalFunctions_h

/*==============
    Variables
===============*/

//The variable that will store a link between thw nodes
typedef struct{
    int id, node1Id, node2Id;
    float length;

    //int wayId, poi;
    //float veg, arch, land;
}Link;

//A variable that will store the next possible nodes from anoter node
typedef struct{
    int Id;
    float length;
}NextNode;

//A variable that will store information about a node
typedef struct{
    int id;
    float lat, lon;
    NextNode *nextNodes;
    int numberOfNextNodes;
}Node;

//The variable that will store all the links
typedef struct{
    int numberOfLinks;
    Link *links;
}Links;

//The variable that will store all the nodes
typedef struct{
    int numberOfNodes;
    Node *nodes;
}Nodes;

/*
typedef struct{
    int id;
    int nodes, *nodeId;
}Way;

typedef struct{
    int id;
    int nodes, *nodeId;
}Geom;
*/

double minLat, maxLat, minLon, maxLon;
Nodes listOfNodes;
Links listOfLinks;

/*==============
    Functions
===============*/
//A function that will read the data from the file
int readFromFile(char* input);

//A function that will transform the read data into an easier to process information
int linkPoints();

//A function that will show the map on the points
void showMap();
#endif
