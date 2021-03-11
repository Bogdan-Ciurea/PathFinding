/************************************************************************
    University of Leeds
    School of Computing
    COMP1921 - Programming project
    Coursework 2
    File: functions.h
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

//A struct that will store information about a node
typedef struct{
    int id, matrixId;
    double lat, lon;
}Node;

//The struct that will store a link between the nodes
typedef struct{
    int id;
    double length;
    Node node1, node2;
}Link;

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
int indexStart, indexFinish;
Nodes listOfNodes;
Nodes pathOfNodes;
Links listOfLinks;

//Variables for drawing the image
const float scaler;
const int width ;
const int mapWidth;
const int height;
const int mapHeight;
const int distToBoxWidth;
const int distToBoxHeight;
const int distFromBoxWidth;
const int distFromBoxHeight;
const int smallLine;
const int distBetweenLinesBot;
const int distBetweenLinesLeft;
const int boxWidth;
const int boxHeight;

/*==============
    Functions
===============*/

//A function that will read the data from the file
int readFromFile(char* input);

//A function that will show the map on the points
void showMap(int showPath);

//Shows the relative position to the window that we want to show
int relativePozY(double y);
int relativePozX(double x);

//A function that will get the two points' coordinates
int getCoordinatesStFin();

//The function that will make Dijkstra's algorithm and show the process
int dijkstra();

#endif
