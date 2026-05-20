# Utah UNAY Microcontrollers Workshop 2026

A weekend introduction to microcontrollers and sensor logging for high school students. Students build a working environmental data logger from scratch using an Adafruit Feather Logger, I2C sensors, and an SD card.

## Workshop Overview

**Day 1** — Guided build. Students work through four modules, ending with a deployed sensor logger writing data to an SD card.

| Module | Topic |
|--------|-------|
| 1 | Blink an LED — first upload, verify the board works |
| 2 | Photoresistor — first analog sensor, Serial Plotter |
| 3 | Temperature & humidity sensor — intro to I2C |
| 4 | SD card logging — saving and graphing real data |

**Day 2** — Independent work. Students choose a new I2C sensor from the kit, integrate it into their logger, and get it logging alongside temperature and humidity.

## Hardware

Each student kit contains:
- Adafruit Feather Logger
- Photoresistor module (3-pin breakout)
- I2C temperature & humidity sensor
- I2C sensor assortment kit (for Day 2)
- SD card
- Battery
- Jumper wires and assorted components

## Repo Structure

```
utah_unay_2026/
├── guides/                  # Printed student handouts
│   ├── day1-guide.html
│   └── day2-sensor-integration-guide.html
├── sketches/                # Arduino sketches for each module
│   ├── 01_blink/
│   ├── 02_photoresistor/
│   ├── 03_temp_humidity/
│   └── 04_sd_logging/
├── scripts/                 # Data processing and graphing
│   └── graph_data.py
└── README.md
```

## Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software)
- Python 3 (for graphing script)
  - `matplotlib`
  - `pandas`

## Instructor Notes

Student guides are in `guides/`. Each guide has placeholder sections marked with dashed boxes — fill these in with the appropriate code snippets and wiring diagrams before printing.
