#include <Arduino.h>
#include <SPI.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold12pt7b.h>

// Waveshare/clone ESP32 e-paper boards often wire the connector to HSPI
#define EPD_SCK  13
#define EPD_MOSI 14
#define EPD_CS   15
#define EPD_DC   27
#define EPD_RST  26
#define EPD_BUSY 25

// Panel selection: set to 1 for 7.5" (HINK-E075A07-A0), 0 for 5.83" Z83.
#define PANEL_75 1
#define EPD_RESET_MS 2

// Use HSPI explicitly (Arduino defaults to VSPI otherwise)
SPIClass hspi(HSPI);

#if PANEL_75
// HINK-E075A07-A0 (880x528) tri-color (B/W/Red), SSD1677 family
using DisplayClass = GxEPD2_3C<GxEPD2_750c_Z90, GxEPD2_750c_Z90::HEIGHT / 4>;
static const char* kPanelName = "HINK-E075A07-A0 (7.5 Z90)";
#else
// 5.83" tri-color panel used by Waveshare 5.83inch e-Paper HAT (B)
using DisplayClass = GxEPD2_3C<GxEPD2_583c_GDEW0583Z83, GxEPD2_583c_GDEW0583Z83::HEIGHT / 4>;
static const char* kPanelName = "GDEW0583Z83 (5.83)";
#endif

DisplayClass display(
#if PANEL_75
  GxEPD2_750c_Z90(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY)
#else
  GxEPD2_583c_GDEW0583Z83(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY)
#endif
);

void drawHello()
{
  display.setRotation(1);
  display.setFont(&FreeMonoBold12pt7b);

  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    display.setTextColor(GxEPD_BLACK);
    display.setCursor(20, 60);
    display.print("Hello ePaper");

    display.setCursor(20, 100);
    display.print(kPanelName);

    display.setTextColor(GxEPD_RED);
    display.setCursor(20, 150);
    display.print("RED works!");
  } while (display.nextPage());

  display.hibernate();
}

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting...");

  // Bind the display to HSPI
  hspi.begin(EPD_SCK, -1, EPD_MOSI, EPD_CS);
  display.epd2.selectSPI(hspi, SPISettings(4000000, MSBFIRST, SPI_MODE0));

  // init(baud, initial, reset_duration_ms, pulldown_busy)
  display.init(115200, true, EPD_RESET_MS, false);

  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
  } while (display.nextPage());
  delay(1000);

  drawHello();

  Serial.println("Done.");
}

void loop() {}