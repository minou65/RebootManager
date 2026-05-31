# RebootManager

A lightweight ESP32 Arduino library for tracking reboot history. It stores reboot information in non-volatile memory (Preferences) and helps you inspect reboot causes in a human-readable way.

## Table of Contents

- [RebootManager](#rebootmanager)
  - [Table of Contents](#table-of-contents)
  - [Features](#features)
  - [Requirements](#requirements)
  - [Installation](#installation)
    - [Option 1: Arduino Library Manager (recommended)](#option-1-arduino-library-manager-recommended)
    - [Option 2: Manual installation](#option-2-manual-installation)
  - [Quick Start](#quick-start)
  - [API Reference](#api-reference)
    - [Static Methods](#static-methods)
  - [Usage Examples](#usage-examples)
    - [Basic Usage](#basic-usage)
    - [Resetting The Counter](#resetting-the-counter)
    - [Working With Raw Reason Codes](#working-with-raw-reason-codes)
  - [Reboot Reasons](#reboot-reasons)
  - [Troubleshooting](#troubleshooting)

## Features

- Tracks reboot count across power cycles
- Stores the last ESP32 reset reason persistently
- Converts ESP32 reset reason codes to readable text
- Simple static API (no object lifecycle required)
- Minimal memory overhead
- No dependencies except ESP32 core libraries

## Requirements

- **Hardware:** ESP32-based boards (ESP32, ESP32-S2, ESP32-S3, ESP32-C3)
- **Software:**
  - Arduino IDE 1.8.x or higher / PlatformIO
  - ESP32 Board Support Package (BSP) 2.0.0+
  - Arduino framework with:
    - `Preferences.h`
    - `esp_system.h`

## Installation

### Option 1: Arduino Library Manager (recommended)

1. Open Arduino IDE
2. Go to **Sketch > Include Library > Manage Libraries...**
3. Search for **RebootManager** and click **Install**

### Option 2: Manual installation

1. Download or clone this repository.
2. Place the folder in your Arduino libraries directory.
3. Restart Arduino IDE.

## Quick Start

```cpp
#include <Arduino.h>
#include <RebootManager.h>

void setup() {
  Serial.begin(115200);
  delay(300);

  // Load stored values, record the current reboot reason,
  // and increment the reboot counter.
  RebootManager::begin();

  Serial.println("---- Reboot Info ----");
  Serial.println("Count: " + String(RebootManager::getRebootCount()));
  Serial.println("Last reason: " + RebootManager::getLastRebootReasonText());
}

void loop() {
}
```

## API Reference

### Static Methods

- `RebootManager::begin()`
  - Loads reboot data from persistent storage, records the current ESP32 reset reason, increments the reboot counter, and saves the updated state. Call once from `setup()`.
- `RebootManager::getRebootCount()`
  - Returns current reboot count.
- `RebootManager::getLastRebootReason()`
  - Returns the raw ESP32 reset reason code.
- `RebootManager::getLastRebootReasonText()`
  - Returns a human-readable description of the last reason.
- `RebootManager::getRebootReasonText(uint32_t reason)`
  - Converts a reset reason code into human-readable text.
- `RebootManager::resetRebootCount()`
  - Resets the reboot counter to `0` and saves the change.

## Usage Examples

### Basic Usage

```cpp
#include <RebootManager.h>

void setup() {
  Serial.begin(115200);
  delay(300);

  // Initialize the library and persist the current reboot reason
  RebootManager::begin();

  Serial.print("Reboot count: ");
  Serial.println(RebootManager::getRebootCount());

  Serial.print("Last reboot reason: ");
  Serial.println(RebootManager::getLastRebootReasonText());
}

void loop() {
  // Your code here
}
```

### Resetting The Counter

```cpp
#include <RebootManager.h>

void setup() {
  Serial.begin(115200);
  RebootManager::begin();

  if (RebootManager::getRebootCount() > 100) {
    RebootManager::resetRebootCount();
    Serial.println("Reboot counter reset.");
  }
}

void loop() {
}
```

### Working With Raw Reason Codes

```cpp
#include <RebootManager.h>

void setup() {
  Serial.begin(115200);
  RebootManager::begin();

  uint32_t reason = RebootManager::getLastRebootReason();
  Serial.println("Reason code: " + String(reason));
  Serial.println("Reason text: " + RebootManager::getRebootReasonText(reason));
}

void loop() {
}
```

## Reboot Reasons

The library uses ESP-IDF reset reason constants. Some common reasons include:

- `ESP_RST_POWERON`: Power on reset
- `ESP_RST_SW`: Software reset
- `ESP_RST_PANIC`: Panic reset (from assert or error)

## Troubleshooting

- If the library does not seem to track reboots, ensure:
  - `RebootManager::begin()` is called once during `setup()`.
  - The selected board uses the ESP32 Arduino core with `Preferences` support.
  - The board is not running in an environment that clears NVS between flashes or boots.
