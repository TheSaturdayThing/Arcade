#include <bits/stdc++.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;

int main(int argc, char* args[]){

	int InitSDL = SDL_Init(SDL_INIT_EVERYTHING);
	if(InitSDL != 0)
		cout << "Couldn't initialize SDL!\n";
	int InitIMG = IMG_Init(IMG_INIT_PNG);
	if(InitIMG == 0)
		cout << "Couldn't initialize IMG!\n";
	int InitTTF = TTF_Init();
	if(InitTTF != 0)
		cout << "Couldn't initialize TTF!\n";
  if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );

		
	SDL_Window* Window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);
	SDL_Renderer* Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Event Event;
	bool Quit = false;
	Mix_Volume(-1, 5);
	
	while(!Quit){
    while(SDL_PollEvent( &Event ) != 0){
      if(Event.type == SDL_QUIT){
        Quit = true;
			}
			if (Event.key.state == SDL_PRESSED) {
				switch (Event.key.keysym.sym) {
					case SDLK_ESCAPE:
						Quit = true;
						break;
					default:
						break;
				}
			}
		}
		SDL_RenderPresent(Renderer);
		SDL_Delay(100);
	}
	
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
	
}

