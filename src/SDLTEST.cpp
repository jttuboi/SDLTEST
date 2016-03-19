#include <SDL.h>
#include <stdio.h>


const int TELA_LARGURA = 640;
const int TELA_ALTURA = 480;

bool inicializaSDL();
bool carregaDados();
void executaJogo();
void finalizaSDL();

SDL_Window* gWindow = NULL; //The window we'll be rendering to
SDL_Surface* gScreenSurface = NULL; //The surface contained by the window
SDL_Surface* gHelloWorld = NULL; //The image we will load and show on the screen

int main(int argc, char* args[]) {
	if (!inicializaSDL()) {
		printf("Falha ao inicializar!\n");
		return -1;
	}

	if (!carregaDados()) {
		printf("Falha ao carregar dados!\n");
		return -1;
	}

	executaJogo();

	finalizaSDL();
	return 0;
}

bool inicializaSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL nao pode ser inicializado! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("JOGOOOO!!!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, TELA_LARGURA, TELA_ALTURA, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		printf("Window nao pode ser criado! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	gScreenSurface = SDL_GetWindowSurface(gWindow);

	return true;
}

bool carregaDados() {
	const char* imagemHelloWorld = "imagem/hello_world.bmp";

	gHelloWorld = SDL_LoadBMP(imagemHelloWorld);

	if (gHelloWorld == NULL) {
		printf("Falha ao carregar a imagem em %s! SDL Error: %s\n", imagemHelloWorld, SDL_GetError());
		return false;
	}

	return true;
}

void executaJogo() {
	SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

	SDL_UpdateWindowSurface(gWindow);

	SDL_Delay(2000);
}

void finalizaSDL() {
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}
