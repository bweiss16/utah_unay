/*
 * log
 * Reads lux, temperature, and humidity once per second and appends
 * each reading to log.csv on the SD card. Each row is also printed
 * to the Serial Monitor so you can confirm writes are happening.
 *
 * Hardware
 *   Adafruit Feather RP2040 Adalogger
 *   BH1750 light sensor  — connected via STEMMA QT
 *   AHT20 temp/humidity  — daisy-chained after BH1750
 *   MicroSD card         — inserted in the onboard slot
 *
 * Required libraries (install via Tools → Manage Libraries)
 *   SdFat - Adafruit Fork
 *   hp_BH1750
 *   Adafruit AHTX0
 *   Adafruit BusIO
 */

#include <Wire.h>
#include <SPI.h>
#include "SdFat.h"
#include <hp_BH1750.h>
#include <Adafruit_AHTX0.h>

// SD card — RP2040 Adalogger uses SPI1, CS on pin 23
#define SD_CS_PIN 23
SdFat SD;
SdSpiConfig sdConfig(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(16), &SPI1);

hp_BH1750      lightMeter;
Adafruit_AHTX0 aht20;

const char* LOG_FILENAME = "log.csv";
unsigned long sampleCount = 0;

// ── Setup ─────────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialise BH1750
  if (!lightMeter.begin(BH1750_TO_GROUND)) {
    Serial.println("ERROR: BH1750 not found — check wiring");
    while (true) { delay(100); }
  }
  Serial.println("BH1750  : OK");

  // Initialise AHT20
  if (!aht20.begin()) {
    Serial.println("ERROR: AHT20 not found — check wiring");
    while (true) { delay(100); }
  }
  Serial.println("AHT20   : OK");

  // Initialise SD card
  if (!SD.begin(sdConfig)) {
    Serial.println("ERROR: SD card not found — check that it is inserted");
    while (true) { delay(100); }
  }
  Serial.println("SD card : OK");

  // Write CSV header if file doesn't already exist
  if (!SD.exists(LOG_FILENAME)) {
    FsFile f = SD.open(LOG_FILENAME, FILE_WRITE);
    if (f) {
      f.println("sample,millis,lux,temp_C,humidity_pct");
      f.close();
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
  Serial.print("  Temp: ");     Serial.print(tempC, 2);     Serial.print(" C");
  Serial.print("  Humidity: "); Serial.print(humidity, 1);  Serial.println(" %");

  // Append CSV row to SD card
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

  delay(1000);
}
