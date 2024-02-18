

class Timer{
public:
	Timer();
	~Timer();
	void Start();
	void Stop();
	void Pause();
	void Unpause();
	uint32_t GetTicks();
	bool IsStarted();
	bool IsPaused();
private:
	uint32_t StartTicks;	//The clock time when the timer started
	uint32_t PausedTicks;	//The ticks stored when the timer was paused
	bool Paused;
	bool Started;
};


Timer::Timer() :
    StartTicks(0),
    PausedTicks(0),
    Paused(false),
    Started(false)
{

}

Timer::~Timer(){

}

void Timer::Start(){
    //Start the timer
    Started = true;

    //Unpause the timer
    Paused = false;

    //Get the current clock time
    StartTicks = SDL_GetTicks();
    PausedTicks = 0;
}

void Timer::Stop(){
    //Stop the timer
    Started = false;

    //Unpause the timer
    Paused = false;

    //Clear tick variables
    StartTicks = 0;
    PausedTicks = 0;
}

void Timer::Pause(){
    //If the timer is running and isn't already paused
    if (Started && !Paused)
    {
        //Pause the timer
        Paused = true;

        //Calculate the paused ticks
        PausedTicks = SDL_GetTicks() - StartTicks;
        StartTicks = 0;
    }
}

void Timer::Unpause(){
    //If the timer is running and paused
    if (Started && Paused)
    {
        //Unpause the timer
        Paused = false;

        //Reset the starting ticks
        StartTicks = SDL_GetTicks() - PausedTicks;

        //Reset the paused ticks
        PausedTicks = 0;
    }
}

uint32_t Timer::GetTicks(){
    //The actual timer time
    uint32_t time = 0;

    //If the timer is running
    if (Started)
    {
        //If the timer is paused
        if (Paused)
        {
            //Return the number of ticks when the timer was paused
            time = PausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - StartTicks;
        }
    }

    return time;
}

bool Timer::IsStarted(){
    //Timer is running and paused or unpaused
    return Started;
}

bool Timer::IsPaused(){
    //Timer is running and paused
    return Paused && Started;
}
