#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>

#define MOV 1

typedef struct{

 	int x;
 	int y;
}
Model;

void call_render(SDL_Renderer*, Model*);

int call_events(Model*);

int main(int argc, char **argv){

	int flag;

	Model model;

	model.x = 100;
	model.y = 100;

	SDL_Window *window;
	SDL_Renderer *renderer;
	
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Titulo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_BORDERLESS);

	if(!window){

		printf("Erro ao criar janela! %s", SDL_GetError());
		SDL_Quit();
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(!renderer){

		printf("Erro ao cirar renderizacao! %s", SDL_GetError());
		SDL_Quit();
		exit(1);
	}

	SDL_Event event;

	flag = 0;

	while(!flag){

		flag = call_events(&model);

		call_render(renderer, &model);
		
		SDL_Delay(1);
	}

	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}

void call_render(SDL_Renderer *renderer, Model *model){

	SDL_Rect rect;

	rect.x = model->x;
	rect.y = model->y;
	rect.w = 60;
	rect.h = 60;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &rect);

	SDL_RenderPresent(renderer);
}

int call_events(Model *model){

	int flag = 0;

	SDL_Event event;

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	printf("%d", SDL_GetKeyboardState);

	while(SDL_PollEvent(&event)){

		if(event.key.keysym.sym == SDLK_ESCAPE){

			flag = 1;
		}
	}

	if(state[SDL_SCANCODE_LEFT]){
   			
   		model->x -= MOV;
	}

	if(state[SDL_SCANCODE_RIGHT]){
   			
   		model->x += MOV;
	}

	if(state[SDL_SCANCODE_UP]){
   			
   		model->y -= MOV;
	}

	if(state[SDL_SCANCODE_DOWN]){
   			
   		model->y += MOV;
	}

	return flag;
}