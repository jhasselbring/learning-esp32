#include <heltec.h>
#include "WiFi.h"
#include "esp_sleep.h"
#include <HTTPClient.h>

// Custom wraper libs
#include "esp32-oled/main.c"
#include "esp32-time/main.c"

#define MYLED 25

// Define classes
OLED oled;
Time t;

String serverPath = "https://api.ipify.org/?format=string";
String version = "Test v0.1.24";

void setup()
{
    // Enable serial
    Serial.begin(9600);

    // Enable OLED
    oled.init();

    // Print to serial
    Serial.println("Booting up.");
    Serial.println(version);

    // Initialize and test oled
    oled.echo(version);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        oled.echo("Connecting to WiFi..");
    }

    oled.echo("Connected to the WiFi network");
    Serial.println(WiFi.localIP());

    // Initialize for white LED
    pinMode(MYLED, OUTPUT);
    digitalWrite(MYLED, LOW);
}

void loop()
{

    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;

        // Your Domain name with URL path or IP address with path
        http.begin(serverPath.c_str());

        // Send HTTP GET request
        int httpResponseCode = http.GET();

        if (httpResponseCode > 0)
        {
            Serial.println("HTTP Response code: " + httpResponseCode);
            String payload = http.getString();
            Serial.println(payload);
            oled.echo(payload);
        }
        else
        {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }
        // Free resources
        http.end();
    }
    else
    {
        Serial.println("WiFi Disconnected");
    }
    ledSleep();
}

void ledSleep()
{
    // Toggle LED every cycle
    digitalWrite(MYLED, !digitalRead(MYLED));
    delay(t.mSeconds(3)); // Let the LED light up for 3 seconds
    esp_deep_sleep(t.uSeconds(30));
}