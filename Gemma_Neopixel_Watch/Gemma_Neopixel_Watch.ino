// This project is a bling bling smart watch made with Arduino Gemma and NeoPixel.
// For simplicity and lightness, we do not include an RTC or GPS module.
// Basically we set time manually when uploading the sketch and we use
// a LiPo battery to power it. (I used a 3.7V, 500mAh LiPo battery)
// To start, install Arduino Gemma driver and use USB 2.0 for USB connection.
// Modify the current hour and minute and upload this sketch.
// The watch will be up and running :)

#include <Adafruit_NeoPixel.h>

#define N_LEDS 12
#define PIN    0

// Increase Brightness
#define SWITCH 0

// Decrease Brightness
#define SWITCH2 2

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// Initialize the current time here!
int hours = 8;
int minutes = 22;
int seconds = 0;

// Specify the level of brightness
int partialBrightness = 7;

void setup() {
  // initialize the SWITCH pins as inputs.
  pinMode(SWITCH, INPUT);
  pinMode(SWITCH2, INPUT);
  // ...with a pullup
  digitalWrite(SWITCH, HIGH);
  digitalWrite(SWITCH2, HIGH);
  strip.begin();
}

void loop() {
  seconds++;
  delay(1000);
  
  if (seconds == 60) {
    seconds = 0;
    minutes++;
  }
  if (minutes == 60) {
    minutes = 0;
    hours++;
  }
  if (hours == 13) {
    hours = 1;
  }

  // Use different colors for different hands
  uint32_t white  = strip.Color(partialBrightness, partialBrightness, partialBrightness);
  uint32_t purple  = strip.Color(partialBrightness, partialBrightness / 3, partialBrightness);
  uint32_t blue = strip.Color(0, 0, partialBrightness) ;

  strip.setPixelColor(hours, white);
  // Match minutes to the nearest one out of the 12 positions.
  // Basically 9:23 will be shown as if it is 9:25
  strip.setPixelColor((minutes+2) / 5, purple);
  strip.setPixelColor(seconds % 12, blue);
  strip.show();
  strip.clear();
}

