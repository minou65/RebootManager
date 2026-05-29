#pragma once

#include <Arduino.h>
#include <Preferences.h>
#include <esp_system.h>

/**
 * @brief Manages reboot information and history for ESP32 devices.
 *
 * Stores and loads reboot counter and reboot reasons from device preferences.
 * Provides easy access to human-readable reboot reason descriptions.
 * Automatically logs the current reboot reason at startup.
 */
class RebootManager {
public:
    /**
     * @brief Logs the current reboot reason and increments the reboot counter.
     *
     * Should be called once during system startup.
     * Automatically detects the current reset reason, stores it, and prints it to Serial.
     */
    static void logRebootReason();

    /**
     * @brief Loads reboot information from device preferences.
     *
     * Typically called once during system startup.
     */
    static void load();

    /**
     * @brief Saves current reboot information to device preferences.
     */
    static void save();

    /**
     * @brief Increments reboot counter by 1 and records the reason.
     *
     * @param reason The ESP32 reboot reason (e.g., ESP_RST_POWERON)
     */
    static void recordReboot(uint32_t reason);

    /**
     * @brief Returns the number of reboots recorded so far.
     *
     * @return Reboot counter value
     */
    static uint32_t getRebootCount();

    /**
     * @brief Returns the last reboot reason (ESP32 constant).
     *
     * @return Reboot reason constant
     */
    static uint32_t getLastRebootReason();

    /**
     * @brief Converts a reboot reason code to a human-readable string.
     *
     * @param reason The ESP32 reboot reason code
     * @return Human-readable description of the reboot reason
     */
    static String getRebootReasonText(uint32_t reason);

    /**
     * @brief Returns the last reboot reason as a human-readable string.
     *
     * @return Human-readable description of the last reboot reason
     */
    static String getLastRebootReasonText();

    /**
     * @brief Resets the reboot counter to 0.
     */
    static void resetRebootCount();

private:
    static uint32_t _rebootCount;
    static uint32_t _lastRebootReason;
};