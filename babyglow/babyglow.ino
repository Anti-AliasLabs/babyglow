#include <Adafruit_NeoPixel.h>

int ledsPin = 6;
int numLEDs = 3;

int yPin = A3;
int zPin = A5;
int lastYValue;
int lastZValue;

int colors[] = {
  0, 100, 200};
  

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLEDs, ledsPin, NEO_GRB + NEO_KHZ800);


void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  // initialise accelerometers values
  lastYValue = analogRead( yPin );
  lastZValue = analogRead( zPin );

  lastTimerValue = millis();

  rainbow();
  Serial.begin( 9600 );
}

void loop() {
  int yValue;
  int zValue;

  yValue = analogRead( yPin );
  zValue = analogRead( zPin );
  Serial.print( yValue );
  Serial.print( " " );
  Serial.print( zValue );
  Serial.print( " " );

  if( abs(yValue-lastYValue) > 10 ) {
    rainbow(); 
    Serial.print( "sped up" );
  }
  Serial.println();
  lastYValue = yValue;
  lastZValue = zValue;
}

// adapted from function by Adafruit
void rainbow() {
  uint16_t i;

  for(i=0; i<numLEDs; i++) {
    strip.setPixelColor(i, Wheel(colors[i]));
    colors[i] = (colors[i]+1) %256;
    strip.show();
  }
}


// below function by Adafruit
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}





