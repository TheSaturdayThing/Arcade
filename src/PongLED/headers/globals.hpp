SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
TTF_Font *font = NULL;
SDL_Joystick* JoyStick1 = NULL;
SDL_Joystick* JoyStick2 = NULL;
const int JOYSTICK_DEAD_ZONE = 8000;

int window_width = 1920;
int window_height = 1080;

float font_size = window_width / 50.0f;
float paddle_width = window_width / 100.0f;
float paddle_height = window_height / 7.5f;
float ball_radius = paddle_width / 2.0f;
float global_velocity = window_width / 130.0f;	//240.0

const SDL_Color white = {0xff, 0xff, 0xff};
const SDL_Color black = {0x00, 0x00, 0x00};
const float Pi = 3.14159f;

void draw_pix(int x, int y, SDL_Color color = white){
	uint8_t* pixel_ptr = (uint8_t*)surface->pixels + (y * window_width + x) * 4;
	*(pixel_ptr + 2) = color.r;
	*(pixel_ptr + 1) = color.g;
	*(pixel_ptr) = color.b;
}

void draw_line(int x0, int y0, int x1, int y1, SDL_Color color = white){
  float x = x1 - x0;
	float y = y1 - y0;
	float length = sqrt(x * x + y * y);
	float addx = x / length;
	float addy = y / length;
	x = x0;
	y = y0;
	for(int i = 0; i < length; i++){
		draw_pix((int)x, (int)y, color);
		x += addx;
		y += addy;
	}
}

void draw_ball(int x, int y, SDL_Color color = white, int radius = ball_radius){
	for(int w = 0; w < 2 * radius; w++){
    for(int h = 0; h < 2 * radius ; h++){
      int dx = radius - w;
      int dy = radius - h;
      if((dx * dx + dy * dy) < (radius * radius)){
        draw_pix(x + dx, y - dy, color);
			}
    }
  }
}
#include <iostream>
void InitializeSDL(){
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_SKIP_TASKBAR);
	surface = SDL_GetWindowSurface(window);
	TTF_Init();
	font = TTF_OpenFont("font/pixelated.ttf", (int)(font_size * 2.0f));
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	if( SDL_NumJoysticks() < 1 ){
		std::cout << SDL_NumJoysticks() << "\n";
    printf( "Warning: No joysticks connected!\n" );
  }
  else{
  	JoyStick1 = SDL_JoystickOpen(0);
    if(JoyStick1 == NULL){
      printf( "Warning: Unable to open game controller 1 ! SDL Error: %s\n", SDL_GetError() );
    }
    JoyStick2 = SDL_JoystickOpen(1);
    if(JoyStick2 == NULL){
      printf( "Warning: Unable to open game controller 2 ! SDL Error: %s\n", SDL_GetError() );
    }
	}
}

void CloseSDL(){
	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);
	SDL_JoystickClose(JoyStick1);
	SDL_JoystickClose(JoyStick2);
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}
