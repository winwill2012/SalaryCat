#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#include "cat_frames.h"

// ESP32-C3 Super Mini + 0.42 inch 72x40 SSD1306 I2C OLED.
// Wiring:
//   VCC -> 3V3, GND -> GND, SCL -> IO6, SDA -> IO5
U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

constexpr uint8_t OLED_SDA = 5;
constexpr uint8_t OLED_SCL = 6;

void setup() {
  Wire.begin(OLED_SDA, OLED_SCL);
  u8g2.begin();
  u8g2.setBusClock(400000);
  u8g2.setContrast(220);
}

void loop() {
  const uint8_t frame = (millis() / CAT_FRAME_MS) % CAT_FRAME_COUNT;

  u8g2.clearBuffer();
  u8g2.drawXBMP(0, 0, CAT_FRAME_WIDTH, CAT_FRAME_HEIGHT, CAT_FRAMES[frame]);
  u8g2.sendBuffer();
}
