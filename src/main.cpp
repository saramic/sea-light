#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_BUILTIN 2 // ESP32 equivalent of Arduino 13

#define PIN_NEO_PIXEL 26 // The ESP32 pin GPIO26 connected to NeoPixel
#define NUM_PIXELS 1     // The number of LEDs (pixels) on NeoPixel LED strip

long last = 0;
boolean light = false;

byte redValue = 0;
byte greenValue = 0;
byte blueValue = 0;

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);
  Serial.println("setup");
  pinMode(LED_BUILTIN, OUTPUT);
  NeoPixel.begin();
}

void loop()
{
  long now = millis();
  if (now - last > 1000) // 1 second flash
  {
    if (light)
    {
      light = false;
      digitalWrite(LED_BUILTIN, LOW);
      Serial.print(">led:");
      Serial.println(0);

      // NeoPixel.setPixelColor(0, NeoPixel.Color(0, 255, 0));
      // NeoPixel.show();
    }
    else
    {
      light = true;
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.print(">led:");
      Serial.println(1);

      // NeoPixel.setPixelColor(0, NeoPixel.Color(255, 0, 0));
      // NeoPixel.show();
      // NeoPixel.clear(); // to turn off if we need it
    }
    last = now;
  }
  redValue = 128 + (sin(millis() / 900.0) * 128);
  greenValue = 128 + (sin(millis() / 600.0) * 128);
  blueValue = 128 + (sin((millis()) / 300.0) * 128);
  Serial.print(">red:");
  Serial.println(redValue);
  Serial.print(">green:");
  Serial.println(greenValue);
  Serial.print(">blue:");
  Serial.println(blueValue);
  NeoPixel.setPixelColor(0, NeoPixel.Color(redValue, greenValue, blueValue));
  NeoPixel.show();
  delay(20);
}
