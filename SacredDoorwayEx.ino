#include <Adafruit_NeoPixel.h>

/*
 * The 'strip' is composed of 419 (it should have been 420, but it's the last led so who cares)
 * LEDs with daisy chained segments. Which can make addressing a specific sheet a little intense.
 *
 * Basically the first 30 LEDs are the front left side of the first sheet and the last 29 are the front right side.
 * Meaning that to address the first led of the front right side you would need to address its offset 
 * from the last LED of the front left side (which should be 389, i.e, 389+1 would be the first LED for the front
 * sheet on the right side.
 
 * Diagram to show the directional flow of data. 
 *
 *        Left                      Right
 *       -->     -->     -->        -->     -->     -->
 *  1  60  61  120 150 180 210    240 270 300 330 360 390 419
 *  |   |   |   |   |   |   |      |   |   |   |   |   |   |
 *  |   |   |   |   |   |   |      |   |   |   |   |   |   |
 *  v   ^   v   ^   v   ^   v      ^   v   ^   v   ^   v   ^
 *  |   |   |   |   |   |   |      |   |   |   |   |   |   |
 *  |   |   |   |   |   |   |      |   |   |   |   |   |   |
 * 30  31  90  91  121 151 181    211 241 271 301 331 361 391
 *   -->     -->     -->     -->>--     -->     -->     -->
 *
 * Make sense? Good. I'll get some constructors defined for each sheet
 * so you'll just be able to say sheet1.set(4) or sheet5.set(10) to handle the offsets.
 *
 * The remainder of the code was ganked out of the strandtest library and just 
 * does a cascading rainbow over the entire strip.
 *
 * These LEDs are full color (so yeah, you can do pink).
 */

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(419, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  rainbow(10);
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

