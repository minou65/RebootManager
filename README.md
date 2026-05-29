# RebootManager

RebootManager is a lightweight ESP32 Arduino library for tracking reboot history.
It stores reboot information in non-volatile memory (`Preferences`) and helps you inspect reboot causes in a human-readable way.

## Features

- Tracks reboot count across power cycles
- Stores the last ESP32 reset reason persistently
- Converts ESP32 reset reason codes to readable text
- Simple static API (no object lifecycle required)

## Requirements

- ESP32 board support package
- Arduino framework with:
  - `Preferences.h`
  - `esp_system.h`

## Installation

### Option 1: Arduino Library Manager (when published)

1. Open Arduino IDE.
2. Go to **Sketch > Include Library > Manage Libraries...**
3. Search for **RebootManager** and install.

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

  // Load stored values from Preferences
  RebootManager::load();

  // Record current reboot reason and update counter
  RebootManager::logRebootReason();

  Serial.println("---- Reboot Info ----");
  Serial.println("Count: " + String(RebootManager::getRebootCount()));
  Serial.println("Last reason: " + RebootManager::getLastRebootReasonText());
}

void loop() {
}
```

## API Overview

- `RebootManager::load()`
  - Loads reboot count and last reboot reason from persistent storage.
- `RebootManager::save()`
  - Saves current in-memory values to persistent storage.
- `RebootManager::logRebootReason()`
  - Reads the current ESP32 reset reason, increments reboot count, stores both values.
- `RebootManager::recordReboot(uint32_t reason)`
  - Manually increments reboot count and stores a provided reason.
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

## Notes

- The library stores data in the `Preferences` namespace `system` using keys:
  - `reboots`
  - `last_reason`
- Reboot reason values are based on ESP-IDF reset reason constants (for example `ESP_RST_POWERON`, `ESP_RST_SW`, and `ESP_RST_PANIC`).

## License

See the LICENSE file in this repository.
