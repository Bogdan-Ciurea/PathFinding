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

//The type of variable that will store information about a node
typedef struct{
    int id; //The id of the node
    int matrixId; // matrixId is the position of the node in the matrix
    double lat, lon; //The latitude and longitude of the node
}Node;

//The type of variable that will store an edge between the nodes
typedef struct{
    int id; //The id of the link
    double length; // The length/weight of the edge
    Node node1, node2; // The two nodes that the edge connects
}Link;

//The type of variable that will store all the edges
typedef struct{
    int numberOfLinks; // Represents how many edges do we have
    Link *links; // This pointer will store all the edges
}Links;

//The variable that will store all the nodes
typedef struct{
    int numberOfNodes; // Represents how many nodes do we have
    Node *nodes; // This pointer will store all the nodes
}Nodes;

//The variables that will tell the dimensions of the map
double minLat, maxLat, minLon, maxLon;
int width, height;

//The index of the starting node and the finish node that we want to link
int indexStart, indexFinish;

int hasReadNodes;
Nodes listOfNodes; //The list of nodes
Nodes pathOfNodes; //The path of nodes from node x to node y
Links listOfLinks; //The list of edges


/*==============
    Functions
===============*/

// The purpose of this function is to read the borders, nodes and edges of the map
// If the function worked properly, and all the data has been read correctly, then it will return 1 indicating success
// If the function did not work as intended, it will return 0 indicating an error
int readFromFile(char* input);

// The purpose of this function is to show the map of the nodes and edges
// The function will take an integer as a parameter, this representing if the function should also show the path
// If the user has read two points, these two points will be colored black
void showMap(int showPath);

// The purpose of this function is to see if the input is a number or not
// The function will take a char pointer as a parameter
// If the input is a number, the function will return 1
// If the input is not a number, the function will return 0
int inputIsNumber(char* input);

// The purpose of this function is to give the position of a node relative to the window that we render
// The function will take one double value as a parameter, this representing the longitude of the node
// The function will return the integer value of the relative value to the window
int relativePozX(double x);

// The purpose of this function is to give the position of a node relative to the window that we render
// The function will take one double value as a parameter, this representing the latitude of the node
// The function will return the integer value of the relative value to the window
int relativePozY(double y);

// The purpose of this function is to wait a specific number of seconds
// The function will take one float value as a parameter, this representing the seconds we want to wait
// It is an equivalent of time.sleep in python
void wait(float seconds);

//The function that will choose two random nodes from the map if the user does not want to input two points
int randomNodes();

// The purpose of this function is to see if a node has the given coordinates
// The function will take two double variables, representing the x and y coordinates of the supposed node
// If the given coordinates have a corresponding node, the function will return the index if the node the coordinates correspond to
// If the given coordinates do not have a corresponding node, the function will return -1
int nodeInNodes(double x, double y);

// The purpose of this function is to add information to the pathOfNodes from the listOfNodes
// After the path is build, it will only store the id in matrix of each node
// So, we add the information to the pathOfNodes
void completePath();

// The purpose of this function is to find the distance between two nodes that are connected with one edge
// The function will take two integers as parameters. These parameters represent the matrixId.
// If the function worked properly, and the node have an edge connecting them, then it will return the weight of the edge indicating success
// If the function did not work as intended, it will return DBL_MAX indicating an error
double distBetweenNodes(int node1, int node2);

//The function that will get the two points' coordinates
// The purpose of this function is to get the two nodes
// If the function worked properly, and the nodes have been read successfully, then it will return 1 indicating success
// If the function did not work as intended, it will return 0 indicating an error
// The user will be asked to give the coordinates of the nodes
// The function will read the input and validate it (if it is a number)
// If the input is valid the function will try to find the nodes
int getCoordinatesStFin();

// The purpose of this function is to find the shortest path and shortest distance from node x to node y using Dijkstra's Algorithm
// The function will take an integer as a parameter. This value indicates if the user wants to see how the algorithm works
// If the function worked properly, and the path is found, then it will return 1 indicating success
// If the function did not work as intended, it will return 0 indicating an error
// The function will have three steps:
// Step 1: Initialize the predecessor, the distance and the visited matrices
// Step 2: Relax all the edges
// Step 3: Make the path
// If the user chooses to see the animation, during the 2nd step, the visited nodes will be colored in blue and the compared one in green
int dijkstra(int animation);

// The purpose of this function is to find the shortest distance from node x to node y using Bellman-Ford's Algorithm
// If the function worked properly, and the path is found, then it will return 1 indicating success
// If the function did not work as intended, it will return 0 indicating an error
// The function will have three steps:
// Step 1: Initialize distances from the start node to all other nodes
// Step 2: Relax all edges |listOfNodes.numberOfNodes| - 1 times
// Disclaimer!: The function is not meant for find the path so it will just show the distance
int bellmanFord();

#endif
