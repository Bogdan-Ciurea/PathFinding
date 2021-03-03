#include <SDL.h>
#include <stdio.h>
int main(void){
    SDL_Init(SDL_INIT_VIDEO);
	printf("Initialize succesful!\n");
	SDL_Quit();
	return 0;
}
