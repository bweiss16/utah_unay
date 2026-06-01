# Building a Sensor Logger
**Day 1 — Follow-Along Guide · Adafruit Feather RP2040 Adalogger**

> **Today's goal:** By the end of the day you'll have a working sensor logger — a small computer that measures light, temperature, and humidity, saves the data to an SD card, and runs on a battery in the field. You'll build it one module at a time. Each module adds something new to what you already have.

---

## 🆘 If Your Board Stops Showing Up as a Port

On the RP2040, the USB connection is managed by the microcontroller itself — not a separate chip. If a sketch crashes before USB initializes, the port disappears. This is normal and recoverable.

**To get your board back:**

1. Hold the **BOOT** button on the board
2. While holding BOOT, unplug and replug the USB cable
3. Release BOOT — a drive called **RPI-RP2** should appear on your computer
4. In Arduino IDE, open **File → Examples → 01.Basics → Blink**
5. Select your board under **Tools → Board**
6. Select the port under **Tools → Port** — it may appear as `UF2 Bootloader` or `RPI-RP2`
7. Upload Blink — the board will reboot and the normal port will reappear
8. You can now re-upload whichever sketch you were working on

> 💡 If no port appears in step 6, go to **Sketch → Export Compiled Binary** while Blink is open, then drag the resulting `.uf2` file onto the RPI-RP2 drive.

---

## Module 1 — Blink an LED

Your first program. You'll get the Arduino IDE talking to the Feather RP2040, upload a sketch, and make the board's built-in LED blink. This confirms everything is set up correctly before you add any sensors.

### Steps

**Step 1 — Set up Arduino IDE for the RP2040**

Follow the Adafruit setup tutorial at **[learn.adafruit.com/adafruit-feather-rp2040-adalogger/arduino](https://learn.adafruit.com/adafruit-feather-rp2040-adalogger/arduino)** — work through each section in order:

- [ ] A) Adding the Philhower Board Manager URL
- [ ] B) Add Board Support Package
- [ ] C) Choose Your Board
- [ ] D) Go to next page by selecting "Arduino Usage"
- [ ] E) Plug in your board
- [ ] F) Select port
- [ ] G) Load the example Blink sketch

**Step 2 — Upload CODE_1 and experiment with the timing**

The built-in Blink example can't be edited directly. Open `CODE_1_blink` from the workshop sketches instead — it's the same sketch, but yours to modify. Find the two `delay()` calls and try changing the numbers. What happens when you make one value much larger than the other?

> 📎 _[PLACEHOLDER — CODE_1 link or file path]_

✅ **Checkpoint:** Your board's LED is blinking and you've changed the timing to see the effect.

---

## Module 2 — Sensing Light

Your first sensor. The BH1750 measures ambient light and reports the value directly in lux — the standard unit for light intensity. You'll connect it via a Qwiic cable, install its library, and watch the data stream live.

### Concept

The BH1750 communicates over **I2C** — a protocol that lets a microcontroller talk to sensors using just two wires: one for data (`SDA`) and one for a clock signal (`SCL`). The Feather RP2040 Adalogger has a STEMMA QT port that exposes these pins via a small JST connector, so no individual wires are needed at all.

### Wiring

Plug one end of a Qwiic/STEMMA QT cable into the port on your Feather and the other end into either port on the BH1750 breakout. All four connections (power, ground, SDA, SCL) are made by the cable.

> ⚠️ Unplug the board from USB before connecting the cable. Reconnect USB once the cable is in place.

### Steps

**Step 1 — Install the BH1750 library**

Go to **Tools → Manage Libraries**, search for `Adafruit BH1750`, and install it. Install any dependencies when prompted.

✅ **Checkpoint:** The library is installed and visible under Sketch → Include Library.

**Step 2 — Upload CODE_2**

Open `CODE_2_light_sensor` and upload it.

> 📎 _[PLACEHOLDER — CODE_2 link or file path]_

**Step 3 — Watch the data stream**

Go to **Tools → Serial Monitor**. You should see lux values scrolling. Cover the sensor with your hand and watch the number drop.

✅ **Checkpoint:** Lux values are printing in the Serial Monitor and change when you cover the sensor.

**Step 4 — Try the Serial Plotter**

Close the Serial Monitor and open **Tools → Serial Plotter**. Wave your hand over the sensor and watch the line respond.

✅ **Checkpoint:** You can see the live graph reacting to changes in light level.

---

## Module 3 — Sensing Temperature & Humidity

Add a second I2C sensor — the AHT20 — by daisy-chaining it after the BH1750. Because I2C is a bus, multiple sensors share the same two wires simultaneously. Your serial output will now show three values at once: lux, temperature, and humidity.

### Concept

The Feather's STEMMA QT port and the BH1750 breakout each have **two** Qwiic connectors — one in, one out. This lets you chain sensors together in a line. Each sensor has a unique I2C address so the microcontroller can tell them apart, even though they share the same wires.

