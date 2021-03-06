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
#include "globalFunctions.h"

int tryToOpenFile(char * text){
	FILE *file = fopen(text, "r");
	fclose(file);
	if(file == NULL)
		return 0;
	else
		return 1;
}

int main(void){

	printf("===============\n");
	printf("Hello\n===============\n\n");

	char path[50];

	printf("Type the name of the file you want to open.\nBe carefull to also type the extension of the file.\n");
	printf("You can also type exit to end the program!\n");
	printf(">>>");
	scanf(" %[^\n]", path);
	int a = tryToOpenFile(path); //bool
	if(!strcmp(path, "exit"))
		exit(1);
	while(!a){
		printf("File not found! Try again.\n");
		printf(">>>");
		scanf(" %[^\n]", path);
		a = tryToOpenFile(path);
		if(!strcmp(path, "exit"))
			exit(1);
	}
	if(readFromFile(path))
		printf("File succesfully read.\n");

	printf("Linking points...\n");

	if(linkPoints())
		printf("Points linked succesfully.\n");
	else
		printf("Error while linking the points!\n");

	showMap();
	scanf(" %[^\n]", path);
	return 0;
}
