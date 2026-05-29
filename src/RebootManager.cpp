#include "RebootManager.h"

// Definition of static member variables
uint32_t RebootManager::_rebootCount = 0;
uint32_t RebootManager::_lastRebootReason = 0;

void RebootManager::logRebootReason() {
    Preferences prefs_;
    prefs_.begin("system", false);

    // Increment reboot count
    uint32_t rebootCount_ = prefs_.getUInt("reboots", 0);
    rebootCount_++;
    prefs_.putUInt("reboots", rebootCount_);

    // Store last reboot reason
    esp_reset_reason_t reason_ = esp_reset_reason();
    prefs_.putUInt("last_reason", (uint32_t)reason_);

    prefs_.end();

    _lastRebootReason = (uint32_t)reason_;

    // Print reboot information to Serial
    Serial.print("Reboot reason: ");
    Serial.println(getRebootReasonText((uint32_t)reason_));
    Serial.println("Reboot count: " + String(_rebootCount));
}

void RebootManager::load() {
    Preferences prefs_;
    prefs_.begin("system", true);
    _rebootCount = prefs_.getUInt("reboots", 0);
    _lastRebootReason = prefs_.getUInt("last_reason", 0);
    prefs_.end();
}

void RebootManager::save() {
    Preferences prefs_;
    prefs_.begin("system", false);
    prefs_.putUInt("reboots", _rebootCount);
    prefs_.putUInt("last_reason", _lastRebootReason);
    prefs_.end();
}

void RebootManager::recordReboot(uint32_t reason) {
    _rebootCount++;
    _lastRebootReason = reason;
    save();
}

uint32_t RebootManager::getRebootCount() {
    return _rebootCount;
}

uint32_t RebootManager::getLastRebootReason() {
    return _lastRebootReason;
}

String RebootManager::getRebootReasonText(uint32_t reason) {
    switch (reason) {
    case ESP_RST_UNKNOWN:    return "Unknown";
    case ESP_RST_POWERON:    return "Power on";
    case ESP_RST_EXT:        return "External reset";
    case ESP_RST_SW:         return "Software reset";
    case ESP_RST_PANIC:      return "Panic reset";
    case ESP_RST_INT_WDT:    return "Interrupt watchdog reset";
    case ESP_RST_TASK_WDT:   return "Task watchdog reset";
    case ESP_RST_WDT:        return "Other watchdog reset";
    case ESP_RST_DEEPSLEEP:  return "Deep sleep reset";
    case ESP_RST_BROWNOUT:   return "Brownout reset";
    case ESP_RST_SDIO:       return "SDIO reset";
    case ESP_RST_USB:        return "USB reset";
    case ESP_RST_JTAG:       return "JTAG reset";
    case ESP_RST_EFUSE:      return "EFUSE reset";
    case ESP_RST_PWR_GLITCH: return "Power glitch reset";
    case ESP_RST_CPU_LOCKUP: return "CPU lockup reset";
    default:                 return "Unknown reason code: " + String(reason);
    }
}

String RebootManager::getLastRebootReasonText() {
    return getRebootReasonText(_lastRebootReason);
}

void RebootManager::resetRebootCount() {
    _rebootCount = 0;
    save();
}