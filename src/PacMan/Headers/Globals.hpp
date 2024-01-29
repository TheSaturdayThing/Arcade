const unsigned char BoardWidth = 28;
const unsigned char BoardHeight = 36;
const unsigned char BlockSize32 = 32;
const unsigned char BlockSize24 = 24;
const unsigned short WindowWidth = 1920;
const unsigned short WindowHeight = 1080;

const char CharBoard[] =
	"                            "
	"                            "
	"                            "
	"############################"
	"#............##............#"
	"#.####.#####.##.#####.####.#"
	"#o####.#####.##.#####.####o#"
	"#.####.#####.##.#####.####.#"
	"#..........................#"
	"#.####.##.########.##.####.#"
	"#.####.##.########.##.####.#"
	"#......##....##....##......#"
	"######.##### ## #####.######"
	"     #.##### ## #####.#     "
	"     #.##    1     ##.#     "
	"     #.## ###==### ##.#     "
	"######.## #      # ##.######"
	"      .   #2 3 4 #   .      "
	"######.## #      # ##.######"
	"     #.## ######## ##.#     "
	"     #.##          ##.#     "
	"     #.## ######## ##.#     "
	"######.## ######## ##.######"
	"#............##............#"
	"#.####.#####.##.#####.####.#"
	"#.####.#####.##.#####.####.#"
	"#o..##.......0 .......##..o#"
	"###.##.##.########.##.##.###"
	"###.##.##.########.##.##.###"
	"#......##....##....##......#"
	"#.##########.##.##########.#"
	"#.##########.##.##########.#"
	"#..........................#"
	"############################"
	"                            "
	"                            ";

const unsigned char LivingPacFrames = 3;
const unsigned char DeathPacFrames = 10;
const unsigned char GhostBodyFrames = 6;
const unsigned char GhostEyeFrames = 5;
const unsigned char FruitFrames = 8;

const unsigned short ScoreTable[FruitFrames] = {100, 300, 500, 700, 1000, 2000, 3000, 5000};

const SDL_Color Black = {0x00, 0x00, 0x00};
const SDL_Color White = {0xff, 0xff, 0xff};
const SDL_Color Yellow = {0xff, 0xff, 0x00};
const SDL_Color Red = {0xff, 0x00, 0x00};
const SDL_Color Cyan = {0x00, 192, 0xff};
const SDL_Color Pink = {0xff, 192, 203};
const SDL_Color Orange = {0xff, 128, 0x00};
const SDL_Color SoftColor = {99, 99, 99};

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect* CurrentClip = NULL;
TTF_Font* Font = NULL;
TTF_Font* LittleFont = NULL;
SDL_Joystick* Joystick1 = nullptr;
SDL_Joystick* Joystick2 = nullptr;
const int JOYSTICK_DEAD_ZONE = 8000;

enum BlockType{
	Wall, Door, Pellet, Energizer, Nothing
};

enum Direction{
	Right, Up, Left, Down, Nowhere
};

enum EntityType{
	ePacMan, eBlinky, eInky, ePinky, eClyde, Noone
};

void InitializeSDL(){
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	TTF_Init();
	Font = TTF_OpenFont("Fonts/emulogic.ttf", BlockSize24);
	LittleFont = TTF_OpenFont("Fonts/VpPixel.ttf", 20);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
  if( SDL_NumJoysticks() < 1 ){
    printf( "Warning: No joysticks connected!\n" );
  }
  else{
    Joystick1 = SDL_JoystickOpen(0);
    if(Joystick1 == NULL){
      printf( "Warning: Unable to open game controller 1! SDL Error: %s\n", SDL_GetError() );
    }
    Joystick2 = SDL_JoystickOpen(1);
    if(Joystick2 == NULL){
      printf( "Warning: Unable to open game controller 2! SDL Error: %s\n", SDL_GetError() );
    }
	}
}

void CloseSDL(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	CurrentClip = NULL;
  SDL_JoystickClose(Joystick1);
  Joystick1 = NULL;
  SDL_JoystickClose(Joystick2);
  Joystick2 = NULL;
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

void InitFrames(const unsigned char TotalFrames, SDL_Rect SpriteClips[], unsigned char CurrentBlockSize = BlockSize32){
	unsigned short counter = 0;
	for(unsigned char i = 0; i < TotalFrames; i++){
		SpriteClips[i].x = counter;
		SpriteClips[i].y = 0;
		SpriteClips[i].w = CurrentBlockSize;
		SpriteClips[i].h = CurrentBlockSize;
		counter += CurrentBlockSize;
	}
}
