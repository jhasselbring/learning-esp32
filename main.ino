#include <heltec.h>
#include "esp32-oled/main.c"



// Define Oled
OLED oled;

void setup()
{
    // Enable serial
    Serial.begin(9600);

    // Print to serial
    Serial.println("Booting up.");

    // Initialize and test oled
    oled.init();
    oled.echo("Test v0.1.3");
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
    delay(1000);
}
