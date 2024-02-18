#include <iostream>		// Include all needed libraries here
#include <wiringPi.h>

using namespace std;		// No need to keep using std

int r = 1;  // red to GPIO 1
int g = 0;  // green to GPIO 0
int b = 2;	// blue to GPIO 2

int main(){
	wiringPiSetup();			// Setup the library
	
	pinMode(r, OUTPUT);		
	pinMode(g, OUTPUT);	
	pinMode(b, OUTPUT);		
	
	//turn on all led
	digitalWrite(r, 0);
	digitalWrite(g, 0);
	digitalWrite(b, 0);

	// 1 sec. delay
	delay(1000);
	
	//turn off all led
	digitalWrite(r, 1);
	digitalWrite(g, 1);
	digitalWrite(b, 1);

	return 0;
}
