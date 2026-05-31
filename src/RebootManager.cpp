#include "RebootManager.h"
#include <Preferences.h>
#include <esp_system.h>

// Definition of static member variables
uint32_t RebootManager::_rebootCount = 0;
uint32_t RebootManager::_lastRebootReason = 0;

void RebootManager::begin() {
	load();
	
    esp_reset_reason_t reason_ = esp_reset_reason();

    // Increment reboot count
    _rebootCount++;
    _lastRebootReason = (uint32_t)reason_;
    save();
}

void RebootManager::save() {
    Preferences prefs_;
    if (!prefs_.begin("RebootManager", false)) {
        return;
    }

    prefs_.putUInt("reboots", _rebootCount);
    prefs_.putUInt("last_reason", _lastRebootReason);
    prefs_.end();
}

void RebootManager::load() {
    Preferences prefs_;
    if (!prefs_.begin("RebootManager", false)) {
        _rebootCount = 0;
        _lastRebootReason = 0;
        return;
    }
    _rebootCount = prefs_.getUInt("reboots", 0);
    _lastRebootReason = prefs_.getUInt("last_reason", 0);
    prefs_.end();
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