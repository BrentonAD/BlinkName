void blinkLed(pin_t, int);
void morseBlink(const char*, int, pin_t);

// Define configuration variables
const pin_t MY_LED = D7;
const int MORSE_TIMING = 200;

const char *MY_NAME = "-... .-. . -. - --- -.";

SYSTEM_THREAD(ENABLED);

// The setup() method is called once when the device boots.
void setup()
{
	pinMode(MY_LED, OUTPUT);
}

void loop()
{
	morseBlink(MY_NAME, MORSE_TIMING, MY_LED);
}

void blinkLed(pin_t pin, int blinkDuration) {
    // Turn on the LED
	digitalWrite(pin, HIGH);

	// Leave it on for specified time
	delay(blinkDuration);

	// Turn it off
	digitalWrite(pin, LOW);

}

void morseBlink(const char* morseCode, int morseTiming, pin_t pin)
{
    int i;
    int passageLen = strlen(morseCode);
    
    // Loop through morse code string, either calling blink function or waiting the appropriate time
    for (i = 0; i < passageLen; i++)
    {
        if (morseCode[i] == '.'){
            // Blink Short (1 unit)
            blinkLed(pin, morseTiming);
            delay(morseTiming);
        }
        else if(morseCode[i] == '-') {
            // Blink Long (3 units)
            blinkLed(pin, 3*morseTiming);
            delay(morseTiming);            
        }
        else if(morseCode[i] == ' ') {
            // Delay Short (3-1=2 units)
            delay(2*morseTiming);
        }
        else if(morseCode[i] == '/'){
            // Delay Long (7-1=6 units)
            delay(6*morseTiming);
        }
        else {
            // Invalid input
            exit(EXIT_FAILURE);
        }
    }
}