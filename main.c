/************************************************************************
    University of Leeds
    School of Computing
    COMP1921 - Programming project
    Coursework 2
    File: Main.c
    Student Name: Bogdan Alexandru Ciurea
    Student ID: 201438333
    Email: sc20bac@leeds.ac.uk
    Date Work Commenced: 3rd Mar 2021
*************************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"


int tryToOpenFile(char * text){
	FILE *file = fopen(text, "r");
	fclose(file);
	if(file == NULL)
		return 0;
	else
		return 1;
}

void showAvailableCommands(int start){
    if(start){
    printf("You have the following commands:\n1) 'show' - to show the map\n2) 'read nodes' - to read the Start and Finish nodes\n");
    printf("3) 'show path' - to view the shortest path | You first have to use an algorithm!\n");
    printf("4) 'dijkstra' - to visualize Dijkstra's algorithm | You first have to read the two points\n");
    printf("5) 'bellman-ford' - to visualize Bellman-Ford algorithm | You first have to read the two points\n");
    printf("6) 'exit' - to exit the program\n");
    printf("Keep in mind that, for every algorithm, the distance will be showed in the CMD as well as the path\nThe path will also be displayed visually.\n");
    }
    else{
    printf("You have the following commands:\n1) 'show' - to show the map\n2) 'read nodes' - to read the Start and Finish nodes\n");
    printf("3) 'show path' - to view the shortest path\n");
    printf("4) 'dijkstra' - to visualize Dijkstra's algorithm\n");
    printf("5) 'bellman-ford' - to visualize Bellman-Ford algorithm\n");
    printf("6) 'exit' - to exit the program\n");
    }
}


int main(void){

	printf("===============\n");
	printf("Hello\n===============\n\n");

	char path[50];
	int a, answer;


	//Reading the input for the file.
	printf("Type the name of the file you want to open.\nBe careful to also type the extension of the file.\n");
	printf("You can also type exit to end the program!\n");

	do{
        printf("\n>>>"); scanf(" %[^\n]", path);
        if(!strcmp(path, "exit"))
			exit(1);
        a = tryToOpenFile(path);
	}while(!a);


	if(readFromFile(path))
		printf("File successfully read.\n");


    int hasMadeAPath = 0, hasReadNodes = 0;



    showAvailableCommands(1);


    while(1){
        printf("\n>>>");
        scanf(" %[^\n]", path);
        if(!strcmp("exit", path))
            exit(1);
        else if(!strcmp("show", path)){
            showMap(0);
        }
        else if(!strcmp("read nodes", path)){
            if(getCoordinatesStFin())
                hasReadNodes = 1;
            else
                printf("Error while reading the nodes.\n");

        }
        else if(!strcmp("show path", path)){
            if(hasMadeAPath){
                showMap(1);
            }
            else{
                printf("You first need to chose an algorithm before showing the path.\n");
            }
        }
        else if(!strcmp("dijkstra", path)){
            if(hasReadNodes){

                printf("This algorithm has an animation that will show how it works.\nDo you want to use this option? (yes/no)\n");
                do{
                    printf("\n>>>");scanf(" %[^\n]", path);
                    if(strcmp(path, "yes") == 0)
                        answer = 1;
                    else if(strcmp(path, "no") == 0)
                        answer = 0;
                    else{
                        printf("Unrecognised command!\n");
                        answer = -1;
                    }

                }while(answer == -1);

                printf("Loading...\n");
                if(dijkstra(answer))
                   hasMadeAPath = 1;
                else
                    printf("Error while applying Dijkstra.\n");
            }
            else
                printf("You first have to read the Start and Finish nodes.\n");

        }
        else if(!strcmp("bellman-ford", path)){
            if(hasReadNodes){
                hasMadeAPath = 1;
            }
            else
                printf("You first have to read the Start and Finish nodes.\n");;
        }
        else
            printf("Unrecognised command!\n");
        printf("\n");showAvailableCommands(0);

    }

	return 0;
}
