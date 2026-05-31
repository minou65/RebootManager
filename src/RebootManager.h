#ifndef REBOOT_MANAGER_H
#define REBOOT_MANAGER_H

#include <Arduino.h>

/**
 * @brief Manages reboot information and history for ESP32 devices.
 */
class RebootManager {
public:
    /**
     * @brief Initializes the RebootManager and records the current reboot.
     *
     * Loads previous reboot information from NVS, increments the reboot counter,
     * stores the current reset reason, and updates internal state.
     * Should be called once at the start of setup().
     */
    static void begin();

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

    /**
     * @brief Saves current reboot information to NVS.
     */
    static void save();

    /**
     * @brief Loads reboot information from NVS.
     */
    static void load();
};

#endif // REBOOT_MANAGER_H