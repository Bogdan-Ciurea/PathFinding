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

//The struct that will store a link between the nodes
typedef struct{
    int id, node1Id, node2Id;
    double length;

    double node1Lat, node1Lon, node2Lat, node2Lon;

    //int wayId, poi;
    //float veg, arch, land;
}Link;


//A struct that will store information about a node
typedef struct{
    int id;
    double lat, lon;
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

//A function that adds the coordinates of the ends of a Link
int completeLinks();

int relativePozX(double y);
int relativePozY(double x);

//A function that will show the map on the points
void showMap();
#endif
