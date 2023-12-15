#include <FastLED.h>


#define NUM_STRIPS 12
#define NUM_LEDS_PER_STRIP 20
#define DATA_BUFF_SIZE 63

// PROTOCOL DEFINITION
// byte 0 -> mode: setup = 0x00; set color = 0x01
// byte 1 -> port number: from 0x00 to 0x0F
// IN SET COLOR MODE
// byte 2 - 62 -> port colors in RGB format (UP TO 20 LEDS MANAGEMENT)
// byte 63 check byte

uint8_t DATA_PINS[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

void setup()
{
    Serial.begin(9600);

    FastLED.addLeds<WS2812B, 2, RGB>(leds[0], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 3, RGB>(leds[1], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 4, RGB>(leds[2], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 5, RGB>(leds[3], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 6, RGB>(leds[4], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 7, RGB>(leds[5], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 8, RGB>(leds[6], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 9, RGB>(leds[7], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 10, RGB>(leds[8], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 11, RGB>(leds[9], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 12, RGB>(leds[10], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 13, RGB>(leds[11], NUM_LEDS_PER_STRIP);

    FastLED.show();
}

void loop()
{

    READY_CMD();

    byte data[DATA_BUFF_SIZE];
    memset(data, 0, sizeof(data));
    while (Serial.available() < 63)
    {
        // wait 63 bytes
    }
    Serial.readBytes(data, sizeof(data));
    RECEIVED_CMD();

    if (data[0] == 0x01)
    {
        for (uint8_t i = 2; i <= NUM_LEDS_PER_STRIP; i += 3)
        {
            leds[data[1]][(i-2) / 3] = CRGB(data[i+1], data[i], data[i + 2]);
        }
        FastLED.show();
    }
    else if (data[0] == 0x00)
    {
        Serial.println("setup");
    }
    else
    {
        Serial.write(&data[0], sizeof(data[0]));
    }
}

const byte _READY_CMD[] = {0x01, 0x02, 0x03, 0x04};
void READY_CMD()
{
    Serial.write(_READY_CMD, sizeof(_READY_CMD));
}

const byte _RECEIVED_CMD[] = {0x05, 0x06, 0x07, 0x08};
void RECEIVED_CMD()
{
    Serial.write(_RECEIVED_CMD, sizeof(_RECEIVED_CMD));
}
