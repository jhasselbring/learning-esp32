#include <heltec.h>
#include "esp_sleep.h"
#include "esp32-oled/main.c"
#include "esp32-time/main.c"


#define MYLED 25
#define SPEED 1000

// Define classes
OLED oled;
Time t;

void setup()
{
    // Enable serial
    Serial.begin(9600);

    // Print to serial
    Serial.println("Booting up.");

    // Initialize and test oled
    oled.init();
    oled.echo("Test v0.1.9");

    // Initialize for white LED
    pinMode(MYLED, OUTPUT);
    digitalWrite(MYLED, LOW);
}

// Used by filler
int loopCounter = 0;

// Just a filler logic
void filler()
{
    String newString = "Loop: ";
    newString += loopCounter;
    Serial.println(newString);
    loopCounter = loopCounter + 1;
}

void loop()
{
    filler();

    // Toggle LED every cycle
    digitalWrite(MYLED, !digitalRead(MYLED));
    delay(t.mSeconds(3));
}
