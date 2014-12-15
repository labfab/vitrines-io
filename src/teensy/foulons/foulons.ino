#include <OctoWS2811.h>

const int ledsPerStrip = 119;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

#define RGB(r, g, b) (((r) << 16) | ((g) << 8) | (b))

const unsigned int Color[9] = {
  RGB(0,255,0),
  RGB(32,200,0),
  RGB(64,150,0),
  RGB(255,100,0),
  RGB(0,255,0),
  RGB(32,200,0),
  RGB(64,150,0),
  RGB(32,200,0),
  RGB(32,200,0)
  };

  const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

void setup() {
  pinMode(0, INPUT);
  Serial.begin(9600);
  leds.begin();
  leds.show();
}

#define GREEN  0x00FF00
#define CLEAR 0x000000

void loop() {

  if(digitalRead(0) == HIGH) {
    for (int i=0; i < ledsPerStrip; i++) {
      for(int j=0; j<9; j++) {
        //int seed = random(0,20);

        leds.setPixel(i+ledsPerStrip*j, CLEAR);
        //leds.setPixel(i+10+ledsPerStrip*j, Color[j]);
        //leds.setPixel(i+9+ledsPerStrip*j, Color[j-1]);
        leds.setPixel(i+5+ledsPerStrip*j, Color[0]);
        //Serial.println(i+j);
        delay(1);
      }
      leds.show();
    }
  }
  else {
    for (int i=0; i < ledsPerStrip; i++) {
      for(int j=0; j<9; j++) {
        //int seed = random(0,20);

        leds.setPixel(i+ledsPerStrip*j, CLEAR);
        //leds.setPixel(i+10+ledsPerStrip*j, Color[j]);
        //leds.setPixel(i+9+ledsPerStrip*j, Color[j-1]);
        leds.setPixel(i+5+ledsPerStrip*j, CLEAR);
        //Serial.println(i+j);
        delay(1);
      }
      leds.show();
    }
  }
}




