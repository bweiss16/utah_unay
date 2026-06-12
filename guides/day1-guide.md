# Building a Sensor Logger
**Day 1 — Follow-Along Guide · Adafruit Feather RP2040 Adalogger**

> **Today's goal:** By the end of the day you'll have a working sensor logger — a small computer that measures light, temperature, and humidity, saves the data to an SD card, and runs on a battery in the field. You'll build it one module at a time. Each module adds something new to what you already have.

---

## 🆘 If Your Board Stops Showing Up as a Port

On the RP2040, sometimes the USB connection looks like it's no longer functioning. If this happens, follow these steps to recover the connection.

1. Unplug the USB cable from your computer
2. Hold down the **BOOT** button on the board
3. While pressing BOOT, plug the USB cable back in
4. THEN release BOOT — a drive called **RPI-RP2** should appear on your computer
5. Close the Arduino IDE and re-open it. You can either go back to the file you were working on OR open **File → Examples → 01.Basics → Blink**
6. Select your board under **Tools → Board**
7. Select the port under **Tools → Port** — it may appear as `UF2 Bootloader` or `RPI-RP2`
8. Upload the code — the board will reboot and the normal port will reappear

---

## Accessing Materials and Example Code

All guides, tools, and code for this workshop live in one place. Take a minute to get everything downloaded before we start.

### Workshop Site

