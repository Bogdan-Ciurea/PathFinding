# Introduction
This software was made by Bogdan Alexandru Ciurea Alexandru

University of Leeds

School of Computing

COMP1921 - Programming project

Coursework 2

Student Name: Bogdan Alexandru Ciurea

Student ID: 201438333

Email: sc20bac@leeds.ac.uk

----

## About the files
The project contains 8 files:
 
```
Makefile;
Final_Map.map
main.c; Djikstra.c; globalFunctions.c; readding.c; SDLFunctions;
functions.h
```

<br>

## First command
When the program is first launched the user has one option: to type the file's name, in this case `Final_Map.map`.

If the program cannot open the file, it will not proceed to the next commands.
If the file can be opend, then the program will proceed in readding the data and store the nodes' values and links' values. 

<br>

## Main menu

After the file from which we will read the information from has executed corectly, the user will be prompted to select from the following commands:

* [Show Command](#show-command)
* [Read Nodes Command](#read-nodes-command)
* [Show Path Command](#show-path-command)
* [The Algorithms](#the-algorithms)
* [Exit](#exit-command)

<br>


## Show Command

After the file has been read, the user can chose to visualize how the map looks.

This command can be accessed by typeing `show` into the CMD.


<br>

## Read Nodes Command

If the user wants to see the distance between two points, he needs to insert the coordinates of these two points (_start_ and _end_ points ).

This command can be accessed by typeing `read nodes` into the CMD.

If the user has chosen to use this command, he will be asked to insert the following information: 

- startNode's Latitude ;

- startNode's Longitude;

- endNode's Latitude;

- endNode's Longitude;

If the coordinates are not exactly the same as the Node in the database, the user will not be able to proceed. Also, if the user inserted invalid characters, he will need to type again the coordinates.

<br>

## Show Path Command

If the user wants to see the path between the two pints, he is able to use the `show path` command in the CMD in order to rewatch the animation for the path. 

Keep in mind that, if one of the algorithms has not been used, the program will inform the user that the `show path` command is not available and will ask to first use an algorithm.


<br>

## The Algorithms

There are a couple of algorithms that the user will be able to chose from:
    - Dijkstra's algorithm;
    - Bellman-Ford algorithm;
He can chose of o these by typeing `dijkstra` or `bellman-ford` respectively in the CMD. 
After the user has chosen an algorithm, another information will be required: if an animation of the algorithm wants to be shown.

If **yes**, the program will open a window in which the user can visualize how the computer does the algorithm (this process will take a little more time compared to the other option).

If **not**, the program will purcede with finding the shortest path between the two points.

<br>

## Exit Command

If the user does not want to continue, he can use this command `exit` to exit the program.
