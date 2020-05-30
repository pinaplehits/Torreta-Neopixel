#include <Adafruit_NeoPixel.h>

#define PIN 9
#define NUMPIXELS 16

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int RGBColorLeds[][3] = {
  {0, 0, 0}, //turn cells off
  {255, 0, 0}, //red
  {0, 255, 0}, //green
  {0, 0, 255}, //blue
  {255, 0, 255}, //purple
  {0, 255, 255}, //green_blue
  {255, 255, 0}, //yellow
  {255, 255, 255}, //white
  {255, 100, 100}, //pink
  {255, 85, 0} //orange
};

const int colorPin[] = {5, 6, 7, 8};
const int flashColor[] = {1, 2, 3, 6, 7, 9};
const int sizeColorPin = sizeof(colorPin) / sizeof(colorPin[0]);
const int rowsRGBColorLeds = sizeof(RGBColorLeds) / sizeof(RGBColorLeds[0]);
const int delayFlash = 400;

int i;
int currentColor;

void setup()
{
  delay(100);
  Serial.begin(9600);
  Serial.println("Torreta Version 1.0");
  Serial.println("El pin 9 es el pin de datos");
  Serial.println("Selector de colores por pines: 5, 6, 7, 8");
  Serial.println("9 colores disponibles rojo [PIN 5], verde [PIN 6], azul [PIN 5+6], morado [PIN 7], verde-azul [PIN 5+7], amarillo [PIN 6+7], blanco[PIN 5+6+7], rosa [PIN 8], naranja [PIN 5+8]");
  Serial.println("6 colores con flash disponibles rojo [PIN 5], verde [PIN 6], azul [PIN 5+6], amarillo [PIN 6+7], blanco[PIN 5+6+7], naranja [PIN 5+8]");

  pixels.begin();
  pixels.setBrightness(128);

  for (i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, 255, 255, 255);
    pixels.show();
    delay(20);
  }

  pixels.clear();
  pixels.show();

  for (i = 0; i < sizeColorPin; i++)
  {
    pinMode(colorPin[i], INPUT);
  }
}

void loop()
{
  SelectPixelColor();

  if (currentColor < rowsRGBColorLeds)
  {
    TurnOnPixel();
  }
  else
  {
    FlashPixel();
  }

  currentColor = 0;
}

void SelectPixelColor()
{
  for (i = 0; i < sizeColorPin; i++)
  {
    if (digitalRead(colorPin[i]) == LOW)
    {
      currentColor += bit(i);
    }
  }
}

void TurnOnPixel()
{
  for (i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, RGBColorLeds[currentColor][0], RGBColorLeds[currentColor][1], RGBColorLeds[currentColor][2]);
    }

    pixels.show();
}

void FlashPixel()
{
  currentColor -= rowsRGBColorLeds;
  currentColor = flashColor[currentColor];

  TurnOnPixel();

  delay(delayFlash);

  pixels.clear();
  pixels.show();

  delay(delayFlash);
}