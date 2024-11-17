#ifndef EBASE_H
#define EBASE_H

#include <Arduino.h>

class EBase {
private:
    size_t _size;

    // Helper methods
    int findKey(String key);               // Find the starting address of a key
    int findNextAvailableAddress();       // Find the next available address in EEPROM
    void writeToAddress(int addr, String data); // Write a string to EEPROM
    String readFromAddress(int addr);     // Read a string from EEPROM

public:
    EBase(size_t size);                   // Constructor to initialize EEPROM with a given size

    void flash();                         // Method to clear (flash) the EEPROM
    void write(String key, String value); // Write a key-value pair to EEPROM
    String read(String key);              // Read a value by its key
};

#endif
