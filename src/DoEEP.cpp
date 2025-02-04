#include <EEPROM.h>
#include "DoEEP.h"

DoEEP::DoEEP(size_t size) {
    _size = size;
#ifdef ESP_PLATFORM
    EEPROM.begin(_size); // Initialize EEPROM for ESP
#else
    // No initialization needed for AVR
#endif
}

// Flash (clear) the EEPROM
void DoEEP::flash() {
    for (int i = 0; i < _size; i++) {
        EEPROM.write(i, 0xFF); // Write default erased value
    }
#ifdef ESP_PLATFORM
    EEPROM.commit(); // Save changes for ESP
#endif
}

// Write a key-value pair to EEPROM
void DoEEP::write(String key, String value) {
    int addr = findKey(key);

    if (addr == -1) { // Key not found
        addr = findNextAvailableAddress();
        if (addr == -1) {
            Serial.println("No space available in EEPROM!");
            return;
        }

        writeToAddress(addr, key);
        int valueAddr = addr + key.length() + 1;
        writeToAddress(valueAddr, value);
    } else {
        int valueAddr = addr + key.length() + 1;
        writeToAddress(valueAddr, value);
    }

#ifdef ESP_PLATFORM
    EEPROM.commit(); // Save changes for ESP
#endif
}

// Read a value by its key
String DoEEP::read(String key) {
    int addr = findKey(key);
    if (addr == -1) {
        return String(); // Return NULL equivalent
    }
    int valueAddr = addr + key.length() + 1;
    return readFromAddress(valueAddr);
}

// Read with default value
String DoEEP::read(String key, String defaultValue) {
    int addr = findKey(key);
    if (addr == -1) {
        write(key, defaultValue);
        return defaultValue;
    }
    int valueAddr = addr + key.length() + 1;
    return readFromAddress(valueAddr);
}

// Check if a key exists
bool DoEEP::exists(String key) {
    return findKey(key) != -1;
}

// Find key address
int DoEEP::findKey(String key) {
    for (int addr = 0; addr < _size;) {
        String storedKey = readFromAddress(addr);
        if (storedKey == "") break;
        if (storedKey == key) return addr;
        addr += storedKey.length() + 1 + readFromAddress(addr + storedKey.length() + 1).length() + 1;
    }
    return -1;
}

// Find next available address
int DoEEP::findNextAvailableAddress() {
    for (int addr = 0; addr < _size; addr++) {
        if (EEPROM.read(addr) == 0xFF) return addr;
    }
    return -1;
}

// Write string to EEPROM
void DoEEP::writeToAddress(int addr, String data) {
    for (int i = 0; i < data.length(); i++) {
        EEPROM.write(addr + i, data[i]);
    }
    EEPROM.write(addr + data.length(), '\0');
}

// Read string from EEPROM
String DoEEP::readFromAddress(int addr) {
    String data = "";
    char c;
    while ((c = EEPROM.read(addr++)) != '\0' && addr < _size) {
        data += c;
    }
    return data;
}
