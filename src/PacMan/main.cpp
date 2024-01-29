#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <cmath>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

#include "Headers/Globals.hpp"
#include "Headers/Texture.hpp"
#include "Headers/Timer.hpp"
#include "Headers/Position.hpp"
#include "Headers/Entity.hpp"
#include "Headers/Pac.hpp"
#include "Headers/Ghost.hpp"
#include "Headers/Blinky.hpp"
#include "Headers/Inky.hpp"
#include "Headers/Pinky.hpp"
#include "Headers/Clyde.hpp"
#include "Headers/Fruit.hpp"
#include "Headers/Board.hpp"
#include "Headers/Sound.hpp"
#include "Headers/Game.hpp"

//Use arrow keys or WASD to move

int main(int argc, char* args[]){

	InitializeSDL();

	Game mGame;
	Timer GameTimer;
	SDL_Event e;
	bool quit = false;
	unsigned short StartTicks = 4500;
	std::vector<unsigned char> mover;
	mover.push_back(Right);
	GameTimer.Start();
  mGame.mSound.PlayIntro();
	LTexture BackGround;
	BackGround.loadFromFile("Textures/back2.png");

	while(!quit){
		
    while( SDL_PollEvent( &e ) != 0 ){
      if( e.type == SDL_QUIT ){
        quit = true;
      }
      if(e.key.state == SDL_PRESSED){
				if((e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d))			mover.push_back(Right);
				else if((e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w)) 		mover.push_back(Up);
				else if((e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a))	mover.push_back(Left);
				else if((e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s))	mover.push_back(Down);
			}
			if(e.type == SDL_JOYBUTTONDOWN){
				if(e.jbutton.which == 0){
					if(e.jbutton.button == 1){
						mover.push_back(Up);
					}
					if(e.jbutton.button == 4){
						mover.push_back(Down);
					}
					if(e.jbutton.button == 3){
						mover.push_back(Left);
					}
					if(e.jbutton.button == 5){
					  mover.push_back(Right);
					}
				}
				if(e.jbutton.which == 1){
					if(e.jbutton.button == 1){
						mover.push_back(Up);
					}
					if(e.jbutton.button == 4){
						mover.push_back(Down);
					}
					if(e.jbutton.button == 3){
						mover.push_back(Left);
					}
					if(e.jbutton.button == 5){
					  mover.push_back(Right);
					}
				}
			}
			if( e.type == SDL_JOYAXISMOTION ){
        if( e.jaxis.which == 0 ){																		//Motion on controller 0
          if( e.jaxis.axis == 0 ){																	//X axis motion
            if( e.jaxis.value < -JOYSTICK_DEAD_ZONE ){							//Left of dead zone
							mover.push_back(Left);
            }
            else if( e.jaxis.value > JOYSTICK_DEAD_ZONE ){					//Right of dead zone
              mover.push_back(Right);
            }
					}
        	else if( e.jaxis.axis == 1 ){																//Y axis motion
          	if( e.jaxis.value < -JOYSTICK_DEAD_ZONE ){								//Below of dead zone
							mover.push_back(Up);
          	}
						else if( e.jaxis.value > JOYSTICK_DEAD_ZONE ){						//Above of dead zone
						  mover.push_back(Down);
          	}
        	}
 				}
 				if( e.jaxis.which == 1 ){																		//Motion on controller 0
          if( e.jaxis.axis == 0 ){																	//X axis motion
            if( e.jaxis.value < -JOYSTICK_DEAD_ZONE ){							//Left of dead zone
							mover.push_back(Left);
            }
            else if( e.jaxis.value > JOYSTICK_DEAD_ZONE ){					//Right of dead zone
              mover.push_back(Right);
            }
					}
        	else if( e.jaxis.axis == 1 ){																//Y axis motion
          	if( e.jaxis.value < -JOYSTICK_DEAD_ZONE ){								//Below of dead zone
							mover.push_back(Up);
          	}
						else if( e.jaxis.value > JOYSTICK_DEAD_ZONE ){						//Above of dead zone
						  mover.push_back(Down);
          	}
        	}
 				}
			}
			if(mover.size() > 2)
				mover.erase(mover.begin() + 1);
    }
          
		double IterationStart = SDL_GetPerformanceCounter();

		SDL_RenderClear(renderer);

		if(mGame.Process(GameTimer, mover, StartTicks)){
			mGame.Draw();
			BackGround.render();
			SDL_RenderPresent(renderer);
		}
		
		double IterationEnd = SDL_GetPerformanceCounter();
		double ElapsedSeconds = (IterationEnd - IterationStart) / (double)SDL_GetPerformanceFrequency();
		double Delay = 13.333f - (ElapsedSeconds * 1000.0f);
		if(Delay > 0)
			SDL_Delay(std::max(0, (int) Delay));

	}
	CloseSDL();
	
	return 0;
	
}