### Wiring

Plug a second Qwiic cable into the unused port on the BH1750 and connect the other end to either port on the AHT20:

```
Feather RP2040 → BH1750 → AHT20
```

| Sensor | I2C Address | What it measures |
|--------|-------------|-----------------|
| BH1750 | `0x23` | Light (lux) |
| AHT20  | `0x38` | Temperature (°C) & humidity (%RH) |

### Steps

**Step 1 — Install the AHT20 library**

Go to **Tools → Manage Libraries**, search for `Adafruit AHTX0`, and install it. Install any dependencies when prompted.

✅ **Checkpoint:** The library is installed and visible under Sketch → Include Library.

**Step 2 — Upload CODE_3**

Open `light_temp_humidity` and upload it. This sketch reads from both sensors and prints three values — lux, temperature, and humidity — on each line.

> 📎 _[PLACEHOLDER — CODE_3 link or file path]_

**Step 3 — Interact with the sensors**

Open the Serial Monitor. You should see three values streaming. Try these:

- Cover the BH1750 — does the lux value drop?
- Hold the AHT20 in your palm — does temperature rise slowly?
- Breathe on the AHT20 — does humidity spike?

✅ **Checkpoint:** Three values are printing on each row and all three respond to your interactions.

---

## Module 4 — Data Logging

Right now, all your data disappears the moment you unplug the USB cable. In this module you'll save every reading to the SD card so you can keep it, transfer it to a computer, and graph it.

### Concept

Your sketch will open a file on the SD card and append a new row every few seconds. The file is saved as a **CSV** (comma-separated values) — a simple text format that any graphing tool can read. Each row will contain a reading count, lux, temperature, and humidity.

### Steps

**Step 1 — Install the SD library**

Go to **Tools → Manage Libraries**, search for `SdFat - Adafruit Fork`, and install it. Install any dependencies when prompted.

✅ **Checkpoint:** The library is installed and visible under Sketch → Include Library.

**Step 2 — Insert the SD card**

Make sure the SD card is formatted as FAT32 with no old files on it. Slide it into the slot on the underside of the Feather until it clicks.

> ⚠️ If there's an old `log.csv` on the card, delete it before starting to avoid mixing datasets.

**Step 3 — Upload `log`**

Open `log` and upload it.

> 📎 _[PLACEHOLDER — log sketch link or file path]_

**Step 4 — Let it log**

Open the Serial Monitor. You should see a new row printing every few seconds, each confirming a successful write to the SD card. Let it run for at least 3 minutes.

✅ **Checkpoint:** The Serial Monitor is showing a new row every few seconds confirming SD card writes.

**Step 5 — Retrieve the data**

Unplug the board. Remove the SD card, insert it into the USB card reader, and plug the reader into your computer. Open `log.csv` — you should see a table of readings.

✅ **Checkpoint:** You can open `log.csv` and see rows of real sensor data.

---

## Module 5 — Visualizing Data

Numbers in a CSV file are hard to interpret at a glance. In this module you'll upload your data to a graphing tool and see all three sensor channels plotted over time.

### Steps

**Step 1 — Open the graphing tool**

In a browser, navigate to: **[bweiss16.github.io/utah_unay/graph](https://bweiss16.github.io/utah_unay/graph)**

**Step 2 — Upload your CSV**

Click **Upload CSV** and select your `log.csv` file. The tool will plot lux, temperature, and humidity over time.

**Step 3 — Read your data**

Can you spot moments where you covered the light sensor? Where you breathed on the humidity sensor?

✅ **Checkpoint:** You have a graph with all three sensor channels plotted over time.

---

## Module 6 — Make It Deployable

Your logger is fully functional — now you'll deploy it like a real instrument. You'll wipe the SD card for a clean dataset, switch to battery power, seal everything in the weatherproof case, and take it outside.

### Steps

**Step 1 — Prepare a fresh SD card**

Remove the SD card, delete `log.csv` (or reformat), and reinsert it.

**Step 2 — Switch to battery power**

Unplug the USB cable and connect the LiPo battery to the JST connector on the Feather. The board should restart and begin logging automatically.

> ⚠️ Make sure CODE_4 is still uploaded — the board runs whatever sketch was last uploaded when it powers on.

✅ **Checkpoint:** The board is running on battery and logging without a USB connection.

**Step 3 — Seal it in the case**

Place your Feather and sensors inside the Pelican case and close the lid.

**Step 4 — Deploy outside**

Take your logger outside and place it somewhere interesting — in the sun, in the shade, on the ground. Leave it for at least 10 minutes.

**Step 5 — Retrieve and graph your data**

Bring the logger back in. Remove the SD card, upload `log.csv` to the graphing tool, and look at what you captured.

✅ **Checkpoint:** You have a graph showing real environmental data from your outdoor deployment.

---

*Microcontrollers Workshop — Day 1 · Adafruit Feather RP2040 Adalogger · Arduino IDE*
