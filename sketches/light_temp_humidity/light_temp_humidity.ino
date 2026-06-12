/*
 * light_temp_humidity
 * Reads lux from a BH1750 light sensor and temperature + humidity
 * from an AHT20, then prints all three values to the Serial Monitor
 * once per second.
 *
 * Hardware
 *   Adafruit Feather RP2040 Adalogger
 *   BH1750 light sensor  — connected via STEMMA QT
 *   AHT20 temp/humidity  — daisy-chained after BH1750
 *
 * Required libraries (install via Tools → Manage Libraries)
 *   hp_BH1750
 *   Adafruit AHTX0
 *   Adafruit BusIO
 */

#include <Wire.h>
#include <hp_BH1750.h>
#include <Adafruit_AHTX0.h>

hp_BH1750      lightMeter;
Adafruit_AHTX0 aht20;

// ── Setup ─────────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialise BH1750 (address pin connected to ground)
  if (!lightMeter.begin(BH1750_TO_GROUND)) {
    Serial.println("ERROR: BH1750 not found — check wiring");
    while (true) { delay(100); }
  }

  // Initialise AHT20
  if (!aht20.begin()) {
    Serial.println("ERROR: AHT20 not found — check wiring");
    while (true) { delay(100); }
  }

  // CSV header so Serial Plotter labels the three traces
  Serial.println("lux,temp_F,humidity_pct");
}

// ── Loop ──────────────────────────────────────────────────────────────────────
void loop() {
  // Read BH1750
  lightMeter.start();
  float lux = lightMeter.getLux();

  // Read AHT20
  sensors_event_t humidityEvent, tempEvent;
  aht20.getEvent(&humidityEvent, &tempEvent);
  float tempF    = (tempEvent.temperature * 9.0 / 5.0) + 32.0;
  float humidity = humidityEvent.relative_humidity;

  // Print comma-separated — works in both Serial Monitor and Serial Plotter
  Serial.print(lux,      1);  Serial.print(",");
  Serial.print(tempF,    2);  Serial.print(",");
  Serial.println(humidity, 1);

  delay(1000);
}
