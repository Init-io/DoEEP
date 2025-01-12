#ifndef DOEEP_H
#define DOEEP_H

#include <Arduino.h>

class DoEEP {
private:
    size_t _size;

    // Helper methods
    int findKey(String key);                    // Find the starting address of a key
    int findNextAvailableAddress();            // Find the next available address in EEPROM
    void writeToAddress(int addr, String data); // Write a string to EEPROM
    String readFromAddress(int addr);          // Read a string from EEPROM

public:
    DoEEP(size_t size);                        // Constructor to initialize EEPROM with a given size

    void flash();                              // Method to clear (flash) the EEPROM
    void write(String key, String value);      // Write a key-value pair to EEPROM
    String read(String key);                   // Read a value by its key
    String read(String key, String defaultValue); // Read with default value fallback
    bool exists(String key);                   // Check if a key exists in EEPROM
};

#endif
