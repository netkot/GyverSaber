#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 58

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define LED_PIN 6

#define button_pin_encoder 7
#define pin_encoder_1 2
#define pin_encoder_2 3

#define button_pin_red 3
#define button_pin_black 4

#define DEBUG true

int button_state_encoder = 0;
int button_state_red = 0;
int button_state_black = 0;

byte red, green, blue;

int mode_cnt = 1;

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(button_pin_encoder, INPUT_PULLUP);
  pinMode(button_pin_red, INPUT_PULLUP);
  pinMode(button_pin_black, INPUT_PULLUP);

  FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(40);  // яркость ленты 0 - 255
  setAll(0, 0, 0);            // ставим чёрный цвет ленты

  delay(1000);

  red = 255;
  green = 0;
  blue = 0;
}

void loop() {
  // Turn the LED on, then pause

   //setAll(255, 0, 0);  // ставим красный цвет ленты
  setAll(0, 0, 0);  // ставим черный цвет ленты
  FastLED.show();

  delay (100);

  light_up();
  delay (2000);
  light_down();

  //transite_all();

  delay (100);
  
  
}



void transite_all() {
  for (char i = 0; i <= NUM_LEDS; i++) {  // включить все диоды выбранным цветом
    setPixel(i, red, green, blue);
    FastLED.show();
    delay(100);
    setAll(0, 0, 0);
    FastLED.show();
  }
}



void light_up() {
  for (char i = 0; i <= (NUM_LEDS / 4); i++) {  // включить все диоды выбранным цветом
    setPixel(i, red, green, blue);
    setPixel((NUM_LEDS / 2) - i - 1, red, green, blue);
    setPixel(NUM_LEDS / 2 + i, red, green, blue);
    setPixel(NUM_LEDS - i - 1, red, green, blue);
    FastLED.show();
    delay(200);
  }
}


void light_down() {
  for (char i = (NUM_LEDS / 4); i >= 0; i--) {      // выключить все диоды
    setPixel(i, 0, 0, 0);
    setPixel((NUM_LEDS / 2) - i - 1, 0, 0, 0);
    setPixel(NUM_LEDS / 2 + i, 0, 0, 0);
    setPixel(NUM_LEDS - i - 1, 0, 0, 0);
    FastLED.show();
    delay(200);
  }
}

// функция заливки всех светодиодов выбранным цветом
void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < NUM_LEDS; i++) {
    setPixel(i, red, green, blue);
  }
  FastLED.show();
}

// функция выбора цвета одного светодиода
void setPixel(int Pixel, byte red, byte green, byte blue) {
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
}