Open a browser and go to: **[bweiss16.github.io/utah_unay](https://bweiss16.github.io/utah_unay)**

This is your home base for the workshop — it has links to both day guides, the graphing tool, and the hardware list. Keep this tab open.

### Download the Workshop Repository

**Step 1 — Download the workshop repository**

Open the Github repository at **[github.com/bweiss16/utah_unay](https://github.com/bweiss16/utah_unay)**. Click the green **Code** button and select **Download ZIP**. Save it to your Desktop.

**Step 2 — Unzip the folder**

Find the downloaded ZIP file and extract it. Inside you'll find a `sketches/` folder — that's where all the Arduino code for today and tomorrow lives. You won't need it until Module 3, but it's good to have it ready.

---

## Module 1 — Blink an LED

Your first program. You'll get the Arduino IDE talking to the Feather RP2040, upload a sketch, and make the board's built-in LED blink. This confirms everything is set up correctly before you add any sensors.

### Steps

**Step 1 — Set up the Arduino IDE**

> ℹ️ If the IDE is already installed and your board has been added, skip to step 2.

Follow the Adafruit setup tutorial at **[learn.adafruit.com/adafruit-feather-rp2040-adalogger/arduino](https://learn.adafruit.com/adafruit-feather-rp2040-adalogger/arduino)** and work through each section until your board is set up.

**Step 2 — Upload and run Blink code**

Follow the steps at **[learn.adafruit.com/adafruit-feather-rp2040-adalogger/arduino-usage](https://learn.adafruit.com/adafruit-feather-rp2040-adalogger/arduino-usage)**. After you select your board and port, you should see **Adafruit Feather RP2040 Adalogger** in bold at the top of the window. After you upload the Blink code, you should see the LED on your board start blinking. If not, try to figure out what went wrong!

> ⚠️ When selecting your board, make sure the name matches exactly: "Adafruit Feather RP2040 Adalogger". Do not select "Adafruit Feather RP2040" — it looks similar but is a different board and will cause problems.

**Step 3 — Edit the code and experiment with timing**

Find the two places in the code where the `delay()` function is used. Try changing the numbers. What happens when you make one value much larger than the other? What does each number control?

✅ **Checkpoint:** Move on if your board's LED is blinking and you understand what each `delay()` is doing.

---

## Module 2 — Sensing Light

Your first sensor. The BH1750 measures ambient light and reports the value directly in lux — the standard unit for light intensity. You'll connect it via a Qwiic cable, install its library, and watch the data stream live.

### Concept

The BH1750 communicates over **I2C** — a protocol that lets a microcontroller talk to sensors using just two wires: one for data (`SDA`) and one for a clock signal (`SCL`). The Feather RP2040 Adalogger has a STEMMA QT port that exposes these pins via a small JST connector, so no individual wires are needed at all.

### Wiring

Disconnect your RP2040 from your laptop. Plug one end of a Qwiic/STEMMA QT cable into the port on your Feather and the other end into either port on the BH1750 breakout. All four connections (power, ground, SDA, SCL) are made by the cable. Plug the RP2040 back into your computer.

> ⚠️ Unplug the board from USB before connecting the cable. Reconnect USB once the cable is in place.

### Steps

**Step 1 — Install the BH1750 library**

Go to **Tools → Manage Libraries**, search for `hp_BH1750`, and install it. Install any dependencies when prompted.

✅ **Checkpoint:** The library is installed and visible under Sketch → Include Library.

**Step 2 — Open and upload the BareMinimum example**

Go to **File → Examples**, scroll down until you see **hp_BH1750**, and open the **BareMinimum** example. Upload it.

**Step 3 — Watch the data stream**

Click the **magnifying glass icon** in the top-right corner of the Arduino IDE to open the Serial Monitor. Make sure the baud rate dropdown is set to 9600. You should see lux values scrolling. Cover the sensor with your hand and watch the number drop.

✅ **Checkpoint:** Lux values are printing in the Serial Monitor and change when you cover the sensor.

**Step 4 — Try the Serial Plotter**

Click the **squiggle icon** in the top-right corner of the Arduino IDE to open the Serial Plotter. Wave your hand over the sensor and watch the line respond.

✅ **Checkpoint:** You can see the live graph reacting to changes in light level.

---

## Module 3 — Sensing Temperature & Humidity

Add a second I2C sensor — the AHT20 — by daisy-chaining it after the BH1750. Because I2C is a bus, multiple sensors share the same two wires simultaneously. Your serial output will now show three values at once: lux, temperature, and humidity.

### Concept

The Feather's STEMMA QT port and the BH1750 breakout each have **two** Qwiic connectors — one in, one out. This lets you chain sensors together in a line. Each sensor has a unique I2C address so the microcontroller can tell them apart, even though they share the same wires.

### Wiring

First, disconnect your RP2040 from your computer's USB. Plug a second Qwiic cable into the unused port on the BH1750 and connect the other end to either port on the AHT20. Your chain should look like:

```
Feather RP2040 → BH1750 → AHT20.
```

Plug your RP2040 back into your computer.

### Steps

**Step 1 — Install the AHT20 library**

Go to **Tools → Manage Libraries**, search for `Adafruit AHTX0`, and install it. Install any dependencies when prompted.

✅ **Checkpoint:** The library is installed and visible under Sketch → Include Library.

**Step 2 — Upload `light_temp_humidity`**

In the unzipped repo folder, go to `sketches → light_temp_humidity` and open `light_temp_humidity.ino`. Arduino IDE will open the sketch — upload it. This sketch reads from both sensors and prints three values — lux, temperature, and humidity — on each line.

> 📎 [github.com/bweiss16/utah_unay/tree/main/sketches/light_temp_humidity](https://github.com/bweiss16/utah_unay/tree/main/sketches/light_temp_humidity)

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

**Step 1 — Format the SD card**

The SD card must be formatted as **FAT32** before the logger can write to it. Insert the card into the USB card reader and plug it into your computer.

- **Windows:** Open File Explorer, right-click the card's drive, and select **Format**. Set the file system to **FAT32** and click **Start**.
- **Mac:** Open **Disk Utility** (search for it in Spotlight). Select the SD card in the left panel, click **Erase**, choose **MS-DOS (FAT)** as the format, and click **Erase**.

Once formatting is complete, eject the card and remove it from the reader.

✅ **Checkpoint:** The SD card is formatted as FAT32 and ejected from the reader.

**Step 2 — Install the SD library**

Go to **Tools → Manage Libraries**, search for `SdFat - Adafruit Fork`, and install it. Install any dependencies when prompted.

✅ **Checkpoint:** The library is installed and visible under Sketch → Include Library.

**Step 3 — Insert the SD card**

Slide the card into the slot on the underside of the Feather until it clicks.

**Step 4 — Upload `log`**

In the unzipped repo folder, go to `sketches → log` and open `log.ino`. Select your board and port again if needed, then upload the sketch.

> 📎 [github.com/bweiss16/utah_unay/tree/main/sketches/log](https://github.com/bweiss16/utah_unay/tree/main/sketches/log)

**Step 5 — Let it log**

Open the Serial Monitor. You should see a new row printing every few seconds, each confirming a successful write to the SD card. Let it run for at least 3 minutes.

✅ **Checkpoint:** The Serial Monitor is showing a new row every few seconds confirming SD card writes.

---

## Module 5 — Visualizing Data

Numbers in a CSV file are hard to interpret at a glance. In this module you'll retrieve your data, take a look at the raw file, then upload it to a graphing tool to see all three sensor channels plotted over time.

### Steps

**Step 1 — Retrieve the data**

Unplug the board. Remove the SD card and insert it into the USB card reader, then plug the reader into your computer. The card will appear as a drive — open it and confirm `log.csv` is there.

✅ **Checkpoint:** You can see `log.csv` on the SD card.

**Step 2 — Open the raw file**

Before graphing, take a look at the data in its raw form:

- **Windows:** right-click `log.csv` → **Open with → Notepad**. You'll see plain text with values separated by commas — one row per reading.
- **Mac:** right-click `log.csv` → **Open with → TextEdit**. Same thing — rows of comma-separated values.

If you have Excel or Numbers available, you can open it there too and it will automatically split the columns into a table.

✅ **Checkpoint:** You can see rows of sensor readings in the raw file.

**Step 3 — Open the graphing tool**

Go to the workshop site at **[bweiss16.github.io/utah_unay](https://bweiss16.github.io/utah_unay)** and click the **Sensor Data Grapher** card under Resources.

**Step 4 — Upload your CSV**

Click **Choose File** and select your `log.csv` file. The tool will plot lux, temperature, and humidity over time.

**Step 5 — Read your data**

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

> ⚠️ Make sure `log` is still uploaded — the board runs whatever sketch was last uploaded when it powers on.

✅ **Checkpoint:** The board is running on battery and logging without a USB connection.

**Step 3 — Seal it in the case**

Place your Feather and sensors inside the Pelican case and close the lid.

**Step 4 — Deploy outside**

Take your logger outside and place it somewhere interesting — in the sun, in the shade, on the ground. Leave it for at least 10 minutes.

**Step 5 — Retrieve and graph your data**

Bring the logger back in. Remove the SD card, upload `log.csv` to the graphing tool, and look at what you captured.

✅ **Checkpoint:** You have a graph showing real environmental data from your outdoor deployment.

---

*Utah Unây Workshop — Day 1 · Adafruit Feather RP2040 Adalogger · Arduino IDE*
