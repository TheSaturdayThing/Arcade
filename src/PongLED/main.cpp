#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <wiringPi.h>

#include <cmath>
#include <ctime>
#include <sstream>

#include "headers/globals.hpp"
#include "headers/vec2.hpp"
#include "headers/paddle.hpp"
#include "headers/ball.hpp"
#include "headers/sound.hpp"
#include "headers/game.hpp"



int main(int argc, char* argv[]){
	
	srand(time(NULL));
	
	InitializeSDL();

	wiringPiSetup();			// Setup the library
	
	pinMode(1, OUTPUT);		
	pinMode(0, OUTPUT);	
	pinMode(2, OUTPUT);		
	
	digitalWrite(1, 0);
	digitalWrite(0, 1);
	digitalWrite(2, 0);
	SDL_Event event;
	bool Movers[4] = {false, false, false, false};
		bool IsOver = false;
	bool IsToRestart = false;
	game pong(Movers, &IsToRestart, &IsOver);
	bool quit = false;
	bool is_paused = false;


	while (!quit){
		
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT)
				quit = true;
				//left paddle: Q up, A down
				//right paddle: E up, D down
				if (event.key.state == SDL_PRESSED) {
					switch (event.key.keysym.sym) {
						case SDLK_q:
							Movers[0] = true;
							break;
						case SDLK_a:
							Movers[1] = true;
							break;
						case SDLK_e:
							Movers[2] = true;
							break;
						case SDLK_d:
							Movers[3] = true;
							break;
						case SDLK_ESCAPE:
							quit = true;
							case SDLK_SPACE:
							if(IsOver){
									IsToRestart = true;
									IsOver = false;
								}
							break;
						default:
							break;
					}
				}
				if (event.key.state == SDL_RELEASED) {
					switch (event.key.keysym.sym) {
						case SDLK_q:
							Movers[0] = false;
							break;
						case SDLK_a:
							Movers[1] = false;
							break;
						case SDLK_e:
							Movers[2] = false;
							break;
						case SDLK_d:
							Movers[3] = false;
							break;
						default:
							break;
					}
				}
				if (event.type == SDL_JOYBUTTONDOWN) {
					if (event.jbutton.which == 0) {
						switch (event.jbutton.button) {
							case 0:
								if(IsOver){
									IsToRestart = true;
									IsOver = false;
								}
								break;
							default:
								break;
						}
					}
					if (event.jbutton.which == 1) {
						switch (event.jbutton.button) {
							case 0:
								if(IsOver){
									IsToRestart = true;
									IsOver = false;
								}
								break;
							default:
								break;
						}
					}
				}

			if( event.type == SDL_JOYAXISMOTION ){
		      if( event.jaxis.which == 0 ){																		//Motion on controller 0
		      	if( event.jaxis.axis == 0 ){																	//X axis motion
					}
		      if( event.jaxis.axis == 1 ){																//Y axis motion
		       	if( event.jaxis.value < -JOYSTICK_DEAD_ZONE ){
							Movers[0] = true;
							Movers[1] = false;
		      		}
						else if( event.jaxis.value > JOYSTICK_DEAD_ZONE ){						//Above of dead zone
							Movers[1] = true;
							Movers[0] = false;
		          		}
		          		if( event.jaxis.value == -256){
							Movers[0] = false;
							Movers[1] = false;
		          		}
		        	}
		 		}
		 		if( event.jaxis.which == 1 ){
				 																		//Motion on controller 1
		    	    if( event.jaxis.axis == 0 ){																	//X axis motion
					}
		      		if( event.jaxis.axis == 1 ){																//Y axis motion
		          		if( event.jaxis.value < -JOYSTICK_DEAD_ZONE ){
						Movers[2] = true;
						Movers[3] = false;
		          	}
					else if( event.jaxis.value > JOYSTICK_DEAD_ZONE ){						//Above of dead zone
					Movers[3] = true;
					Movers[2] = false;
		          	}
		          	if( event.jaxis.value == -256){
							Movers[2] = false;
							Movers[3] = false;
		          		}
		        	}
		 		}
			}
		}
		
		pong.cycle(is_paused);
		
	}
	
	CloseSDL();
	
	return 0;

}
