/*
 * log_display
 * Reads lux, temperature, and humidity once per second, logs each
 * reading to log.csv on the SD card, and displays live readings on
 * the 128x64 OLED FeatherWing.
 *
 * Hardware
 *   Adafruit Feather RP2040 Adalogger
 *   BH1750 light sensor         — connected via STEMMA QT
 *   AHT20 temp/humidity sensor  — daisy-chained after BH1750
 *   OLED FeatherWing 128x64     — stacked on top of Feather
 *   MicroSD card                — inserted in the onboard slot
 *
 * Required libraries (install via Tools → Manage Libraries)
 *   Adafruit SH110x
 *   Adafruit GFX Library
 *   SdFat - Adafruit Fork
 *   hp_BH1750
 *   Adafruit AHTX0
 *   Adafruit BusIO
 */

#include <Wire.h>
#include <SPI.h>
#include "SdFat.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <hp_BH1750.h>
#include <Adafruit_AHTX0.h>

// ── Display ───────────────────────────────────────────────────────────────────
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

// ── SD card ───────────────────────────────────────────────────────────────────
#define SD_CS_PIN 23
SdFat SD;
SdSpiConfig sdConfig(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(16), &SPI1);
const char* LOG_FILENAME = "log.csv";

// ── Sensors ───────────────────────────────────────────────────────────────────
hp_BH1750      lightMeter;
Adafruit_AHTX0 aht20;

// ── State ─────────────────────────────────────────────────────────────────────
unsigned long sampleCount = 0;
bool sdReady = false;

// ── Setup ─────────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialise display
  delay(250);
  display.begin(0x3C, true);
  display.clearDisplay();
  display.setRotation(1);
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("Starting up...");
  display.display();

  // Initialise BH1750
  if (!lightMeter.begin(BH1750_TO_GROUND)) {
    Serial.println("ERROR: BH1750 not found — check wiring");
    displayError("BH1750 not found");
    while (true) { delay(100); }
  }
  Serial.println("BH1750  : OK");

  // Initialise AHT20
  if (!aht20.begin()) {
    Serial.println("ERROR: AHT20 not found — check wiring");
    displayError("AHT20 not found");
    while (true) { delay(100); }
  }
  Serial.println("AHT20   : OK");

  // Initialise SD card
  if (!SD.begin(sdConfig)) {
    Serial.println("ERROR: SD card not found — check that it is inserted");
    sdReady = false;
  } else {
    sdReady = true;
    Serial.println("SD card : OK");

    // Write CSV header if file doesn't already exist
    if (!SD.exists(LOG_FILENAME)) {
      FsFile f = SD.open(LOG_FILENAME, FILE_WRITE);
      if (f) {
        f.println("sample,millis,lux,temp_C,humidity_pct");
        f.close();
      }
    }
  }

  Serial.println("----------------------------------");
  Serial.println("Logging started");
  Serial.println("----------------------------------");
}

// ── Loop ──────────────────────────────────────────────────────────────────────
void loop() {
  sampleCount++;
  unsigned long t = millis();

  // Read BH1750
  lightMeter.start();
  float lux = lightMeter.getLux();

  // Read AHT20
  sensors_event_t humidityEvent, tempEvent;
  aht20.getEvent(&humidityEvent, &tempEvent);
  float tempC    = tempEvent.temperature;
  float humidity = humidityEvent.relative_humidity;

  // Human-readable Serial output
  Serial.print("Sample: ");     Serial.print(sampleCount);
  Serial.print("  Lux: ");      Serial.print(lux, 1);
  Serial.print("  Temp: ");     Serial.print(tempC, 2);    Serial.print(" C");
  Serial.print("  Humidity: "); Serial.print(humidity, 1); Serial.println(" %");

  // Append CSV row to SD card
  if (sdReady) {
    FsFile f = SD.open(LOG_FILENAME, FILE_WRITE);
    if (f) {
      f.print(sampleCount);  f.print(",");
      f.print(t);            f.print(",");
      f.print(lux, 1);       f.print(",");
      f.print(tempC, 2);     f.print(",");
      f.println(humidity, 1);
      f.close();
    } else {
      Serial.println("ERROR: could not open log.csv");
    }
  }

  // Update display
  updateDisplay(lux, tempC, humidity);

  delay(1000);
}

// ── Draw live readings on the 128x64 OLED ────────────────────────────────────
//
//  y=0  : "LOGGER   #00001"
//  y=9  : ────────────────
//  y=13 : "Lux:  XXXXX.X"
//  y=25 : "Temp: XX.XX C"
//  y=37 : "RH:   XX.X %"
//  y=49 : ────────────────
//  y=54 : "SD: OK" / "SD: NO CARD"
//
void updateDisplay(float lux, float tempC, float humidity) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);

  // Title bar
  display.setCursor(0, 0);
  display.print("LOGGER   #");
  if (sampleCount < 10000) display.print("0");
  if (sampleCount < 1000)  display.print("0");
  if (sampleCount < 100)   display.print("0");
  if (sampleCount < 10)    display.print("0");
  display.print(sampleCount);

  display.drawFastHLine(0, 9, 128, SH110X_WHITE);

  // Sensor readings
  display.setCursor(0, 13);
  display.print("Lux:  ");
  display.print(lux, 1);

  display.setCursor(0, 25);
  display.print("Temp: ");
  display.print(tempC, 1);
  display.print(" C");

  display.setCursor(0, 37);
  display.print("RH:   ");
  display.print(humidity, 1);
  display.print(" %");

  // Status bar
  display.drawFastHLine(0, 49, 128, SH110X_WHITE);
  display.setCursor(0, 54);
  display.print("SD: ");
  display.print(sdReady ? "OK" : "NO CARD");

  display.display();
}

// ── Show an error message on the display ─────────────────────────────────────
void displayError(const char* msg) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("ERROR:");
  display.println(msg);
  display.println("");
  display.println("Check wiring");
  display.println("and restart.");
  display.display();
}
