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
int width, height;
int indexStart, indexFinish;
Nodes listOfNodes;
Nodes pathOfNodes;
Links listOfLinks;


/*==============
    Functions
===============*/

//A function that will read the data from the file
int readFromFile(char* input);

//A function that will show the map on the points
void showMap(int showPath);

int inputIsNumber(char* input);

//Shows the relative position to the window that we want to show
int relativePozY(double y);
int relativePozX(double x);

//Equivalent of time.sleep() in python it is used for making an animation
void wait(float seconds);

//Completes adds the rest of the information to the path
void completePath();

//A function that will return the distance between two nodes
double distBetweenNodes(int node1, int node2);

//A function that will get the two points' coordinates
int getCoordinatesStFin();

//The function that will make Dijkstra's algorithm and show the process
int dijkstra(int animation);
int bellmanFord();

#endif
