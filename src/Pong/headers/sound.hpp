class sound{
	public:
		sound();
		~sound();
		void play_score();
		void play_wall();
		void play_paddle();
	private:
		Mix_Chunk *score_sound;
		Mix_Chunk *wall_coll_sound;
		Mix_Chunk *paddle_coll_sound;
};

sound::sound(){
	score_sound = Mix_LoadWAV("sounds/score_sound.wav");
	wall_coll_sound = Mix_LoadWAV("sounds/wall_coll_sound.wav");
	paddle_coll_sound = Mix_LoadWAV("sounds/paddle_coll_sound.wav");
	Mix_Volume(-1, 10);
}

void sound::play_score(){
	Mix_PlayChannel(0, score_sound, 0);
}

void sound::play_wall(){
	Mix_PlayChannel(1, wall_coll_sound, 0);
}

void sound::play_paddle(){
	Mix_PlayChannel(2, paddle_coll_sound, 0);
}

sound::~sound(){
	Mix_FreeChunk(score_sound);
	Mix_FreeChunk(wall_coll_sound);
	Mix_FreeChunk(paddle_coll_sound);
}
