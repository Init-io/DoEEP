#include <EEPROM.h>
#include "EBase.h"

EBase::EBase(size_t size) {
    _size = size;
    EEPROM.begin(_size); // Initialize EEPROM
}

// Flash (clear) the EEPROM
void EBase::flash() {
    for (int i = 0; i < _size; i++) {
        EEPROM.write(i, 0xFF); // Write default erased value
    }
    EEPROM.commit(); // Save changes
}

// Write a key-value pair to EEPROM
void EBase::write(String key, String value) {
    int addr = findKey(key);

    if (addr == -1) { // Key not found
        addr = findNextAvailableAddress();
        if (addr == -1) {
            Serial.println("No space available in EEPROM!");
            return;
        }

        // Write the new key and value
        writeToAddress(addr, key);

        int valueAddr = addr + key.length() + 1; // +1 for null terminator
        writeToAddress(valueAddr, value);
    } else {
        // Update the value if the key exists
        int valueAddr = addr + key.length() + 1;
        writeToAddress(valueAddr, value);
    }

    EEPROM.commit(); // Save changes to EEPROM
}

// Read a value by its key
String EBase::read(String key) {
    int addr = findKey(key);
    if (addr == -1) {
        return ""; // Return an empty string if the key is not found
    }

    int valueAddr = addr + key.length() + 1; // +1 for null terminator
    return readFromAddress(valueAddr);
}

// Find the starting address of a key
int EBase::findKey(String key) {
    for (int addr = 0; addr < _size;) {
        String storedKey = readFromAddress(addr);

        if (storedKey == "") break; // End of EEPROM content
        if (storedKey == key) return addr; // Key found

        // Skip key and its associated value
        addr += storedKey.length() + 1; // Skip key
        addr += readFromAddress(addr).length() + 1; // Skip value
    }
    return -1; // Key not found
}

// Find the next available address in EEPROM
int EBase::findNextAvailableAddress() {
    for (int addr = 0; addr < _size; addr++) {
        if (EEPROM.read(addr) == 0xFF) return addr; // Found empty space
    }
    return -1; // No available space
}

// Write a string to EEPROM
void EBase::writeToAddress(int addr, String data) {
    for (int i = 0; i < data.length(); i++) {
        EEPROM.write(addr + i, data[i]);
    }
    EEPROM.write(addr + data.length(), '\0'); // Null-terminate the string
}

// Read a string from EEPROM
String EBase::readFromAddress(int addr) {
    String data = "";
    char c;

    while ((c = EEPROM.read(addr++)) != '\0' && addr < _size) {
        data += c;
    }
    return data;
}
