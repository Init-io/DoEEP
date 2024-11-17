#include <EBase.h>

EBase eeprom(512); // Initialize EEPROM with 512 bytes

void setup() {
    Serial.begin(9600);
    Serial.println("EBase Library Usage Example");

    // Step 1: Flash (Clear) the EEPROM
    Serial.println("\n--- Flashing EEPROM ---");
    eeprom.flash();

    // Step 2: Write data to EEPROM
    Serial.println("\n--- Writing Data to EEPROM ---");
    eeprom.write("email", "user@example.com");
    eeprom.write("password", "securePassword123");
    eeprom.write("ssid", "MyWiFiNetwork");
    eeprom.write("wifi_password", "WiFiPass123");

    // Step 3: Read data back from EEPROM
    Serial.println("\n--- Reading Data from EEPROM ---");
    String email = eeprom.read("email");
    String password = eeprom.read("password");
    String ssid = eeprom.read("ssid");
    String wifiPassword = eeprom.read("wifi_password");

    // Print the data to Serial Monitor
    Serial.println("Stored Data:");
    Serial.println("Email: " + email);
    Serial.println("Password: " + password);
    Serial.println("SSID: " + ssid);
    Serial.println("WiFi Password: " + wifiPassword);

    // Step 4: Update existing data
    Serial.println("\n--- Updating Data in EEPROM ---");
    eeprom.write("password", "newPassword456");
    String updatedPassword = eeprom.read("password");
    Serial.println("Updated Password: " + updatedPassword);
}

void loop() {
    // Nothing to do here
}
