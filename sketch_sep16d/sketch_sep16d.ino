#include <PololuLedStrip.h>

// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<12> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 10
rgb_color colors[LED_COUNT];

void setup()
{
  // Start up the serial port, for communication with the PC.
  Serial.begin(115200);
  Serial.println("Ready to receive colors.");
}

void loop()
{
  // If any digit is received, we will go into integer parsing mode
  // until all three calls to parseInt return an interger or time out.
  if (Serial.available())
  {
    char c = Serial.peek();
    if (!(c >= '0' && c <= '9'))
    {
      Serial.read(); // Discard non-digit character
    }
    else
    {
      rgb_color color;
      for (uint16_t i = 0; i < LED_COUNT; i++)
      {

        color.red = Serial.parseInt();
        color.green = Serial.parseInt();
        color.blue = Serial.parseInt();

        colors[i] = color;
      }

      // Write to the LED strip.
      ledStrip.write(colors, LED_COUNT);

      Serial.print("Showing color: ");
      Serial.print(color.red);
      Serial.print(",");
      Serial.print(color.green);
      Serial.print(",");
      Serial.println(color.blue);
    }
  }
}
