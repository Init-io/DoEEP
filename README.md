# EEPROM Manager Library DoEEP
[![Arduino Library](https://img.shields.io/badge/Arduino-Library-blue.svg)](https://www.arduino.cc/reference/en/libraries/DoEEP)
![GitHub Release](https://img.shields.io/github/v/release/init-io/DoEEP?label=release)
[![License](https://img.shields.io/github/license/init-io/DoEEP)](LICENSE)

This Arduino library provides a simple interface to manage key-value pairs stored in EEPROM memory. It allows you to store, retrieve, update, and delete data from the EEPROM in a structured and efficient manner.

## Features  
- **Key-Value Storage**: Store and retrieve data using unique keys.  
- **EEPROM Management**: Flash (clear) EEPROM with a single command.  
- **Easy-to-Use API**: Simple methods to write, read, and manage data.  
- **Memory Efficiency**: Automatically finds the next available space for new keys and values.  

## Installation  

### Using Arduino IDE  
1. Download the ZIP file of this library.  
2. Open Arduino IDE.  
3. Go to **Sketch > Include Library > Add .ZIP Library...**.  
4. Select the downloaded ZIP file.  

### Manual Installation  
1. Clone or download this repository.  
2. Place the `DoEEP` folder into the `libraries` folder in your Arduino directory:  
   ```
   Documents/Arduino/libraries/
   ```

## Usage  

### Initialize the Library  
Include the library and initialize it with the desired EEPROM size (in bytes).  

```cpp
#include <DoEEP.h>

// Initialize the library with 512 bytes of EEPROM
DoEEP eeprom(512);
```

---

### Writing Data to EEPROM  
Store data by providing a key and a value.  

```cpp
eeprom.write("email", "user@example.com");
eeprom.write("wifi_password", "WiFiPass123");
```

---

### Reading Data from EEPROM  
Retrieve data by providing the key.  

```cpp
String email = eeprom.read("email");
String wifiPassword = eeprom.read("wifi_password");

Serial.println("Email: " + email);
Serial.println("WiFi Password: " + wifiPassword);
```

---

### Flash (Clear) EEPROM  
Erase all data from EEPROM.  
```cpp
eeprom.flash();
```

---

## Examples  

### Basic Example  
```cpp
#include <DoEEP.h>

// Initialize EEPROM with a size of 512 bytes
DoEEP eeprom(512);

void setup() {
  Serial.begin(9600);

  // Write data to EEPROM
  eeprom.write("ssid", "MyWiFiNetwork");
  eeprom.write("password", "SecurePassword123");

  // Read data from EEPROM
  String ssid = eeprom.read("ssid");
  String password = eeprom.read("password");

  // Print data to the Serial Monitor
  Serial.println("SSID: " + ssid);
  Serial.println("Password: " + password);
}

void loop() {
  // Add continuous logic here if needed
}
```

More examples can be found in the `examples/` folder.  

## API Reference  

### `DoEEP(size_t size)`  
- **Description**: Initializes the library with a specified EEPROM size.  
- **Parameters**:  
  - `size`: Size of EEPROM in bytes.  

### `void write(String key, String value)`  
- **Description**: Stores or updates a key-value pair in EEPROM.  
- **Parameters**:  
  - `key`: The unique key to identify the data.  
  - `value`: The value to be stored.  

### `String read(String key)`  
- **Description**: Retrieves the value associated with a key.  
- **Parameters**:  
  - `key`: The unique key to identify the data.  
- **Returns**: The value associated with the key.  

### `void flash()`  
- **Description**: Clears all data from the EEPROM.  

## Contributing  

Contributions are welcome! If you have suggestions or improvements, feel free to submit a pull request.  

## License  

This library is licensed under the MIT License. See the `LICENSE` file for more details.  

## Support  

If you encounter any issues or have questions, feel free to create an issue in the [GitHub repository](https://github.com/init-io/DoEEP).  
