# Introduction
**This software was made by Bogdan Alexandru Ciurea

University of Leeds

School of Computing

COMP1921 - Programming project

Coursework 2

Student Name: Bogdan Alexandru Ciurea

Student ID: 201438333

Email: sc20bac@leeds.ac.uk**

----

# Table of contents
* [Git repository](#git-repository)
* [The Software](#the-software)
* [Video Presentation](#video-presentation)
* [Git Commit History](#git-commit-history)

# Git repository

SSH: git@gitlab.com:sc20bac/comp1921-cwk2.git

HTTP: https://gitlab.com/sc20bac/comp1921-cwk2.git


# The software

## About the files
The project contains 9 files:
 
```
CMakeLists.txt; Makefile;
main.c; unit_tests.c;
globalFunctions.c; readding.c;
dijkstra.c; bellman_ford.c
sdl_functions.c;
functions.h;
CyberRoads.exe
```

There is also a folder named `assets` that contains the dll files for SDL, the font for SDL_TTF and the map for the project. There should be 7 files:

```
Final_Map.map;
OpenSans.ttf;
libfreetype-6.dll; SDL2.dll; SDL2_image.dll; SDL2_ttf.dll; zlib1.dll
```

Furthermore, there should also be one mode folder named `unity` and two mode files:  `unity.c` and `unity.h`. These files are used for debugging.

On the **Feng Linux** machine that the University provides us with, the software can be built by using these commands: `mkdir build` -> `cd build` -> `cmake ..` -> `make`.
After you have used these commands you have two options. If you want to run the program, you would want to use the `./CyberRoads` command. If you want to use the unit testing program type `./unit_tests` command.

If the software does not work as intended, another way to run the program is to run the `make` command in the main folder and then './CyberRoads' but this would also need to ode all the files from the `assets` folder into the main folder and the `unit_tests` file will not exist.

If you want to run this software on **Windows** you will have to just run the `CyberRoads.exe` file but you would also need to move all the files from the `assets` folder into the main folder. 

<br>

## Drawbacks
In the current state of the program will not make the path between the two points if you use Bellman-Ford algorithm but it will make the shortest path.

If the graph given in the `Final_Map.map` file has a negative weight link, Dijkstra’s algorithm will not work as intended. Also, if there is a negative weight cycle, Bellman-Ford’s Algorithm will also not work properly. 
<br>

## First command
When the program is first launched the user has one option: to type the file's name, in this case `Final_Map.map`.

If the program cannot open the file, it will not proceed to the next commands.
If the file can be opened, then the program will proceed in readding the data and store the nodes' values and links' values. 

If the format is not the same as the initial `Final_Map.map` file, the program will not work and send a `File has invalid stored data! ` message.

<br>

## Main menu

After the file from which we will read the information from has executed correctly, the user will be prompted to select from the following commands:

* [Show Command](#show-command)
* [Read Nodes Command](#read-nodes-command)
* [Random Nodes Command](#random-nodes-command)
* [Show Path Command](#show-path-command)
* [Find Path Command](#find-path-command)
* [Find Distance Command](#find-dostance-command)
* [Exit](#exit-command)
* [Map](#egypt-map)

<br>


## Show Command

After the file has been read, the user can choose to visualize how the map looks.

This command can be accessed by typing `show` into the CMD.


<br>

## Read Nodes Command

If the user wants to see the distance between two points, he needs to insert the coordinates of these two points (_start_ and _end_ points).

This command can be accessed by typing `read nodes` into the CMD.

If the user has chosen to use this command, he will be asked to insert the following information: 

- start Node’s Latitude;

- start Node’s Longitude;

- end Node’s Latitude;

- end Node’s Longitude;

If the coordinates are not the same as the Node in the database, the user will not be able to proceed. Also, if the user inserted invalid characters, he would need to type again the coordinates.

<br>

## Random Nodes Command

If the user does not want to use the `read nodes` command but still wants to select two nodes, he/she is able to use the `random nodes` command to have two randomly selected nodes as the start node and finish node.

<br>


## Show Path Command

If the user wants to see the path between the two pints, he can use the `show path` command in the CMD to re-watch the animation for the path. 

Keep in mind that, if the `find path` command has not been used, the program will inform the user that the `show path` command is not available and will ask to first use the `find path` command.


<br>

## Find Path Command

If the user wants to find the path between the two nodes, he/she can type the `find path` command. After this command has been chosen, the user can choose whether to have an animation of how the program finds the shortest path or not.  Just type `yes` not `not` depending on your preference.

If **yes**, the program will open a window in which the user can visualize how the computer does the algorithm (this process will take a little more time compared to the other option).

If **not**, the program will proceed with finding the shortest path between the two points. **Disclaimer:** the program will open a window for a brief moment but it will be destroyed instantly. 

<br>

## Find Distance Command

If the user just wants to know the distance but not the path between the two nodes, he/she is able to use the `find distance` command. After this, the program will tell the distance.

<br>

## Exit Command

If the user does not want to continue, he can use this command `exit` to exit the program.

## Egypt Map

![](egypt_map.png)

# Video Presentation

![](video_demonstration.mp4)


# Git commit history

![](commits_screenshot.png)
