# Utah Unây Workshop 2026

A weekend workshop for high school students that brings together Traditional Ecological Knowledge (TEK) and Robotics to observe and understand the natural world. Students build a working environmental data logger — measuring light, temperature, and humidity — as a hands-on entry point into microcontroller programming and environmental sensing. The workshop is grounded in Two-Eyed Seeing: the practice of holding Indigenous and Western ways of knowing side by side, each strengthening the other. See the "Process Agenda" below for the schedule, which also contains more information about the TEK modules.

This repository contains guides and example sketches used for the microcontroller modules. The website linked below is a landing page for participants, whereas the repository is intended to help facilitators manage all workshop materials.


🌐 **Workshop site:** [bweiss16.github.io/utah_unay](https://bweiss16.github.io/utah_unay)

---

## Microcontroller Modules Overview

### Day 1 — Guided Build

Students work through six modules, ending with a deployed sensor system sealed in a weatherproof enclosure.

| Module | Topic | Key Steps |
|--------|-------|-----------|
| 1 | **Blink an LED** | Set up Arduino IDE for the RP2040, open built-in Blink example, experiment with delay timing |
| 2 | **Sensing Light** | Connect BH1750 via Qwiic, install library, open BareMinimum example, Serial Monitor + Serial Plotter |
| 3 | **Sensing Temperature & Humidity** | Daisy-chain AHT20 after BH1750, verify with AHT20 example, upload `light_temp_humidity` |
| 4 | **Data Logging** | Format SD card as FAT32, install SdFat library, upload `log`, log data for a few minutes, retrieve `log.csv` via SD card reader |
| 5 | **Visualizing Data** | Upload `log.csv` to the web graphing tool, view plotted sensor data |
| 6 | **Deployment** | Place system in Pelican case, go outside and deploy |

### Day 2 — Add the Display

Students add the Adafruit FeatherWing OLED 128x64 display to their logger. They'll run the example sketch first to verify it works, then upload the provided code to display all three sensor readings (light, temperature, humidity) live on screen.

---

## Student Guides

| Guide | Rendered | Markdown |
|-------|----------|----------|
| Day 1 — Building a Sensor Logger | [View](https://bweiss16.github.io/utah_unay/guides/day1-guide.html) | [guides/day1-guide.md](guides/day1-guide.md) |
| Day 2 — Adding the Display | [View](https://bweiss16.github.io/utah_unay/guides/day2-guide.html) | [guides/day2-guide.md](guides/day2-guide.md) |

---

## Hardware

Each student kit contains:

| Item | Part | Purpose |
|------|------|---------|
| Adafruit Feather RP2040 Adalogger | [#5980](https://www.adafruit.com/product/5980) | Main microcontroller + SD card |
| BH1750 Light Sensor | [#4681](https://www.adafruit.com/product/4681) | Module 2 — light sensing |
| AHT20 Temp & Humidity Sensor | [#4566](https://www.adafruit.com/product/4566) | Module 3 — temperature & humidity |
| FeatherWing OLED 128x64 | [#4650](https://www.adafruit.com/product/4650) | Day 2 — live display |
| Qwiic/STEMMA QT cables | — | Solder-free I2C connections |
| MicroSD card | — | Data logging |
| USB SD card reader | — | Transferring log.csv to computer |
| LiPo battery | — | Portable deployment |
| Pelican case (small) | — | Weatherproof enclosure for deployment |

---

## Repo Structure

```
utah_unay/
├── index.html                    # GitHub Pages landing page
├── graph/                        # Web-based CSV graphing tool
│   └── index.html
├── guides/                       # Student handouts (HTML + Markdown)
│   ├── day1-guide.html
│   ├── day1-guide.md
│   ├── day2-guide.html
│   └── day2-guide.md
├── sketches/                     # Arduino sketches for each module
│   ├── light_temp_humidity/
│   ├── log/
│   └── log_display/
└── README.md
```

---

## Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software) with the [Earle Philhower RP2040 core](https://github.com/earlephilhower/arduino-pico) installed
- Arduino libraries (all installable via Library Manager):
  - `hp_BH1750`
  - `Adafruit AHTX0`
  - `Adafruit SH110x`
  - `Adafruit GFX Library`
  - `SdFat - Adafruit Fork`
  - `Adafruit BusIO`
- A web browser (for the graphing tool — no Python required)

---

## Data Visualization

Students retrieve their `log.csv` from the SD card using a USB card reader and upload it to the hosted graphing tool at:

**[bweiss16.github.io/utah_unay/graph](https://bweiss16.github.io/utah_unay/graph)**

No software installation required — the tool runs entirely in the browser.

---

## To Do

- [ ] Update landing page with final version of Process Agenda (replace DRAFT PDF)
- [ ] Before workshop: uninstall sensor libraries (hp_BH1750, Adafruit AHTX0, Adafruit SH110x, Adafruit GFX) so the projected screen matches what students see when installing fresh
- [ ] Test latest firmware (6/12/2026)
- [ ] Print hard copies of guides
