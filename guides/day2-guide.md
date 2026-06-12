# Adding a Live Display
**Day 2 — Follow-Along Guide · Adafruit Feather RP2040 Adalogger**

> **Today's goal:** Add the OLED display to your sensor logger so you can see live readings on screen — no laptop required. By the end of the session your display will show light level, temperature, and humidity updating in real time, and your system will still be logging everything to the SD card simultaneously.

---

## Module 1 — Add the OLED Display

The FeatherWing OLED snaps directly onto your Feather board — no wiring needed. It communicates over I2C, the same bus your sensors are already using, so adding it is mostly a software task.

### Concept

The display connects via the same SDA and SCL pins as your BH1750 and AHT20. All three devices share the I2C bus simultaneously — the microcontroller addresses each one separately by its unique I2C address. The display also has three buttons (A, B, C) on the wing that you can use in future projects.

---

### Step 1 — Attach the FeatherWing

Make sure your Feather is unplugged from USB and the battery is disconnected. Align the FeatherWing OLED over your Feather RP2040 Adalogger and press it firmly onto the headers until it seats flush.

> ⚠️ The display and sensors all share the same I2C bus. Don't remove your BH1750 or AHT20 Qwiic cables — they stay connected throughout Day 2.

✅ **Checkpoint:** The FeatherWing is seated firmly. No pins are bent. Your Qwiic sensor cables are still connected.

---

### Step 2 — Install the display libraries

Go to **Tools → Manage Libraries** and install both of these if you don't already have them:

- `Adafruit SH110x`
- `Adafruit GFX Library`

Install any dependencies when prompted.

✅ **Checkpoint:** Both libraries are installed and visible under Sketch → Include Library.

---

### Step 3 — Run the Adafruit example sketch

Before touching your logging code, confirm the display works on its own. Go to **File → Examples → Adafruit SH110x** and open `OLED_featherwing`.

Upload it. The display should show a splash screen and some text. The A, B, and C buttons on the wing will print letters to the screen when pressed.

> ⚠️ If the display stays blank, check that the FeatherWing is fully seated on the headers. A partially connected pin is the most common cause.

✅ **Checkpoint:** The display is showing output from the Adafruit example. Remove and reseat the wing if it stays blank.

---

### Step 4 — Upload `log_display`

In the unzipped repo folder, go to `sketches → log_display` and open `log_display.ino`. Arduino IDE will open the sketch — upload it. It reads all three sensors, displays live readings on the OLED, and continues logging to the SD card simultaneously.

> 📎 [github.com/bweiss16/utah_unay/tree/main/sketches/log_display](https://github.com/bweiss16/utah_unay/tree/main/sketches/log_display)

✅ **Checkpoint:** The display shows three lines of live sensor data and updates every few seconds.

---

### Step 5 — Customize your logger name

Near the top of `log_display.ino`, find this line:

```cpp
const char* LOGGER_NAME = "LOGGER";
```

Change `"LOGGER"` to whatever you want — your name, your project name, a location, anything. Keep it short (8–10 characters) so it fits on the screen without overlapping the sample counter. Upload the sketch again and check that your name appears on the display.

✅ **Checkpoint:** Your custom name is showing in the top-left of the display.

---

### Step 6 — Verify the display output

Your screen should look something like this:

```
LOGGER   #00042
────────────────
Light: 412.0
Temp:  74.1 F
Hum:   58.2 %
────────────────
SD: OK
```

Try interacting with your sensors and watch the values update:

- Cover the BH1750 with your hand — does the lux value drop?
- Breathe on the AHT20 — does humidity spike?
- Hold the AHT20 in your palm — does temperature rise?

✅ **Checkpoint:** All three readings are visible on screen and respond to your interactions. The SD card is still logging in the background.

---

### Step 7 — Verify logging is still working

Let the system run for a minute, then remove the SD card and check that new rows are still being written to `log.csv`. The display and logging should be running simultaneously.

✅ **Checkpoint:** Your CSV file has fresh rows with all three sensor columns populated.

> **Notes**
> &nbsp;
> &nbsp;
> &nbsp;

---

## Troubleshooting

| Symptom | Most likely cause | Try this |
|---------|------------------|----------|
| Display stays completely blank | FeatherWing not fully seated | Unplug, remove the wing, and press it back on firmly. Check for bent pins. |
| Example works but `log_display` shows blank | I2C address mismatch | Run the I2C Scanner sketch and confirm the display address — should be `0x3C` or `0x3D`. |
| One sensor reads 0 or NaN | Qwiic cable came loose when attaching wing | Check that both Qwiic cables are still firmly seated. |
| SD card stopped logging | SD not initialized before display in sketch | Check the Serial Monitor for errors. SD must be initialized in `setup()` before the display. |
| Board won't upload | Wrong board selected | Confirm Tools → Board is set to **Adafruit Feather RP2040 Adalogger**. |

---

*Utah Unây Workshop — Day 2 · Adafruit Feather RP2040 Adalogger · Arduino IDE*
